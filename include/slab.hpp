#ifndef RILL_SLAB
#define RILL_SLAB

namespace rill {

     template <typename T> class slab {
        
        public:
            
        static T * create ( T * slab, unsigned long n );
        static T * resize ( T * slab, unsigned long new_size );
        static void destroy ( T * slab );
        
    };

}

#endif