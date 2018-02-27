#include "Val.hpp"

namespace Rill {

    VRef & VRef::deref () {
        if ( !this->val )
            return *this;
        if ( !( --*this->count ) ) {
            delete this->val;
            delete this->count;
            this->val = nullptr;
            this->count = nullptr;
        }
        return *this;
    }

    VRef & VRef::copy () {
        if ( !this->val || ( *( this->count ) == 1 ) )
            return *this;
        Val * newVal = this->val->clone();
        uint64_t * newCount = new uint64_t( 1 );
        this->deref();
        this->val = newVal;
        this->count = newCount;
        return *this;
    }

    VRef::VRef () : val( nullptr ), count( nullptr ) {

    }

    VRef::VRef ( const Val & val ) : val( val.clone() ), count( new uint64_t( 1 ) ) {

    }

    VRef::VRef ( const VRef & other ) : val( other.val ), count( other.count ) {
        ( *this->count )++;
    }

    VRef::~VRef () {
        this->deref();
    }

    VRef::operator bool () const {
        return this->val;
    }

    VRef & VRef::operator= ( const VRef & other ) {
        if ( this->val == other.val )
            return *this;
        this->deref();
        if ( !other ) {
            this->val = nullptr;
            this->count = nullptr;
        } else {
            this->val = other.val;
            this->count = other.count;
            (*this->count)++;
        }
        return *this;
    }

    VRef & VRef::operator= ( const Val & other ) {
        this->deref();
        this->val = other.clone();
        this->count = new size_t( 1 );
        (*this->count)++;
        return *this;
    }

    VRef & VRef::operator= ( const Val * other ) {
        if ( this->val == other )
            return *this;
        this->deref();
        if ( !other ) {
            this->val = nullptr;
            this->count = nullptr;
        } else {
            *this = *other;
        }
        return *this;
    }

    I64Val & VRef::asI64 () {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::I64 )
            throw InternalError( "Bad I64 cast." );
        this->copy();
        return *static_cast<I64Val*>( this->val );
    }

    DblVal & VRef::asDbl () {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::DBL )
            throw InternalError( "Bad Dbl cast." );
        this->copy();
        return *static_cast<DblVal*>( this->val );
    }

    StrVal & VRef::asStr () {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::STR )
            throw InternalError( "Bad Str cast." );
        this->copy();
        return *static_cast<StrVal*>( this->val );
    }

    VecVal & VRef::asVec () {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::VEC )
            throw InternalError( "Bad Vec cast." );
        this->copy();
        return *static_cast<VecVal*>( this->val );
    }

    LstVal & VRef::asLst () {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::LST )
            throw InternalError( "Bad Lst cast." );
        this->copy();
        return *static_cast<LstVal*>( this->val );
    }

    MapVal & VRef::asMap () {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::MAP )
            throw InternalError( "Bad Map cast." );
        this->copy();
        return *static_cast<MapVal*>( this->val );
    }

    const I64Val & VRef::asI64 () const {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::I64 )
            throw InternalError( "Bad I64 cast." );
        return *static_cast<I64Val*>( this->val );
    }

    const DblVal & VRef::asDbl () const {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::DBL )
            throw InternalError( "Bad Dbl cast." );
        return *static_cast<DblVal*>( this->val );
    }

    const StrVal & VRef::asStr () const {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::STR )
            throw InternalError( "Bad Str cast." );
        return *static_cast<StrVal*>( this->val );
    }

    const VecVal & VRef::asVec () const {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::VEC )
            throw InternalError( "Bad Vec cast." );
        return *static_cast<VecVal*>( this->val );
    }

    const LstVal & VRef::asLst () const {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::LST )
            throw InternalError( "Bad Lst cast." );
        return *static_cast<LstVal*>( this->val );
    }

    const MapVal & VRef::asMap () const {
        if ( !this->val )
            throw InternalError( "Null VRef dereference." );
        if ( this->val->getType() != Val::Type::MAP )
            throw InternalError( "Bad Map cast." );
        return *static_cast<MapVal*>( this->val );
    }

    Val * I64Val::clone () const {
        return new I64Val( *this );
    }

    I64Val::I64Val () : i( 0 ) {

    }

    I64Val::I64Val ( int64_t i ) : i( i ) {

    }

    I64Val::I64Val ( const I64Val & other ) : i( other.i ) {

    }

    I64Val::operator int64_t & () {
        return this->i;
    }

    Val::Type I64Val::getType () const {
        return Val::Type::I64;
    }

    String I64Val::toString () const {
        return ""; // TODO: not this
    }

    Val * DblVal::clone () const {
        return new DblVal( *this );
    }

    DblVal::DblVal () : d( 0 ) {

    }

    DblVal::DblVal ( double d ) : d( d ) {

    }

    DblVal::DblVal ( const DblVal & other ) : d( other.d ) {

    }

    double & DblVal::operator()() {
        return this->d;
    }

    Val::Type DblVal::getType () const {
        return Val::Type::DBL;
    }

    String DblVal::toString () const {
        return ""; // TODO: not this
    }

    Val * StrVal::clone () const {
        return new StrVal( *this );
    }

    StrVal::StrVal () : String() {

    }

    StrVal::StrVal ( const String & other ) : String( other ) {

    }

    StrVal::StrVal ( const char * cstr ) : String( cstr ) {

    }

    Val::Type StrVal::getType () const {
        return Val::Type::STR;
    }

    String StrVal::toString () const {
        return *this;
    }

    Val * LstVal::clone () const {
        return new LstVal( *this );
    }

    LstVal::LstVal () : List<VRef>() {

    }

    LstVal::LstVal ( const List<VRef> & other ) : List<VRef>( other ) {

    }

    Val::Type LstVal::getType () const {
        return Val::Type::LST;
    }

    String LstVal::toString () const {
        return ""; // TODO: not this
    }

    Val * VecVal::clone () const {
        return new VecVal( *this );
    }

    VecVal::VecVal () : Vector<VRef>() {

    }

    VecVal::VecVal ( const Vector<VRef> & other ) : Vector<VRef>( other ) {

    }

    Val::Type VecVal::getType () const {
        return Val::Type::VEC;
    }

    String VecVal::toString () const {
        return ""; // TODO: not this
    }

    Val * MapVal::clone () const {
        return new MapVal( *this );
    }

    MapVal::MapVal () : Map<VRef>() {

    }

    MapVal::MapVal ( const Map<VRef> & other ) : Map<VRef>( *this ) {

    }

    Val::Type MapVal::getType () const {
        return Val::Type::MAP;
    }

    String MapVal::toString () const {
        return ""; // TODO: not this
    }

};
