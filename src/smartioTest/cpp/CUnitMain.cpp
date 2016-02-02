/*
 * CUnitMain.cpp
 *
 *  Created on: 02.02.2016
 *      Author: WorldSEnder
 */

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <sstream>

#include "smartio/Environment.hpp"
#include "smartio/configurations.hpp"

int suite_init(void) {
	return 0;
}

int suite_clean(void) {
	return 0;
}

void simpleIntTest(void);

extern "C" {

void gradle_cunit_register(void) {
	CU_pSuite mySuite = CU_add_suite("Read Tests", suite_init, suite_clean);
	(void) CU_add_test(mySuite, "simple integer tests", simpleIntTest);
}

}

#ifdef OUTSIDE_GRADLE
int main() {
	CU_initialize_registry();
	gradle_cunit_register();
	CU_console_run_tests();
}
#endif

void simpleIntTest() {
	std::string bits("\x01\x11\x00\x12\x00\x00\x00", 7);
	std::stringstream ss(bits);
	io::Environment env(io::config::filereading);
	io::Reader reader = env.buildReader();
	io::ReadContext context = reader.from(ss);

	CU_ASSERT(0x01 == *context.get<int8_t>());
	CU_ASSERT(0x11 == *context.get<int16_t>());
	CU_ASSERT(0x12 == *context.get<int32_t>());
}
