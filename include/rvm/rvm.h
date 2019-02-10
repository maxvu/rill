#ifndef RILL_RVM
#define RILL_RVM

#define RILL_RVM_PSDEFSIZ 128
#define RILL_RVM_SSDEFSIZ 16
#define RILL_RVM_CSDEFSIZ 32
#define RILL_RVM_DTDEFSIZ 64
#define RILL_RVM_NFDEFSIZ 64

typedef struct RVM {
    size_t pc;          // program counter
    RVal   ot;          // ops table
    RVal   ps;          // data stack (primary)
    RVal   ss;          // data stack (secondary)
    RVal   cs;          // call stack
    RVal   dt;          // data table
    RVal   nf;          // native function map
    size_t mf;          // machine flags
    RVal   dr;          // debug reverse-index
} RVM;

RVM * rvm_create (
    RVal * ops_table,
    RVal * data_table,
    RVal * native_function_map,
    RVal * debug_reverse_index
);
int rvm_exec ( RVM * vm );
int rvm_step ( RVM * vm );
int rvm_destroy ( RVM * vm );

#endif
