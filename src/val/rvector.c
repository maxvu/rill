#include "val/rvector.h"

RVector * rvector_create ( size_t init_cap );
RVector * rvector_clone ( RVector * vector );
int rvector_destroy ( RVector * vector );

size_t rvector_lease ( RVector * vector );
size_t rvector_release ( RVector * vector );
int rvector_containsref ( RVector * vector, RRef * ref );

size_t rvector_len ( RVector * vector );
int rvector_reserve ( RVector * vector, size_t new_cap );
int rvector_compact ( RVector * vector );

RRef * rvector_get ( RVector * vector, size_t index );
int rvector_set ( RVector * vector, size_t index, RRef * val );
int rvector_push ( RVector * vector, RRef * val );
int rvector_pop ( RVector * vector );
void rvector_clear ( RVector * vector );
