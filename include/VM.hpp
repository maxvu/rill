#ifndef RILL_VM
#define RILL_VM

#include <vector>

#include "Op.h"

namespace Rill {

    class VM {
    
        protected:

        std::vector<Op> ops;
        uint64_t pc;
        // val stack ds
        
        public:
        
        VM ();
        

    };

};

#endif