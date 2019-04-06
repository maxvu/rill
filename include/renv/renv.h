#ifndef RILL_RBLD
#define RILL_RBLD

typedef struct REnv {
    RVM * vm;
    RVal words;  // hash, word-name -> word-def (compiled bit, it offset, arity, text)
    RVal constants;
    RVal     it;          // instruction table
    RVal     ct;          // constant table
    RVal     nt;          // native function map
    RVal constants;
    RVal blocks;
} REnv;

REnv * renv ();

int renv_add_word ( REnv * env, RVal * worddef );
int renv_recompile ( REnv * env );

void renv_destroy ( REnv * env );
