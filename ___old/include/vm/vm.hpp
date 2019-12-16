#ifndef RILL_RVM
#define RILL_RVM

#include "vector.hpp"
#include "vm/rval.hpp"

namespace rill {
namespace vm {
    
    class vm {
        
        public:
            
        enum flag {
            HALT      = 0,
            INTERRUPT = 1
        };
    
        protected:
            
        unsigned long         _ip; // instruction pointer
        vector<unsigned char> _it; // instruction table
        vector<rval>          _ps; // primary data stack
        vector<rval>          _ss; // secondary data stack
        unsigned long         _fs; // flag set

        public:

        vm ( const vector<unsigned char> & it );
        
        vm & step ();
        vm & run ();
        
        const vector<unsigned char> & instructions () const;
        const vector<unsigned char> & constants () const;
        const vector<rval> & primary_stack () const;
        const vector<rval> & secondary_stack () const;
        const unsigned long & flags () const;
        
        vm & set_flag ( flag f, bool on );
        bool get_flag ( flag f );
    
    };
    
}
}

#endif