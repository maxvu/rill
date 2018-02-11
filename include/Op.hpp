#ifndef RILL_OP
#define RILL_OP

#include <cstdint>

namespace Rill {

    enum class Op : uint8_t {

        // Misc.

        NOP = 0x00,

        // Value loading

        LDQ = 0x01,
        LDI = 0x02,
        LDF = 0x03,
        LDS = 0x04,

        // Integer arithmetic

        IADD = 0x05,
        ISUB = 0x06,
        IMUL = 0x07,
        IDIV = 0x08,
        IMOD = 0x09,
        ICMP = 0x0A,
        INEG = 0x0B,

        // Float arithmetic

        FADD = 0x10,
        FSUB = 0x11,
        FMUL = 0x12,
        FDIV = 0x13,
        FCMP = 0x14,
        FNEG = 0x15,
        FFLR = 0x16,
        FINF = 0x17,
        FNAN = 0x18,

        // Conversion

        CI2F = 0x19,
        CF2I = 0x1A,

        // Type-agnostic

        TYPE = 0x1B,
        NOT  = 0x1C,

        // Bitwise arithmetic

        BINV = 0x1D,
        BOR  = 0x1E,
        BXOR = 0x1F,
        BSHL = 0x20,
        BSHR = 0x21,

        // Stack manipulation

        POP  = 0x30,
        DUP  = 0x31,
        SWP  = 0x32,
        OVR  = 0x33,
        ROT  = 0x34,
        RRO  = 0x35,
        NIP  = 0x36,
        TCK  = 0x37,
        DUP2 = 0x38,
        SWP2 = 0x39,
        OVR2 = 0x3A,
        ROT2 = 0x3B,
        RRO2 = 0x3C,
        NIP2 = 0x3D,
        TCK2 = 0x3E,

        // Control flow

        JUMP = 0x50,
        JGEZ = 0x51,
        JLTZ = 0x52,
        JEQZ = 0x53,
        CALL = 0x54,
        RET  = 0x55,

        // String manipulation

        SNEW = 0x70,
        SCON = 0x71,
        SLEN = 0x72,
        SCMP = 0x73,

        // List manipulation

        LNEW = 0x80,
        LPSH = 0x81,
        LSHF = 0x82,
        LPOP = 0x83,
        LUSH = 0x84,
        LLEN = 0x85,

        // Map manipulation

        MNEW = 0x90,
        MSET = 0x91,
        MGET = 0x92,
        MPOP = 0x93,
        MLEN = 0x94

    };

};

#endif
