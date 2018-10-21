#include "test.h"

void test_sanity () {

    test( "sanity check", {
        insist( 1 + 1 == 2 );
    } );

}
