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
void runTest(void);

