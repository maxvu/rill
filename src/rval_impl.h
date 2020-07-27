#ifndef RILL_RVAL_IMPL
#define RILL_RVAL_IMPL

struct rval {
    UXX hed;
};

void rvhed_set_typ ( rval * val, UXX typ, rerr * err );
void rvhed_get_typ ( rval * val, UXX * typ, rerr * err );
void rvhed_set_tag ( rval * val, UXX tag, rerr * err );
void rvhed_get_tag ( rval * val, UXX * tag, rerr * err );
void rvhed_inc_ref ( rval * val, rerr * err );
void rvhed_dec_ref ( rval * val, rerr * err );

// 4 for type
// 7 for ref
// 53/19 for tag

#endif
