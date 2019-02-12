#ifndef RILL_RTYP_RTYPMAP
#define RILL_RTYP_RTYPMAP

/*
    0: rtypkind
    1: name
    2: key type
    3: val type

    exposed with generic HashMap valtype
*/

RVal rtypmap ( RVal * key_typ, RVal * val_typ );
RVal * rtypmap_keytyp ( RVal * typmap );
RVal * rtypmap_valtyp ( RVal * typmap );

#endif
