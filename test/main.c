#include <stdio.h>

#include "val/rval.h"
#include "val/rmap.h"
#include "val/rvec.h"
#include "val/rstr.h"

/* file: minunit.h */
#define mu_assert(test, msg) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
extern int tests_run;

int main ( int argc, char ** argv ) {
    printf( "OK\n" );
    return 1;
}
