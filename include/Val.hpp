#ifndef RILL_VAL
#define RILL_VAL

#include <cstdint>
#include <cstdio>

#include "Error.hpp"
#include "String.hpp"
#include "List.hpp"
#include "Map.hpp"

namespace Rill {

    class Val;
    class I64Val;
    class DblVal;
    class StrVal;
    class LstVal;
    class MapVal;

    class VRef {

        protected:

        Val * val;
        uint64_t * count;

        VRef & deref ();
        VRef & copy  ();

        public:

        VRef ( const Val & val );
        VRef ( const VRef & other );
        ~VRef ();

        I64Val & asI64 ();
        DblVal & asDbl ();
        StrVal & asStr ();
        LstVal & asLst ();
        MapVal & asMap ();

        const I64Val & asI64 () const;
        const DblVal & asDbl () const;
        const StrVal & asStr () const;
        const LstVal & asLst () const;
        const MapVal & asMap () const;

    };

    class Val {

        public:

        enum class Type : uint8_t {
            I64,
            DBL,
            STR,
            LST,
            MAP
        };

        protected:

        virtual Val * clone () const =0;

        public:

        friend class VRef;

        virtual ~Val() {}

        virtual Type getType () const =0;
        virtual String toString () const =0;

    };

    class I64Val : public Val {

        protected:

        int64_t i;

        Val * clone () const;

        public:

        I64Val ();
        I64Val ( int64_t i );
        I64Val ( const I64Val & other );

        operator int64_t & ();

        Val::Type getType () const;
        String toString () const;

    };

    class DblVal : public Val {

        protected:

        double d;

        Val * clone () const;

        public:

        DblVal ();
        DblVal ( double f );
        DblVal ( const DblVal & other );

        double & operator()();

        Type getType () const;
        String toString () const;

    };

    class StrVal : public Val, public String {

        protected:

        Val * clone () const;

        public:

        StrVal ();
        StrVal ( const String & other );
        StrVal ( const char * cstr );

        Type getType () const;
        String toString () const;

    };

    class LstVal : public Val, public List<VRef> {

        protected:

        Val * clone () const;

        public:

        LstVal ();
        LstVal ( const List<VRef> & other );

        Type getType () const;
        String toString () const;

    };

    class MapVal : public Val, public Map<VRef> {

        protected:

        Val * clone () const;

        public:

        MapVal ();
        MapVal ( const Map<VRef> & other );

        Type getType () const;
        String toString () const;

    };

};

#endif
