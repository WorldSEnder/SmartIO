/*
 * main.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include <iostream>
#include <fstream>
#include <cstdint>
#include <list>
#include <memory>
#include <functional>

#include "smartio/Environment.hpp"
#include "smartio/Reader.hpp"

#include "smartio/utilitysupplier.hpp"
#include "smartio/fileformatexception.h"

static constexpr unsigned int INDEX_NBR_KEY = 1;
static constexpr unsigned int VERTEX_NBR_KEY = 2;

typedef struct
{
    uint32_t magicNbr;
    uint16_t nbrObjects;
    uint16_t matFlag;
} headerBlock_t;

using HeaderSupplier = io::utility::aggregate_supplier<
        headerBlock_t,
        uint32_t,
        uint16_t,
        uint16_t>;

typedef struct
{
public:
    char name[64];
    uint32_t startVertex;
    uint32_t nbrVertices;
    uint32_t startIndex;
    uint32_t nbrIndices;
} materialBlock_t;

using MaterialBlockSupplier = io::utility::aggregate_supplier<
        materialBlock_t,
        char[64],
        uint32_t,
        uint32_t,
        uint32_t,
        uint32_t>;

typedef struct
{
    std::list< uint16_t > indices;
} indexBlock_t;

class IndexBlockSupplier : public io::Supplier< indexBlock_t >
{
    bool doapply(io::ReadContext& ctx, indexBlock_t& target) const override
    {
        io::utility::fill_list(ctx, target.indices, ctx[INDEX_NBR_KEY]);
        return true;
    }
};

typedef struct
{
    float pos[3];
    uint8_t boneIdx[4];
    float weights[4];
    float normals[3];
    float texCoords[2];
} vertex_t;

using VertexSupplier = io::utility::aggregate_supplier<
        vertex_t,
        float[3],
        uint8_t[4],
        float[4],
        float[3],
        float[2]>;

typedef struct
{
    std::list< vertex_t > vertices;
} vertexBlock_t;

class VertexBlockSupplier : public io::Supplier< vertexBlock_t >
{
    bool doapply(io::ReadContext& ctx, vertexBlock_t& target) const
    {
      io::utility::fill_list(ctx, target.vertices, ctx[VERTEX_NBR_KEY]);
      return true;
    }
};

typedef struct
{
    uint32_t nbrIndices;
    uint32_t nbrVertices;
    indexBlock_t indices;
    vertexBlock_t vertices;
} objectBlock_t;

class ObjectBlockSupplier : public io::Supplier< objectBlock_t >
{
    bool doapply(io::ReadContext& ctx, objectBlock_t& trgt) const override
    {
        ctx[INDEX_NBR_KEY] = (ctx >>= trgt.nbrIndices);
        ctx[VERTEX_NBR_KEY] = (ctx >>= trgt.nbrVertices);
        ctx >> trgt.indices >> trgt.vertices;
        return true;
    }
};

typedef struct
{
    headerBlock_t header;
    uint32_t nbrMats;
    std::list< materialBlock_t > materials;
    std::list< objectBlock_t > objects;
} sknFile_t;

class FileSupplier : public io::Supplier< sknFile_t >
{
    bool doapply(io::ReadContext& ctx, sknFile_t& trgt) const override
    {
        ctx >> trgt.header;
        uint32_t c = 0;
        if (trgt.header.matFlag)
        {

            c = (ctx >>= trgt.nbrMats);
        }
        io::utility::fill_list(ctx, trgt.materials, c);
        io::utility::fill_list(ctx, trgt.objects, trgt.header.nbrObjects);
        return true;
    }
};

int main(void)
{
    io::Environment env;
    // Add suppliers
    env.emplaceSupplier< FileSupplier >();
    env.emplaceSupplier< HeaderSupplier >();
    env.emplaceSupplier< MaterialBlockSupplier >();
    env.emplaceSupplier< ObjectBlockSupplier >();
    env.emplaceSupplier< IndexBlockSupplier >();
    env.emplaceSupplier< VertexBlockSupplier >();
    env.emplaceSupplier< VertexSupplier >();
    io::Reader read = env.build();
    // Open the file
    std::ifstream file(
            R"wpykn(C:\Users\Carbon\Documents\CreativeWorkspace\LoLBearbeitung\data\characters\ahri\skins\base\ahri.skn)wpykn",
            std::ios::in | std::ios::binary );
    if (!file)
    {
        std::cout << "Couldn't open file. Exiting." << std::endl;
        return EXIT_FAILURE;
    }
    // And read the objects
    try
    {
        io::ReadContext context = read.from(file);
        sknFile_t sknData = context.construct<sknFile_t>();
        std::cout << sknData.objects.front().vertices.vertices.back().pos[1];
    } catch (std::invalid_argument& e)
    {
        // Environment can't supply type
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (io::fileformatexception& e)
    {
        // Formatexception, EOF mostly
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    file.close();
    return 0;
}
