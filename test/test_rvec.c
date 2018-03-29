#include "test.h"

#include "rvec.h"

void test_rvec () {

    RVec * a = rvec_create( sizeof( char ) );
    RVec * b = rvec_create( sizeof( char ) );
    insist( rvec_len( a ) == 0, "rvecs start empty" );

    for ( int i = 0; i < 10; i++ ) {
        char j = i + 1;
        rvec_set( a, i, &j );
    }
    insist( rvec_len( a ) == 10, "rvec set() on end is a push()" );

    rvec_reserve( a, 99 );
    insist( rvec_len( a ) == 10, "rvec reserve() doesn't ruin it" );

    int sum = 0;
    for ( int i = 0; i < 10; i++ ) {
        sum += *( ( char * ) rvec_get( a, i ) );
    }
    insist( sum == 55, "rvec can get()" );

    insist(
        *( ( char * ) rvec_head( a ) ) == 1 &&
        *( ( char * ) rvec_tail( a ) ) == 10,
        "rvec head() and tail() point to the right spots"
    );

    rvec_compact( a );
    sum = 0;
    for ( int i = 0; i < 10; i++ ) {
        sum += *( ( char * ) rvec_get( a, i ) );
    }
    insist(
        *( ( char * ) rvec_head( a ) ) == 1 &&
        *( ( char * ) rvec_tail( a ) ) == 10,
        "rvec head() and tail() point to the right spots"
    );

    rvec_destroy( a );
    rvec_destroy( b );

}
