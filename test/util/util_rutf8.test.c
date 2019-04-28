// TODO: fix to use rerr

void rill_test_util_utf8 () {}

// #include "rval/rval.h"
// #include "test/test.h"
// #include "util/rutf8.h"
//
// typedef struct {
//     const char * str;
//     unsigned int len;
//     uint8_t      err;
// } utf8_testcase;
//
// const utf8_testcase * test_cases[] = {
//     [0] = &(utf8_testcase) { "hello world", 11, RUTF8_OK },
//     [1] = &(utf8_testcase) { "привет всем 大家好 こんにちは世 𬍤", 24, RUTF8_OK },
//     [2] = &(utf8_testcase) { "\xf8\x87\xbf\xbf\xbf", 0, RUTF8_INVALID_BYTE },
//     [3] = &(utf8_testcase) { "hi \xed\xb0\x80", 4, RUTF8_OK },
//     [4] = &(utf8_testcase) { "hi \xf0\xa0\x99\x9f", 4, RUTF8_OK },
//     [5] = &(utf8_testcase) { "hi \xed\xb0 ", 4, RUTF8_EARLY_TRUNCATION },
//     [6] = &(utf8_testcase) { "hi \xf0\xa0\x99 ", 4, RUTF8_EARLY_TRUNCATION }
// };
//
// void run_utf8_test_case ( const utf8_testcase * testcase ) {
//     rval s = rbuf( 10 );
//     rbuf_strcpy( &s, testcase->str );
//     uint8_t * begin = ( uint8_t * ) rbuf_strget( &s );
//     uint8_t * end = begin + rbuf_len( &s );
//
//     RUTF8Scan scan;
//     rutf8_scan( &scan, begin, end );
//     INSIST( scan.error == testcase->err );
//     if ( testcase->err == RUTF8_OK ) {
//         INSIST( scan.length == testcase->len );
//     }
//     rval_release( &s );
// }
//
// void rill_test_utf8 () {
//
//     RTEST_BEGIN( "rutf8 / ascii OK" )  {
//         run_utf8_test_case( test_cases[0] );
//     } RTEST_END;
//
//     RTEST_BEGIN( "rutf8 / two-byte sequences OK" )  {
//         run_utf8_test_case( test_cases[1] );
//     } RTEST_END;
//
//     RTEST_BEGIN( "rutf8 / overlong sequences rejected" )  {
//         run_utf8_test_case( test_cases[2] );
//     } RTEST_END;
//
//     RTEST_BEGIN( "rutf8 / three-byte sequences OK" )  {
//         run_utf8_test_case( test_cases[3] );
//     } RTEST_END;
//
//     RTEST_BEGIN( "rutf8 / four-byte sequences OK" )  {
//         run_utf8_test_case( test_cases[4] );
//     } RTEST_END;
//
//     RTEST_BEGIN( "rutf8 / early termination rejected" )  {
//         run_utf8_test_case( test_cases[5] );
//         run_utf8_test_case( test_cases[6] );
//     } RTEST_END;
//
// }
