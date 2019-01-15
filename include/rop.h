#ifndef RILL_OPS
#define RILL_OPS

typedef enum rop {

    /* control flow ops */

    NOP  = 0,   // no operation
    CALL = 1,   // invoke subroutine ( % 4 or % 8 offset )
    RTRN = 2,   // end subroutine
    JUMP = 3,   // unconditional jump
    JMPT = 4,   // jump if TOS truthy
    JMPQ = 5,   // jump is TOS and TOS-1 equal
    NOT  = 6,   // logical NOT TOS and TOS-1
    XOR  = 7,   // logical XOR TOS and TOS-1

    /* signed integer ops */

    IADD = 8,   // addition
    ISUB = 9,   // subtraction
    IMUL = 10,  // multiplication
    IDIV = 11,  // division
    IMOD = 12,  // modulo
    ISFT = 13,  // bitwise-shift (positive goes right)
    INEG = 14,  // negate
    ICMP = 15,  // compare TOS and TOS-1
    IC2U = 16,  // convert to unsigned integer
    IC2F = 17,  // convert to floating-point

    /* unsigned integer ops */

    UADD = 18, // addition
    USUB = 19, // subtraction
    UMUL = 20, // multiplication
    UDIV = 21, // division
    USFT = 22, // bitwise shift (positive goes right)
    UCMP = 23, // compare TOS and TOS-1
    UINV = 24, // bitwise NOT
    UAND = 25, // bitwise AND
    UOR  = 26, // bitwise OR
    UXOR = 27, // bitwise XOR
    UC2I = 28, // convert to signed integer
    UC2F = 29, // convert to floating-point

    /* floating-point ops */

    FADD = 30, // addition
    FSUB = 31, // subtraction
    FMUL = 32, // multiplication
    FDIV = 33, // divition
    FFLR = 34, // floor
    FCMP = 35, // compare TOS and TOS-1
    FFNT = 36, // is finite
    FC2I = 37, // convert to signed integer
    FC2U = 38, // convert to unsigned integer

    /* buffer ops */

    BNEW = 39, // create new, empty buffer
    BCAT = 40, // concatenate TOS and TOS-1
    BLEN = 41, // length
    BCMP = 42, // compare TOS and TOS-1

    /* vector ops */

    VNEW = 43, // create new, empty vector
    VCAT = 44, // concatenate TOS and TOS-1
    VLEN = 45, // length
    VPSH = 46, // push
    VPOP = 47, // pop
    VSET = 48, // set element (vec, index, item)
    VGET = 49, // get element (vec, index)

    /* map ops */

    MNEW = 50, // create new, empty map
    MSET = 51, // set element (map, key, item)
    MGET = 52, // get element (map, key)
    MSIZ = 53, // size
    MDEL = 54, // remove elemtn (map, key)

    /* stack manipulation ops */

    DRP  = 55, // drop TOS
    DUP  = 56, // duplicate TOS
    SWP  = 57, // swap positions of TOS and TOS-1
    OVR  = 58, // copy TOS-1 atop TOS
    ROT  = 59, // rotate the top three elements (tuck TOS under TOS-1 and TOS-2)
    RRT  = 60, // reverse-rotate, inverse fof ROT
    DRP2 = 61, // drop TOS and TOS-1
    DUP2 = 62, // duplicate TOS and TOS-1
    SWP2 = 63, // swap positions of TOS and TOS-1 with those of TOS-2 and TOS-3
    OVR2 = 64, // copy TOS-2 and TOS-3 atop TOS
    BURY = 65, // overwrite an arbitrary stack element (index, val)
    DIG  = 66, // retrieve an arbitrary stack element (index)
    SPSN = 67, // side-stack push N (index)
    SPPN = 68, // side-stack pop N (index)

    /* immediate ops */

    DU00 = 69,  // load immediate value 00
    DU01 = 70,  // load immediate value 01
    DU00 = 71,  // load immediate value 00
    DU01 = 72,  // load immediate value 01
    DU02 = 73,  // load immediate value 02
    DU03 = 74,  // load immediate value 03
    DU04 = 75,  // load immediate value 04
    DU05 = 76,  // load immediate value 05
    DU06 = 77,  // load immediate value 06
    DU07 = 78,  // load immediate value 07
    DU08 = 79,  // load immediate value 08
    DU09 = 80,  // load immediate value 09
    DU10 = 81,  // load immediate value 10
    DU13 = 82,  // load immediate value 13
    DU14 = 83,  // load immediate value 14
    DU15 = 84,  // load immediate value 15
    DU16 = 85,  // load immediate value 16
    DU17 = 86,  // load immediate value 17
    DU18 = 87,  // load immediate value 18
    DU19 = 88,  // load immediate value 19
    DU20 = 89,  // load immediate value 20
    DU21 = 90,  // load immediate value 21
    DU22 = 91,  // load immediate value 22
    DU23 = 92,  // load immediate value 23
    DU24 = 93,  // load immediate value 24
    DU25 = 94,  // load immediate value 25
    DU26 = 95,  // load immediate value 26
    DU27 = 96,  // load immediate value 27
    DU28 = 97,  // load immediate value 28
    DU29 = 98,  // load immediate value 29
    DU30 = 99,  // load immediate value 30
    DU31 = 100, // load immediate value 31
    DNIL = 101, // load immediate nil
    DPK4 = 102, // pack four unsigned values into a 20-bit unsigned integer
    DPK8 = 103, // pack eight unsigned values into a 40-bit unsigned integer
    LOAD = 104, // load constant table entry (index)
    SYSC = 105, // invoke native function

} ROp;

#endif
