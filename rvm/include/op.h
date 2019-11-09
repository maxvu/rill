#ifndef RILL_OPCODE
#define RILL_OPCODE

enum rvm_op {

    // control flow
    NOP,
    HALT,
    JUMP, // unconditional jump
    JIFT, // jump if truthy
    JIFF, // jump if falsy
    CALL, // builtin invocation
    HALT, // stop interpreter

    // type-generic

    TYPE,
    IS,
    NOT,
    CMP,

    // stack manipulation

    POP,  // remove top val
    DUP,  // copy top val
    SWP,  // swap top two vals
    OVR,  // copy second value atop the first
    ROT,  // move first val under second and third
    RRO,  // summon third val to top
    NIP,  // remove second val
    TCK,  // copy top value and place beneath the second
    DUP2, // copy first two elements
    SWP2, // swap first top two val pairs
    OVR2, // copy third and fourth vals atop the first and second
    ROT2, // move the first and second vals beneath sixth
    RRO2, // summon fifth and sixth vals atop the first and second
    NIP2, // remove third and fourth vals
    TCK2, // copy the top two values and place beneath the fourth

    // numbers

    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    INC,
    DEC,
    NEG,
    FLR,
    TOI,
    TOU,
    TOF,

    // String

    SCON,
    SLEN,
    SSUB, // subtring

    // Vector

    VPSH,
    VPOP,
    VSHF,
    VUNS,
    VSUB,
    VLEN,

    // Map

    MSET,
    MGET,
    MPOP,
    MSIZ

};

#endif
