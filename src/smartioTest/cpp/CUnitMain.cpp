/*
 * CUnitMain.cpp
 *
 *  Created on: 02.02.2016
 *      Author: WorldSEnder
 */

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>

int suite_init(void) {
	return 0;
}

int suite_clean(void) {
	return 0;
}

void test_example(void) {
	CU_ASSERT(2 == 2);
}
extern "C" {

void gradle_cunit_register(void) {
	CU_pSuite mySuite = CU_add_suite("operator tests", suite_init, suite_clean);
	CU_add_test(mySuite, "test", test_example);
}

}

#ifdef OUTSIDE_GRADLE
int main() {
	CU_initialize_registry();
	gradle_cunit_register();
	CU_console_run_tests();
}
#endif
