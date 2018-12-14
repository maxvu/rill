typedef struct rvm {
    RVector * ds; // data stack
    RVector * ss; // side stack
    RVector * cs; // call stack

    RBuffer * it; // instruction table
    size_t    pc; // program counter
    RVector * ct; // constant table
} RVM;

RVM * rvm_create ();
void rvm_destroy ();
