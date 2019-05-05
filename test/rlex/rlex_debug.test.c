#include "config/rerr.h"
#include "rlex/rlex.h"
#include "rlex/rlexchr.h"
#include "rlex/rlexit.h"
#include "rlex/rlexstt.h"
#include "rval/dump.h"
#include "rval/rbuf.h"
#include "rval/rvec.h"
#include "test/test.h"

#include <stdio.h>
#include <string.h>

void rill_test_rlex_debug () {

    RTEST_BEGIN( "rlex / debug" )  {
        const char * message = ": one-plus-one 1 1 + ; ( comment 'str\\\"ing' )";
        size_t message_len = strlen( message );
        rlexstt stt;
        rval tokens = rnil();

        INSIST( rlex( &stt, ( const uint8_t * ) message, message + message_len ) );
        rlexstt_tokens( &tokens, &stt );
        rlex_dump( &tokens );
        printf( "lex status: %d", rlexstt_err( &stt ) );
        printf( "\n" );
    } RTEST_END;

}
