#include "my_unity.h"
#include<stdio.h>
#include<string.h>

#define MAKE_GROUP(groupName)\
	const char* TEST__GROUP__##groupName = #groupName

#define MAKE_TEST(groupName, testName)\
	int TEST__##groupName##__##testName##_ (void);\
	void TEST__##groupName##__##testName##__run(void);\
	void TEST__##groupName##__##testName##__run(void){\
		addTest(#groupName, #testName, TEST__##groupName##__##testName##_);\
	}\
	int TEST__##groupName##__##testName##_ (void) 

#define INIT_TEST(groupName, testName)\
	TEST__##groupName##__##testName##__run();

#define BEFORE_ALL_TEST(groupName)\
	int BEFORE__TEST__##groupName##_(void);\
	void BEFORE__TEST__##groupName##__run(void);\
	void BEFORE__TEST__##groupName##__run(void){\
		addBefore(#groupName, BEFORE__TEST__##groupName##_, true);\
	}\
	int BEFORE__TEST__##groupName##_ (void)

#define BEFORE_EACH_TEST(groupName)\
	int BEFORE__EACH__TEST__##groupName##_ (void);\
	void BEFORE__EACH__TEST__##groupName##__run(void);\
	void BEFORE__EACH__TEST__##groupName##__run(void){\
		addBefore(#groupName, BEFORE__EACH__TEST__##groupName##_, false);\
	}\
	int BEFORE__EACH__TEST__##groupName##_ (void)

#define AFTER_ALL_TEST(groupName)\
	int AFTER__TEST__##groupName##_(void);\
	void AFTER__TEST__##groupName##__run(void);\
	void AFTER__TEST__##groupName##__run(void){\
		addAfter(#groupName, AFTER__TEST__##groupName##_, true);\
	}\
	int AFTER__TEST__##groupName##_(void)

#define AFTER_EACH_TEST(groupName)\
	int AFTER__EACH__TEST__##groupName##_ (void);\
	void AFTER__EACH__TEST__##groupName##__run(void);\
	void AFTER__EACH__TEST__##groupName##__run(void){\
		addAfter(#groupName, AFTER__EACH__TEST__##groupName##_, false);\
	}\
	int AFTER__EACH__TEST__##groupName##_ (void)

#define INIT_BEFORE_ALL_TEST(groupName)\
	BEFORE__TEST__##groupName##__run();

#define INIT_BEFORE_EACH_TEST(groupName)\
	BEFORE__EACH__TEST__##groupName##__run();

#define INIT_AFTER_ALL_TEST(groupName)\
	AFTER__TEST__##groupName##__run();

#define INIT_AFTER_EACH_TEST(groupName)\
	AFTER__EACH__TEST__##groupName##__run();
