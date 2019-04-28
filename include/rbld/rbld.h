#ifndef RILL_RBLD
#define RILL_RBLD

typedef struct RBld {
    rval constants;
    rval blocks;
} RBld;

typedef struct RBldBlk {
    rval ops;
} RBldBlk;

/*
    value tagging for constant table
    subroutine linking, offset calculation
    common recipes

    map buf -> bb
*/

rval rbld ();
rval rbld_bb ( rval * bld );
rval rbld_bb_op ( rval * bb, uint8_t op );
rval rbld_bb_jump ( rval * bb, uint8_t op );
int rbld_compile ( rval * prg, rval * bld );

/*
    basic block

    buf name
    vec< uxx bytes | buf block name >
*/

rval rbb_create()

#endif
