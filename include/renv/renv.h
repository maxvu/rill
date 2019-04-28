#ifndef RILL_RBLD
#define RILL_RBLD

typedef struct REnv {
    RVM * vm;
    rval words;  // hash, word-name -> word-def (compiled bit, it offset, arity, text)
    rval constants;
    rval     it;          // instruction table
    rval     ct;          // constant table
    rval     nt;          // native function map
    rval constants;
    rval blocks;
} REnv;

REnv * renv ();

int renv_add_word ( REnv * env, rval * worddef );
int renv_recompile ( REnv * env );

void renv_destroy ( REnv * env );
