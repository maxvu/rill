#ifndef RILL_RVM
#define RILL_RVM

#define RILL_RVM_PSDEFSIZE 64
#define RILL_RVM_SSDEFSIZE 64
#define RILL_RVM_CSDEFSIZE 64
#define RILL_RVM_DTDEFSIZE 64
#define RILL_RVM_NFDEFSIZE 64

typedef struct RVM {
    const uint8_t * pg; // program
    size_t pc;          // program counter
    RVal ps;            // data stack (primary)
    RVal ss;            // data stack (secondary)
    RVal cs;            // call stack
    RVal dt;            // data table
    RVal nf;            // native function map
} RVM;

RVM * rvm_create ( RVal * prg );
int rvm_load_module ( RVM * vm, RVal * filename );
int rvm_register_native ( RVM * vm, RVal * name, void * fn );
int rvm_exec ( RVM * vm );
int rvm_exec_one ( RVM * vm );
int rvm_destroy ( RVM * vm );

#endif
