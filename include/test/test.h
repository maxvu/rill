#ifndef RILL_TEST
#define RILL_TEST

#include "config/color.h"
#include "rval/rbuf.h"

struct {
    struct {
        size_t n;
        size_t n_pass;
    } tot;
    struct {
        size_t n;
        size_t n_pass;
        rval name;
        rval msg;
    } cur;
} __rts;

void rtest_init ();
void rtest_test_begin ( const char * test_name );
void rtest_test_end ();
void rtest_test_cleanup ();

#define RILL_MACRO_INT_TO_STRING(i) #i
#define RILL_REALLY_MAKE_INT_MACRO_PARAM_INTO_STRING(i) RILL_MACRO_INT_TO_STRING(i)
#define RTEST_BEGIN(NAME) rtest_test_begin(NAME);
#define INSIST(COND) __rts.cur.n++; if (COND) { __rts.cur.n_pass++; } else { rbuf_strcat( &__rts.cur.msg, __FILE__ ":" RILL_REALLY_MAKE_INT_MACRO_PARAM_INTO_STRING(__LINE__) " | " RILL_CONSOLE_RED #COND RILL_CONSOLE_CLEAR "\n    "); }
#define RTEST_END rtest_test_end();

#endif
