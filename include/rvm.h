#ifndef RILL_RVM
#define RILL_RVM

typedef struct rvm {
    unsigned long ip;
    rvec *        ds;
    rvec *        ss;
    rvec *        cs;
} rvm;

#endif
