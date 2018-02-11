#include "Val.hpp"

namespace Rill {

    Val::Val ( Type type ) : type( type ) {

    }

    Val::Type Val::getType () const {
        return this->type;
    }

    IntVal::IntVal () : IntVal( 0 ) {

    }

    IntVal::IntVal ( int64_t i ) : Val( Val::Type::INT ), i( i ) {

    }

    IntVal::IntVal ( const IntVal & other ) : IntVal( other.i ) {

    }

    int64_t & IntVal::operator()() {
        return this->i;
    }

    FltVal::FltVal () : FltVal( 0.0 ) {

    }

    FltVal::FltVal ( double f ) : Val( Val::Type::FLT ), f( f ) {

    }

    FltVal::FltVal ( const FltVal & other ) : FltVal( other.f ) {

    }

    double & FltVal::operator()() {
        return this->f;
    }

    StrVal::StrVal () : Val( Val::Type::STR ), String() {

    }

    StrVal::StrVal (
        const String & other
    ) : Val( Val::Type::STR ), String( other ) {

    }

    StrVal::StrVal (
        const char * cstr
    ) : Val( Val::Type::STR ), String( cstr ) {

    }

    LstVal::LstVal () : Val( Val::Type::LST ), List<ValPtr>() {

    }

    LstVal::LstVal (
        const List<ValPtr> & other
    ) : Val( Val::Type::LST ), List<ValPtr>( other ) {

    }

    MapVal::MapVal () : Val( Val::Type::MAP ), Map<ValPtr>() {

    }

    MapVal::MapVal (
        const Map<ValPtr> & other
    ) : Val( Val::Type::MAP ), Map<ValPtr>( other ) {

    }

};
