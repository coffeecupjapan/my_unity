#include <stdbool.h>

void setup(void (*func)(void));
void teardown(void (*func)(void));
void checkString(char* a, char*b);
void checkInt(int a, int b);
int addTest(char* groupName, char* testName, int (*test)(void));
int addBefore(char* groupName, int (*test)(void), bool do_once);
int findAndRunBefore(char* groupName, bool do_once);
bool findFinishedBefore(char* groupName);
int insertFinishedBefore(char* groupName);
int addAfter(char* groupName, int (*test)(void), bool do_once);
int findAndRunAfter(char* groupName, bool do_once);
bool findFinishedAfter(char* groupName);
int insertFinishedAfter(char* groupName);
void runTest(void);

