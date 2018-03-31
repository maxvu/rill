#include "test.h"

#include "rvec.h"

void test_rvec () {

    {

        RVec * vec = rvec_create( sizeof( char ) );
        insist( rvec_len( vec ) == 0, "rvecs start empty" );

        for ( int i = 0; i < 10; i++ ) {
            char j = i + 1;
            rvec_set( vec, i, &j );
        }
        insist( rvec_len( vec ) == 10, "rvec set() on end is a push()" );

        rvec_reserve( vec, 99 );
        insist( rvec_len( vec ) == 10, "rvec reserve() doesn't ruin it" );

        int sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += *( ( char * ) rvec_get( vec, i ) );
        }
        insist( sum == 55, "rvec can get()" );

        insist(
            *( ( char * ) rvec_head( vec ) ) == 1 &&
            *( ( char * ) rvec_tail( vec ) ) == 10,
            "rvec head() and tail() point to the right spots"
        );

        rvec_compact( vec );
        sum = 0;
        for ( int i = 0; i < 10; i++ ) {
            sum += *( ( char * ) rvec_get( vec, i ) );
        }
        insist(
            *( ( char * ) rvec_head( vec ) ) == 1 &&
            *( ( char * ) rvec_tail( vec ) ) == 10 &&
            rvec_len( vec ) == 10,
            "rvec compact() doesn't ruin it"
        );

        rvec_destroy( vec );

    }

    {

        RVec * vec = rvec_create( sizeof( int ) );

        int i = 1;
        rvec_push( vec, &i );
        i++;
        rvec_push( vec, &i );
        i++;
        rvec_push( vec, &i );

        RVec * clone = rvec_clone( vec );

        insist(
            rvec_len( clone ) == 3 &&
            *( ( int * ) rvec_get( clone, 0 ) ) == 1 &&
            *( ( int * ) rvec_get( clone, 1 ) ) == 2 &&
            *( ( int * ) rvec_get( clone, 2 ) ) == 3,
            "rvec_clone works"
        );

        rvec_destroy( clone );
        rvec_destroy( vec );

    }

}
