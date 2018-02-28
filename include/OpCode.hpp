#ifndef RILL_OPCODE
#define RILL_OPCODE

#include <cstdint>

namespace Rill {

    enum class OpCode : uint8_t {

        // Misc.

        NOP = 0x00,

        // Value loading

        LDCQ = 0x01,  // load constant, quick (0 to 255)
        LDIQ = 0x02,  // load i64, quick (-128 to 127)
        LDC  = 0x03,  // load constant
        LDI  = 0x04,  // load i64
        LDD  = 0x05,  // load double

        // Integer arithmetic

        IADD = 0x06, // i64 addition
        ISUB = 0x07, // i64 subtract
        IMUL = 0x08, // i64 multiplication
        IDIV = 0x09, // i64 floor division
        IMOD = 0x0A, // i64 modulo
        ICMP = 0x0B, // i64 comparison (i64 -1, 0 or 1)
        INEG = 0x0C, // i64 negation
        IINC = 0x0D, // i64 increment
        IDEC = 0x0E, // i64 decrement

        // Float arithmetic

        DADD = 0x10, // dbl addition
        DSUB = 0x11, // dbl subtraction
        DMUL = 0x12, // dbl multiplication
        DDIV = 0x13, // dbl division
        DCMP = 0x14, // dbl comparison (i64 -1, 0 or 1)
        DNEG = 0x15, // dbl negation
        DFLR = 0x16, // dbl floor
        DINF = 0x17, // dbl is-infinity
        DNAN = 0x18, // dbl is-NaN

        // Conversion

        CI2D = 0x19, // i64 to dbl
        CD2I = 0x1A, // dbl to i64

        // Type-agnostic

        TYPE = 0x1B, // type of value, as i64
        IS   = 0x1C, // truthiness, i64, 0 or 1
        NOT  = 0x1D, // falsiness, i64, 0 or 1

        // Bitwise arithmetic (on i64 only)

        BINV = 0x1E, // binary inverse
        BOR  = 0x1F, // binary OR
        BXOR = 0x20, // binary XOR
        BSHL = 0x21, // binary shift left
        BSHR = 0x22, // binary shift right

        // Stack manipulation

        POP  = 0x30, // remove top val
        DUP  = 0x31, // copy top val
        SWP  = 0x32, // swap top two vals
        OVR  = 0x33, // copy second value atop the first
        ROT  = 0x34, // move first val under second and third
        RRO  = 0x35, // summon third val to top
        NIP  = 0x36, // remove second val
        TCK  = 0x37, // copy top value and place beneath the second
        DUP2 = 0x38, // copy first two elements
        SWP2 = 0x39, // swap first top two val pairs
        OVR2 = 0x3A, // copy third and fourth vals atop the first and second
        ROT2 = 0x3B, // move the first and second vals beneath sixth
        RRO2 = 0x3C, // summon fifth and sixth vals atop the first and second
        NIP2 = 0x3D, // remove third and fourth vals
        TCK2 = 0x3E, // copy the top two values and place beneath the fourth

        // Control flow

        JUMP = 0x50, // unconditional jump
        JIFT = 0x51, // jump if truthy
        JIFF = 0x52, // jump if falsy
        CALL = 0x54, // builtin invocation
        HALT = 0x55, // stop interpreter

        // String manipulation

        SCON = 0x70, // string concatenate
        SLEN = 0x71, // string length

        // List manipulation

        LPSH = 0x81, // list push
        LSHF = 0x82, // list shift
        LPOP = 0x83, // list pop
        LUSH = 0x84, // list unshift
        LLEN = 0x85, // list length

        // Map manipulation

        MSET = 0x91, // map set
        MGET = 0x92, // map get
        MPOP = 0x93, // map get-and-remove
        MLEN = 0x94, // map size

    };

};

#endif
