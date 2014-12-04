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

#include "smartio/Environment.hpp"
#include "smartio/Reader.hpp"

#include "smartio/utilitysupplier.hpp"
#include "smartio/fileformatexception.h"

static constexpr unsigned int INDEX_NBR_KEY = 1;
static constexpr unsigned int VERTEX_NBR_KEY = 2;

typedef struct {
	uint32_t magicNbr;
	uint16_t nbrObjects;
	uint16_t matFlag;
} headerBlock_t;

using HeaderSupplier = io::utility::aggregate_supplier<
		headerBlock_t,
		uint32_t,
		uint16_t,
		uint16_t>;

typedef struct {
public:
	char name[64];
	uint32_t startVertex;
	uint32_t nbrVertices;
	uint32_t startIndex;
	uint32_t nbrIndices;
} materialBlock_t;

class MaterialBlockSupplier : public io::Supplier<materialBlock_t> {
	materialBlock_t supply(io::Context& ctx) const override {
		materialBlock_t trgt;
		ctx.getStream().read(&trgt.name[0], 64);
		trgt.startVertex = ctx.construct<uint32_t>();
		trgt.nbrVertices = ctx.construct<uint32_t>();
		trgt.startIndex = ctx.construct<uint32_t>();
		trgt.nbrIndices = ctx.construct<uint32_t>();
		return trgt;
	}
};

typedef struct {
	std::list<uint16_t> indices;
} indexBlock_t;

class IndexBlockSupplier : public io::Supplier<indexBlock_t> {
	indexBlock_t supply(io::Context& ctx) const override {
		indexBlock_t target;
		unsigned int nbr = ctx.getValue(INDEX_NBR_KEY, 0);
		while(nbr --> 0) {
			target.indices.push_back(ctx.construct<uint16_t>());
		}
		return target;
	}
};

typedef struct {
	float pos[3];
	uint8_t boneIdx[4];
	float weights[4];
	float normals[3];
	float texCoords[2];
} vertex_t;

class VertexSupplier : public io::Supplier<vertex_t> {
	vertex_t supply(io::Context& ctx) const override {
		return {
			{ctx.construct<float>(), ctx.construct<float>(), ctx.construct<float>()},
			{ctx.construct<uint8_t>(), ctx.construct<uint8_t>(), ctx.construct<uint8_t>(),
					ctx.construct<uint8_t>()},
			{ctx.construct<float>(), ctx.construct<float>(), ctx.construct<float>(),
					ctx.construct<float>()},
			{ctx.construct<float>(), ctx.construct<float>(), ctx.construct<float>()},
			{ctx.construct<float>(), ctx.construct<float>()}
		};
	}
};

typedef struct {
	std::list<vertex_t> vertices;
} vertexBlock_t;

class VertexBlockSupplier : public io::Supplier<vertexBlock_t> {
	vertexBlock_t supply(io::Context& ctx) const override {
		vertexBlock_t target;
		unsigned int nbr = ctx.getValue(VERTEX_NBR_KEY, 0);
		while(nbr --> 0) {
			target.vertices.push_back(ctx.construct<vertex_t>());
		}
		return target;
	}
};

typedef struct {
	uint32_t nbrIndices;
	uint32_t nbrVertices;
	indexBlock_t indices;
	vertexBlock_t vertices;
} objectBlock_t;

class ObjectBlockSupplier : public io::Supplier<objectBlock_t> {
	objectBlock_t supply(io::Context& ctx) const override {
		objectBlock_t trgt;
		ctx.setValue(INDEX_NBR_KEY, trgt.nbrIndices = ctx.construct<uint32_t>());
		ctx.setValue(VERTEX_NBR_KEY, trgt.nbrVertices = ctx.construct<uint32_t>());
		trgt.indices = ctx.construct<indexBlock_t>();
		trgt.vertices = ctx.construct<vertexBlock_t>();
		return trgt;
	}
};

typedef struct {
	headerBlock_t header;
	uint32_t nbrMats;
	std::list<materialBlock_t> materials;
	std::list<objectBlock_t> objects;
} sknFile_t;

class FileSupplier : public io::Supplier<sknFile_t> {
	sknFile_t supply(io::Context& ctx) const override {
		sknFile_t trgt;
		trgt.header = ctx.construct<headerBlock_t>();
		uint32_t c = trgt.header.matFlag ?
				trgt.nbrMats = ctx.construct<uint32_t>()
				:
				trgt.nbrMats = 0;
		while (c --> 0) {
			trgt.materials.push_back(ctx.construct<materialBlock_t>());
		}
		c = trgt.header.nbrObjects;
		while (c --> 0) {
			trgt.objects.push_back(ctx.construct<objectBlock_t>());
		}
		return trgt;
	}
};

using io::Environment;
using io::Reader;
using std::ifstream;

int main(void) {
	Environment env;
	// Add suppliers
	Reader read = env.addDefaultConstructibleSupplier<FileSupplier>().
			addDefaultConstructibleSupplier<HeaderSupplier>().
			addDefaultConstructibleSupplier<MaterialBlockSupplier>().
			addDefaultConstructibleSupplier<ObjectBlockSupplier>().
			addDefaultConstructibleSupplier<IndexBlockSupplier>().
			addDefaultConstructibleSupplier<VertexBlockSupplier>().
			addDefaultConstructibleSupplier<VertexSupplier>().build();
	// Open the file
	ifstream file;
	file.open (R"wpykn(C:\Users\Carbon\Documents\CreativeWorkspace\LoLBearbeitung\data\characters\ahri\skins\base\ahri.skn)wpykn", std::ios::in | std::ios::binary);
	if(!file) {
		std::cout << "Couldn't open file. Exiting." << std::endl;
		return -1;
	}
	// And read the objects
	const io::Supplier<sknFile_t>& supplier = read.getSupplier<sknFile_t>();
	try {
		io::Context context = read.createContext(file);
		// sknFile_t sknData = read.construct<sknFile_t>(file);
		sknFile_t sknData = supplier.supply(context);
		std::cout << sknData.objects.front().vertices.vertices.back().texCoords[1];
	} catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
		return -1;
	} catch (io::fileformatexception& e) {
		std::cout << "Unexpected eof!" << std::endl;
		return -1;
	}
	file.close();
	return 0;
}
