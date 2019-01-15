#ifndef RILL_RPRG
#define RILL_RPRG

/*
    uxx version
    map info
    vec data
    buf ops
*/

RVal rprg ();
int rprg_getinfo ( RVal * dst, RVal * prg );
int rprg_setinfo ( RVal * prg, RVal * info );
int rprg_getdata ( RVal * dst, RVal * prg );
int rprg_setdata ( RVal * prg, RVal * data );
int rprg_getops ( RVal * dst, RVal * prg );
int rprg_setops ( RVal * prg, RVal * ops );
int rprg_isvalid ( RVal * prg );
int rprg_save ( RVal * prg, RVal * filename );
int rprg_load ( RVal * dst, RVal * filename );

#endif
