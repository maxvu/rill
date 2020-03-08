#ifndef RILL_RVAL
#define RILL_RVAL

namespace rill {
namespace vm {

    template <typename V> class Val {

        public:

            enum Type {
                NIL = 0,
                NUM = 1,
                STR = 2,
                VEC = 3,
                MAP = 4,
                PIP = 6,
                EXT = 7
            };

        protected:
            Val ( Type type, size_t tag = 0 );

            size_t head;
            size_t ref;

        public:
            Type type () const;
            size_t tag () const;
            ~Val ();

            V & lease ();
            void release ();

            size_t type () const;
            bool cycles_to ( const Val * that ) const;
            bool operator== ( const Val & that ) const;
            V & compact ();

            template <Val V2> const V2 & as ();
            template <Val V2> V2 & as () const;

    };

    class NumVal : public Val<NumVal> {

        protected:

            union {
                unsigned long uxx;
                long          ixx;
                double        fxx;
            };

        public:
            NumVal ();
            NumVal ( unsigned long u );
            NumVal ( long i );
            NumVal ( double f );
            ~NumVal ();

            unsigned long & u ();
            long & i ();
            double & f ();

            const unsigned long & u () const;
            const long & i () const;
            const double & f () const;

    };

    class StrVal : public Val<StrVal>, public String {

        public:
            StrVal ();
            StrVal ( const char * cstr );
            StrVal ( const StrVal & that );
            StrVal ( const String & that );
            StrVal ( StrVal && that );
            StrVal & operator= ( const StrVal & that );
            StrVal & operator= ( StrVal && that );

    };

    class VecVal : public Val<VecVal>, public Vector<Val*> {

        public:
            VecVal ();
            VecVal ( const VecVal & that );
            VecVal ( VecVal && that );
            VecVal ( const Vector<Val*> & that );
            VecVal ( Vector<Val*> && that );
            VecVal ( std::initializer_list<Val*> init_list );
            VecVal & operator= ( const VecVal & that );
            VecVal & operator= ( VecVal && that );
            bool cycles_to ( Val * that ) const;

    };

    class MapVal : public Val<MapVal>, public Map<StrVal*,Val*> {

        public:
            MapVal ();
            MapVal ( const MapVal & that );
            MapVal ( MapVal && that );
            MapVal ( const Map<StrVal*,Val*> & that );
            MapVal ( Map<StrVal*,Val*> && that );
            MapVal ( std::initialzer_list<Tuple<StrVal*,Val*>> init_list );
            MapVal & operator= ( const MapVal & that );
            MapVal & operator= ( MapVal && that );
            bool cycles_to ( Val * that ) const;

    };

    class ExtensionType : public Val<ExtensionType> {

        public:
            virtual ~ExtensionType () =0;

    };

    class ExtVal : public Val<ExtVal>, public ExtensionType {

    };

}
}

#endif
