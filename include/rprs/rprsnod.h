#ifndef RILL_RPRSNOD
#define RILL_RPRSNOD

#define RILL_RPRS_WRD 1    // word definition
#define RILL_RPRS_CLL 2    // word invocation
#define RILL_RPRS_CMT 3    // comment
#define RILL_RPRS_IXX 4    // signed integer
#define RILL_RPRS_UXX 4    // unsigned integer
#define RILL_RPRS_FXX 4    // floating-point number
#define RILL_RPRS_BUF 4    // buffer
#define RILL_RPRS_VEC 4    // vector
#define RILL_RPRS_MAP 4    // map

/* type, nodes, text */

int rprsnod ( rval * dst, int type, rval * nodes, rval * text );
int rprsnod_typ ( rval * node );
int rprsnod_nodes ( rval * node );
int rprsnod_text ( rval * node );

#endif
