#ifndef RILL_RBLD
#define RILL_RBLD

typedef struct RBld {
    RVal constants;
    RVal blocks;
} RBld;

typedef struct RBldBlk {
    RVal ops;
} RBldBlk;

/*
    value tagging for constant table
    subroutine linking, offset calculation
    common recipes

    map buf -> bb
*/

RVal rbld ();
RVal rbld_bb ( RVal * bld );
RVal rbld_bb_op ( RVal * bb, uint8_t op );
RVal rbld_bb_jump ( RVal * bb, uint8_t op );
int rbld_compile ( RVal * prg, RVal * bld );

/*
    basic block

    buf name
    vec< uxx bytes | buf block name >
*/

RVal rbb_create()

#endif
