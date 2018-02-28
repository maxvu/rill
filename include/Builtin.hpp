#ifndef RILL_BUILTIN
#define RILL_BUILTIN

namespace Rill {

    class Builtin {

        protected:

        String name;
        void ( *fn )( Vector<VRef> & stack );

        public:

        Builtin (
            const String & name,
            void ( *fn )( Vector<VRef> & stack )
        );
        Builtin ( const Builtin & other );

        const String & getName () const;
        Builtin & operator() ( Vector<VRef> & stack );

    };

};

#endif
