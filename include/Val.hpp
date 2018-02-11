#ifndef RILL_VAL
#define RILL_VAL

#include <cstdint>

#include "Ptr.hpp"
#include "String.hpp"
#include "List.hpp"
#include "Map.hpp"

namespace Rill {

    class Val {

        public:

        enum class Type : uint8_t {
            INT,
            FLT,
            STR,
            LST,
            MAP
        };

        protected:

        Type type;

        Val ( Type type );

        public:

        Type getType () const;

    };

    class IntVal : public Val {

        protected:

        int64_t i;

        public:

        IntVal ();
        IntVal ( int64_t i );
        IntVal ( const IntVal & other );

        int64_t & operator()();

    };

    class FltVal : public Val {

        protected:

        double f;

        public:

        FltVal ();
        FltVal ( double f );
        FltVal ( const FltVal & other );

        double & operator()();

    };

    class StrVal : public Val, public String {

        public:

        StrVal ();
        StrVal ( const String & other );
        StrVal ( const char * cstr );

    };

    typedef Ptr<Val> ValPtr;

    class LstVal : public Val, public List<ValPtr> {

        public:

        LstVal ();
        LstVal ( const List<ValPtr> & other );

    };

    class MapVal : public Val, public Map<ValPtr> {

        public:

        MapVal ();
        MapVal ( const Map<ValPtr> & other );

    };

};

#endif
