#include "rval.h"
#include "rvm.h"

#include <stdlib.h>

RVM * rvm_create ( RVal * prg ) {
    if ( !prg )
        return NULL;
    if ( !rprg_isvalid( prg ) )
        return NULL;
    char ok = 1;
    RVal ps = rnil();
    RVal ss = rnil();
    RVal cs = rnil();
    RVal dt = rnil();
    RVal nf = rnil();

    ok = ok && rvec_init( &ps, RILL_RVM_PSDEFSIZE );
    ok = ok && rvec_init( &ss, RILL_RVM_SSDEFSIZE );
    ok = ok && rvec_init( &cs, RILL_RVM_CSDEFSIZE );
    ok = ok && rval_copy( &dt, rvec_get( prg, 1 ) );
    ok = ok && rmap_init( &nf, RILL_RVM_NFDEFSIZE );

    RVM * vm = RILL_ALLOC( sizeof( RVM ) );
    ok = ok && vm;

    if ( !ok ) {
        rval_release( &ps );
        rval_release( &ss );
        rval_release( &cs );
        rval_release( &dt );
        rval_release( &nf );
        return NULL;
    }

    *vm = ( RVM ) {
        .pg = program,
        .pc = 0,
        .ps = ps,
        .ss = ss,
        .cs = cs,
        .dt = dt,
        .nf = nf
    };

    return vm;
}

int rvm_load_module ( RVM * vm, RVal * filename ) {

}

int rvm_register_native ( RVM * vm, RVal * name, void * fn ) {

}

int rvm_exec ( RVM * vm ) {

}

int rvm_exec_one ( RVM * vm ) {

}

int rvm_destroy ( RVM * vm ) {
    if ( !vm )
        return 0;
    rval_release( &vm->ps );
    rval_release( &vm->ss );
    rval_release( &vm->cs );
    rval_release( &vm->dt );
    rval_release( &vm->nf );
    RILL_DEALLOC( vm );
    return 1;
}
