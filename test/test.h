#include <stdio.h>

#define insist(test, msg) do { \
    if (test) { printf("OK  %s\n", msg); n_passed++; } \
    else printf("!!  %s\n", msg); \
    n_run++; } while ( 0 )

int n_run;
int n_passed;

void test_all();
void test_rval();
