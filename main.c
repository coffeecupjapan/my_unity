#include "my_unity.h"
#include "fixture.h"
#include <stdio.h>
#include <stdlib.h>

int hoge;

void setupFunc(void) {
	hoge = 1;
	printf("start setup : with hoge = %d \n", hoge);
}

void teardownFunc(void) {
	printf("teardown : with hoge = %d \n", hoge);
}

char* testName1 = "testName1";
char* testName2 = "testName2";
char *testName3 = "testName3";

char* groupName1 = "groupName1";
char* groupName2 = "groupName2";
char* groupName3 = "groupName3";

struct testGroup {
	char* test;
	char* group;
};

MAKE_GROUP(groupName1);

MAKE_TEST(groupName3, testName3) {
	int fuga = 1;
	checkInt(hoge, fuga);
	return 0;
}

MAKE_TEST(groupName1, testName1) {
	int fuga = 1;
	checkInt(hoge, fuga);
	return 0;
}

MAKE_TEST(groupName1, testName2) {
	int fuga = 1;
	checkInt(hoge, fuga);
	return 0;
}

MAKE_TEST(groupName2, testName2) {
	int fuga = 1;
	checkInt(hoge, fuga);
	return 0;
}

AFTER_ALL_TEST(groupName1) {
	hoge = 2;
	printf("-- after test [ hoge = %d ]\n", hoge);
	return 1;
}

BEFORE_ALL_TEST(groupName1) {
	hoge = 1;
	printf("-- before test [ hoge = %d ] \n", hoge);
	return 1;
}

BEFORE_EACH_TEST(groupName1) {
	hoge = 3;
	printf("- before each test [ hoge = %d ] \n", hoge);
	return 1;
}

BEFORE_EACH_TEST(groupName2) {
	hoge = 1;
	printf("- before each test [ hoge = %d ] \n", hoge);
	return 1;
}

int main(void) {
	char* testNames[100] = {
		testName1,
		testName2
	};
	setup(setupFunc);
	INIT_TEST(groupName3, testName3);
	INIT_TEST(groupName1, testName1);
	INIT_TEST(groupName1, testName2);
	INIT_TEST(groupName2, testName2);
	INIT_BEFORE_ALL_TEST(groupName1);
	INIT_BEFORE_EACH_TEST(groupName1);
	INIT_BEFORE_EACH_TEST(groupName2);
	INIT_AFTER_ALL_TEST(groupName1);
	runTest();
	teardown(teardownFunc);
	return 0;
}
