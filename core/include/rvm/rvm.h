#ifndef RILL_RVM
#define RILL_RVM

// Default sizes for VM structures.
#define RILL_RVM_PSDEFSIZ 128
#define RILL_RVM_SSDEFSIZ 16
#define RILL_RVM_CSDEFSIZ 32
#define RILL_RVM_DTDEFSIZ 64
#define RILL_RVM_NFDEFSIZ 64

typedef struct RVM {
    size_t   pc;          // program counter
    RVal     it;          // instruction table
    RVal     ps;          // data stack, primary
    RVal     ss;          // data stack, secondary
    RVal     cs;          // call stack
    RVal     ct;          // constant table
    RVal     nt;          // native function map
    uint32_t mf;          // machine flags (debug?, num behavior?)
} RVM;

RVM * rvm_create ();
int rvm_exec ( RVM * vm );
int rvm_step ( RVM * vm );
int rvm_destroy ( RVM * vm );

#endif
