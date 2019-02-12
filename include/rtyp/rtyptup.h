#ifndef RILL_RTYP_RTYPTUP
#define RILL_RTYP_RTYPTUP

/*
    0: rtypkind
    1: name
    2: vec field values
*/

RVal rtyptup ( RVal * name, RVal * fields );
RVal * rtyptup_get_field ( RVal typtup, size_t index );

#endif
