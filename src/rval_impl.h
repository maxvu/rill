#ifndef RILL_RVAL_IMPL
#define RILL_RVAL_IMPL

struct rval {
    UXX hed;
};

char rvh_get_typ ( rval * val, UXX * typ );
rerr rvh_set_typ ( rval * val, UXX typ );
rerr rvh_get_tag ( rval * val, UXX * tag );
rerr rvh_set_tag ( rval * val, UXX tag );
rerr rvh_inc_ref ( rval * val );
rerr rvh_dec_ref ( rval * val );

// 4 for type
// 7 for ref
// 53/19 for tag

#endif
