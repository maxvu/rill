typedef enum rop {
    ROP_NOP,
    ROP_CALL,
    ROP_RETURN,
    ROP_JUMP,
    ROP_JUMPIF,

    ROP_ENIL,
    ROP_EZRO,
    ROP_EONE,
    ROP_EIMM,

    ROP_GNOT,
    ROP_GXOR,

    ROP_IADD,
    ROP_ISUB,
    ROP_IMUL,
    ROP_IDIV,
    ROP_IMOD,
    ROP_ISHL,
    ROP_ISHR,
    ROP_INEG,
    ROP_ICMP,
    ROP_I2U,
    ROP_I2F,

    ROP_UADD,
    ROP_USUB,
    ROP_UMUL,
    ROP_UDIV,
    ROP_UMOD,
    ROP_USHL,
    ROP_USHR,
    ROP_UCMP,
    ROP_UINV,
    ROP_UAND,
    ROP_UOR,
    ROP_UXOR,
    ROP_U2I,
    ROP_U2F,

    ROP_FADD,
    ROP_FSUB,
    ROP_FMUL,
    ROP_FDIV,
    ROP_FFLR,
    ROP_FCMP,
    ROP_FFNT,
    ROP_F2I,
    ROP_F2U,

    ROP_BNEW,
    ROP_BCAT,
    ROP_BLEN,

    ROP_LNEW,
    ROP_LCAT,
    ROP_LLEN,

    ROP_MNEW,
    ROP_MSET,
    ROP_MGET,
    ROP_MSIZ,
    ROP_MDEL,

    ROP_2PSH,
    ROP_2POP,

    ROP_IMAXV,
    ROP_M00,
    ROP_M01,
    ROP_M02,
    ROP_M03,
    ROP_M04,
    ROP_M05,
    ROP_M06,
    ROP_M07,
    ROP_M08,
    ROP_M09,
    ROP_M10,
    ROP_M11,
    ROP_M12,
    ROP_M13,
    ROP_M14,
    ROP_M15,
    ROP_M16,
    ROP_M17,
    ROP_M18,
    ROP_M19,
    ROP_M20,
    ROP_M21,
    ROP_M22,
    ROP_M23,
    ROP_M24,
    ROP_M25,
    ROP_M26,
    ROP_M27,
    ROP_M28,
    ROP_M29,
    ROP_M30,
    ROP_M31
} ROp;