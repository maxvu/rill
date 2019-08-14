#ifndef RILL_ERR
#define RILL_ERR

#define RERR_OK   0

#define RERR_USE_NULL 33
#define RERR_USE_TYPE 34

#define RERR_SYS_ALLOC 65

typedef unsigned int rerr;

char rerr_ok ( rerr err );

#endif
