#ifndef RILL_RTYP_RTYPWRD
#define RILL_RTYP_RTYPWRD

/*
    0: rtypkind
    1: name
    2: input types
    3: output types
    4: uxx options
        0: is pure
*/

RVal rtypwrd ( RVal * name, RVal * inputs, RVal * outputs, RVal * options );
RVal * rtypwrd_inputs ( RVal * typwrd );
RVal * rtypwrd_outputs ( RVal * typwrd );
RVal * rtypwrd_options ( RVal * typwrd );

RVal * rtypwrd_satisfiedby ( RVal * typwrd );

#endif
