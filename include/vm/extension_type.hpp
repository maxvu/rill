#ifndef RILL_EXTENSION_TYPE
#define RILL_EXTENSION_TYPE

namespace rill {
namespace vm {

    template <typename E> class extension_type {

        virtual ~extension_type () =0;
        virtual E * clone () =0;
        virtual bool contains_ref ( const rref & ref );
        virtual bool operator== ( const E & other ) const;
        virtual bool operator!= ( const E & other ) const;
        virtual string to_string () const;

    };

}
}

#endif
