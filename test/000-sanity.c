#include "rill_test.h"
#include "rval.h"

RILL_TEST_BEGIN ( "sanity" ) {
    INSIST( 1 + 1 == 2 );
} RILL_TEST_END
