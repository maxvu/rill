#ifndef RILL_OP
#define RILL_OP

#include <cstdint>

namespace Rill {

    enum class Op : uint8_t {
    
        NOP  = 0x00,
        LDI  = 0x01,
        LDU  = 0x02,
        LDF  = 0x03,
        LDC  = 0x04,
        
        ADD  = 0x10,
        SUB  = 0x11,
        MUL  = 0x12,
        DIV  = 0x13,
        MOD  = 0x14,
        NEG  = 0x15,
        NOT  = 0x16,
        INV  = 0x17
        AND  = 0x18,
        OR   = 0x19,
        XOR  = 0x1A,
        SHL  = 0x1B,
        SHR  = 0x1C,
        TYPE = 0x1D,
        SIZE = 0x1E,
        CMP  = 0x1F,
        
        POP  = 0x26,
        DUP  = 0x28,
        SWAP = 0x29,
        OVER = 0x2A,
        ROT  = 0x2B,
        NIP  = 0x2C,
        
        JUMP = 0x40,
        JGEZ = 0x41,
        JLTZ = 0x41,
        JEQZ = 0x42,
        CALL = 0x42,
        RET  = 0x43,
        
        LNEW = 0x50,
        LPSH = 0x51,
        LSHF = 0x51,
        LPOP = 0x52,
        LUSH = 0x53,
        LLEN = 0x54,
        
        MNEW = 0x60,
        MSET = 0x61,
        MGET = 0x62,
        MPOP = 0x63,
        MLEN = 0x64
        
    };

};

#endif