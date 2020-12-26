#define RILL_ASSERT( cond ) if ( !( cond ) ) { rill_test_ok = 0; printf( "%s[ !! ] %s\n    %s:%d %s%s\n", "\x1b[31m", rill_test_name, __FILE__, __LINE__, #cond, "\x1b[0m" ); }
#define RILL_TEST( tst, blk ) rill_test_begin( tst ); { blk ; } rill_test_end();

int rill_run_tests ();
