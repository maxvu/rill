#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

const char * GREEN = "\x1B[32m";
const char * RED   = "\x1B[31m";
const char * RESET = "\x1B[0m";

typedef struct rts {
    unsigned long n_run;
    unsigned long n_pass;
    const char *  cur_name;
    unsigned long cur_run;
    unsigned long cur_pass;
    char          colors;
} rts;

const char * color_of ( unsigned long a, unsigned long b ) {
    if ( a == b )
        return GREEN;
    return RED;
}

rts * rts_create ( int colors ) {
    rts * ts = malloc( sizeof( rts ) );
    if ( !ts )
        return ts;
    ts->n_run = 0;
    ts->n_pass = 0;
    ts->cur_name = NULL;
    ts->cur_run = 0;
    ts->cur_pass = 0;
    ts->colors = colors;
    return ts;
}

int rts_begin_test ( rts * ts, const char * name ) {
    if ( !ts || !name ) {
        fprintf( stderr, "rill test: null argument\n" );
        return 0;
    }
    ts->cur_name = name;
    return 1;
}

int rts_assert ( rts * ts, int cond, const char * txt ) {
    if ( !ts ) {
        fprintf( stderr, "rill test: null argument\n" );
        return 0;
    }
    if ( cond )
        return 1;
    fprintf( stderr, "%s%s%s\n", RED, ts->cur_name, RESET );
    fprintf( stderr, "    %s%s%s\n", RED, txt, RESET );
    raise( SIGINT );
    return 1;
}

void rts_report_test ( rts * ts ) {
    if ( !ts ) {
        fprintf( stderr, "rill test: null argument\n" );
        return;
    }
    fprintf(
        stderr,
        "%s%s ( %lu / %lu )%s\n",
        color_of( ts->cur_run, ts->cur_pass ),
        ts->cur_name,
        ts->cur_run,
        ts->cur_pass,
        RESET
    );
}

void rts_end_test ( rts * ts ) {
    if ( !ts ) {
        fprintf( stderr, "rill test: null argument\n" );
        return;
    }
    ts->n_run += ts->cur_run;
    ts->n_pass += ts->cur_pass;
    ts->cur_run = 0;
    ts->cur_pass = 0;
}

void rts_report_all ( rts * ts ) {
    fprintf(
        stderr,
        "\n\n%s%lu run\n%lu passed%s\n",
        color_of( ts->cur_run, ts->cur_pass ),
        ts->n_run,
        ts->cur_pass,
        RESET
    );
}

int rts_successful ( rts * ts ) {
    if ( !ts )
        return 0;
    return ts->n_run == ts->n_pass;
}
