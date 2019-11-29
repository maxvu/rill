#ifndef RILL_RVM
#ifndef RILL_RVM

namespace rill {
    
    class vm {
    
        protected:
            
        unsigned long   _ip; // instruction pointer
        vector<unsigned char> _iq; // instruction queue
        vector<rval>    _ds; // (primary) data stack
        vector<rval>    _ss; // secondary (data) stack
        unsigned long   _fs; // flag set
        
        public:
            
        vm ( vector<unsigned char> & iq );
        
        vm & step ();
        vm & run ();
        
        
    
    };
    
}

#endif