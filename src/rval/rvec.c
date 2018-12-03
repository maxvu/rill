#include "rval/rvec.h"

RVec * rvec_create ( size_t init_cap ) {

}

void rvec_destroy ( RVec * vec ) {

}

void rvec_ref ( RVec * vec ) {

}

void rvec_deref ( RVec * vec ) {

}

int rvec_unique ( RVec * vec ) {

}

size_t rvec_len ( RVec * vec ) {

}

int rvec_reserve ( RVec * vec, size_t new_cap ) {

}

int rvec_compact ( RVec * vec ) {

}

RRef * rvec_get ( RVec * vec ) {

}

int rvec_set ( RVec * vec, size_t index, RRef * ref ) {

}

int rvec_push ( RVec * vec, RRef * ref ) {

}

int rvec_pop ( RVec * vec ) {

}

int rvec_concat ( RVec * vec, RVec * other ) {

}

int rvec_fill ( RVec * vec, RRef * val, size_t n ) {

}

void rvec_clear ( RVec * vec ) {

}
