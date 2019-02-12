#ifndef RILL_RTYP_RTYPVEC
#define RILL_RTYP_RTYPVEC

/*
    0: rtypkind
    1: name
    2: held type
*/

RVal rtypvec ( RVal * held_typ );
RVal * rtypvec_heldtyp ( RVal * typvec );

#endif
