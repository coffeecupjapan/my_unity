#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

#include "fixture.h"
#include "my_unity.h"

struct testType {
	char* groupName;
	char* testName;
	int (*test)(void);
};

struct beforeTestType {
	char* groupName;
	int (*before)(void);
	bool do_once;
};

struct afterTestType {
	char* groupName;
	int (*after)(void);
	bool do_once;
};

int totalTest;
int totalOK;
int totalNG;
struct testType *tests[100];
struct beforeTestType *befores[100];
struct afterTestType *afters[100];
char* finishedBeforeTest[100];
char *finishedAfterTest[100];

void printTests(struct testType *tests[100], int empty_count){
	printf("start with %d ...\n", empty_count);
	for (int i = 0; i < 100; i++) {
		printf("%d : %s %s\n", i, tests[i]->groupName, tests[i]->testName);
	}
	printf("end ...\n");
}

int initTest(void) {
	return 0;
}

int initBeforeTest(void) {
	return 0;
}

int initAfterTest(void) {
	return 0;
}

struct testType *initTestType(char* groupName, char* testName, int(*test)(void)) {
	struct testType *t = malloc(sizeof(struct testType));
	t->groupName = groupName;
	t->testName = testName;
	t->test = test;
	return t;
}

struct beforeTestType *initBeforeTestType(char* groupName, int(*before)(void), bool do_once) {
	struct beforeTestType *b = malloc(sizeof(struct beforeTestType));
	b->groupName = groupName;
	b->before = before;
	b->do_once = do_once;
	return b;
}

struct afterTestType *initAfterTestType(char* groupName, int(*after)(void), bool do_once) {
	struct afterTestType *a = malloc(sizeof(struct afterTestType));
	a->groupName = groupName;
	a->after = after;
	a->do_once = do_once;
	return a;
}

void setup(void (*func)(void))
{
	for (int i = 0; i < 100; i++) {
		// test
		struct testType *t = initTestType("", "", *initTest);
		tests[i] = t;
		// before
		struct beforeTestType *b = initBeforeTestType("", *initBeforeTest, false);
		befores[i] = b;
		// after
		struct afterTestType *a = initAfterTestType("", *initAfterTest, false);
		afters[i] = a;
		// finished before / after (before_all & after_all)
		finishedBeforeTest[i] = "";
		finishedAfterTest[i] = "";
	}

	func();
}

void teardown(void (*func)(void))
{
	func();
	printf("\n-------------------\n");
	printf("totalTests : %d\n", totalTest);
	printf("totalOK : %d\n", totalOK);
	printf("totalNG : %d\n", totalNG);
	printf("-------------------\n");
}

int compareTestType(const void* a, const void* b) {
    struct testType* test1 = (struct testType*)a;
    struct testType* test2 = (struct testType*)b;
    return strcmp(test1->groupName, test2->groupName);
}

int addTest(char* groupName, char* testName, int (*test)(void)) {
	int empty_test_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp ((tests[i]->groupName), "") == 0) {
			empty_test_count = i;
			break;
		}
		// should handle case that overflow.
		if (i == 99) {
			empty_test_count = 0;
			break;
		}
	}
	tests[empty_test_count] = initTestType(groupName, testName, test);
	qsort(tests, 100, sizeof(tests[0]), compareTestType);
	return empty_test_count;
}

int addBefore(char* groupName, int(*before)(void), bool do_once){
	int empty_before_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp ((befores[i]->groupName), "") == 0) {
			empty_before_count = i;
			break;
		}
		// should handle case that overflow.
		if (i == 99) {
			return -1;
		}
	}
	befores[empty_before_count] = initBeforeTestType(groupName, before, do_once);
	return empty_before_count;
}

int findAndRunBefore(char* groupName, bool do_once) {
	int found_before_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp ((befores[i]->groupName), groupName) == 0 && do_once == befores[i]->do_once) {
			found_before_count = i;
			break;
		}
		if (i == 99) {
			return 0;
		}
	}
	if (befores[found_before_count]->do_once) {
		if (findFinishedBefore(groupName)) {
			return 0;
		}
		insertFinishedBefore(groupName);
	}
	return (*befores[found_before_count]->before)();
}

bool findFinishedBefore(char* groupName) {
	for (int i = 0; i < 100; i++) {
		if (strcmp(finishedBeforeTest[i], groupName) == 0) {
			return true;
		}
	}
	return false;
}

int insertFinishedBefore(char* groupName) {
	int empty_finished_before_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp(finishedBeforeTest[i], "") == 0) {
			empty_finished_before_count = i;
		}
		if (i == 99) {
			return 0;
		}
	}
	finishedBeforeTest[empty_finished_before_count] = groupName;
	return empty_finished_before_count;
}

int findAndRunAfter(char* groupName, bool do_once) {
	int found_after_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp((afters[i]->groupName), groupName) == 0 && do_once == afters[i]->do_once) {
			found_after_count = i;
			break;
		}
		if (i == 99) {
			return 0;
		}
	}
	if (afters[found_after_count]->do_once) {
		if (findFinishedAfter(groupName)) {
			return 0;
		}
		insertFinishedAfter(groupName);
	}
	return (*afters[found_after_count]->after)();
}

bool findFinishedAfter(char* groupName) {
	for (int i = 0; i < 100; i++) {
		if (strcmp(finishedAfterTest[i], groupName) == 0) {
			return true;
		}
	}
	return false;
}

int insertFinishedAfter(char* groupName) {
	int empty_finished_after_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp(finishedAfterTest[i], "") == 0) {
			empty_finished_after_count = i;
		}
		if (i == 99) {
			return 0;
		}
	}
	finishedAfterTest[empty_finished_after_count] = groupName;
	return empty_finished_after_count;
}

int addAfter(char* groupName, int(*after)(void), bool do_once){
	int empty_after_count = 0;
	for (int i = 0; i < 100; i++) {
		if (strcmp((afters[i]->groupName), "") == 0) {
			empty_after_count = i;
			break;
		}
		if (i == 99) {
			return -1;
		}
	}
	afters[empty_after_count] = initAfterTestType(groupName, after, do_once);
	return empty_after_count;
}

void runTest(void) {
	for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
		// before
		if (!findFinishedBefore(tests[i]->groupName)) {
			findAndRunBefore(tests[i]->groupName, true);
		}
		findAndRunBefore(tests[i]->groupName, false);
		// main
		if (strcmp((tests[i]->groupName), "") != 0) {
			printf("start test [group] %s [test] %s\n", tests[i]->groupName, tests[i]->testName);
			tests[i]->test();
		}
		// after
		int next_i = i == 99 ? 0 : i + 1;
		if (!findFinishedAfter(tests[i]->groupName) && tests[next_i]->groupName != tests[i]->groupName) {
			findAndRunAfter(tests[i]->groupName, true);
		}
		findAndRunAfter(tests[i]->groupName, false);
	}
}

int countTest(void) {
	return sizeof(tests);
}

void checkString(char* a, char* b) {
	totalTest += 1;
	if (strcmp(a, b) == 0) {
		printf("check OK : %s == %s \n", a, b);
		totalOK += 1;
	} else {
		printf("check NG : %s == %s \n", a, b);
		totalNG += 1;
	}
}

void checkInt(int a, int b) {
	totalTest += 1;
	if (a == b) {
		printf("check OK : %d == %d \n", a, b);
		totalOK += 1;
	} else {
		printf("check NG : %d == %d \n", a, b);
		totalNG += 1;
	}
}