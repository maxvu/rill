#ifndef RILL_EXTENSION_TYPE
#define RILL_EXTENSION_TYPE

namespace rill {
namespace vm {

    class extension_type {

        protected:
        void * (*_clone)(void*);
        void (*_destroy)(void*);
        int (*_cycles_to)(void*, const rval&);
        int (*_equals)(void*, const rval&);
        string (*_to_string)(void*);

        public:

        extension_type(
            void * (*clone)(void*),
            void (*destroy)(void*),
            int (*cycles_to)(void*, rval*),
            int (*equals)(void*, rval*),
            string (*to_string)(void*)
        );

        void * clone ( void * object );
        bool cycles_to ( void * object, const rval & val );
        bool equals ( void * object, const rval & val );
        void destroy ( void * object );
        string to_string ( void * object );

    };

}
}

#endif
