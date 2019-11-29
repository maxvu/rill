#ifndef RILL_REFCOUNTED
#define RILL_REFCOUNTED

namespace rill {
    
    class refcounted {
        
        protected:
            
        unsigned long _count;
        
        public:
            
        unsigned long & refcount ();
        
    };
    
}

#endif