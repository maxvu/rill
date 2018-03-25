#include "rvec.h"

#include "minunit.h"

char * test_rvec_basic_ops () {

    RVec * vec = rvec_create( 10, sizeof( int ) );

    mu_assert( "rvec begins empty", rvec_len( vec ) == 0 );
    mu_assert( "rvec init_cap honored", rvec_cap( vec ) >= 10 );

    for ( int i = 1; i <= 10; i++ ) {
        rvec_push( vec, &i );
    }
    mu_assert( "rvec_push incs len one", vec->len == 10 );

    int sum = 0;
    for ( int i = 0; i < 10; i++ ) {
        sum += *( ( int * ) rvec_get( vec, i ) );
    }
    mu_assert( "rvec_get retrieves", sum == 55 );

    rvec_destroy( vec );

    return NULL;

}

char * test_rvec_resize () {

    RVec * vec = rvec_create( 10, sizeof( int ) );

    for ( int i = 1; i <= 100; i++ ) {
        rvec_push( vec, ( void * ) &i );
    }
    mu_assert( "push() triggers resize", vec->cap >= 100 );

    rvec_clear( vec );
    mu_assert( "clear() triggers compact()", vec->cap < 100 );

    rvec_reserve( vec, 100 );
    mu_assert( "reserve() triggers resize()", vec->cap >= 100 );

    rvec_destroy( vec );

    return NULL;

}

char * test_rvec () {
    mu_run_test( test_rvec_basic_ops );
    mu_run_test( test_rvec_resize );
    return NULL;
}
