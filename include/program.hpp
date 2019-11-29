#ifndef RILL_PROGRAM
#ifndef RILL_PROGRAM

namespace rill {
    
    class program {
    
        protected:
            
        vector<unsigned char> _is; // instruction sequence
        vector<rval>          _ct; // constant table
        
        public:
            
        vm ( vector<unsigned char> & iq );
        
        vm & step ();
        vm & run ();
        
        
    
    };
    
}

#endif