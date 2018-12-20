#include "rval/rnil.h"
#include "rval/rval.h"

RVal rnil () {
    RVal nil;
    nil.info = RVT_NIL;
    nil.uxx = 0;
    return nil;
}
