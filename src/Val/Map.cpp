#include "Val/Buf.hpp"
#include "Val/Map.hpp"

namespace Rill {

void Map::Slot::swap ( Slot & a, Slot & b ) {
    Slot tmp;
    tmp.key = a.key;
    tmp.val = a.val;
    a.key = b.key;
    a.val = b.val;
    b.key = tmp.key;
    b.val = tmp.val;
}

bool Map::Slot::isVacant () const {
    return this->key.isNil();
}

size_t Map::hash_a ( const Buf & key ) const {
    size_t hash = 0; // sdbm
    size_t n = key.length();
    const BufBytesView & asBytes = key.asBytes();
    for ( size_t i = 0; i < n; i++ )
        hash = asBytes[ i ] + ( hash << 6 ) + ( hash << 16 ) - hash;
    return ( hash % this->cap / 4 ) + ( this->cap / 4 ) * 0;
}

size_t Map::hash_b ( const Buf & key ) const {
    size_t hash = 5381; // djb
    size_t n = key.length();
    const BufBytesView & asBytes = key.asBytes();
    for ( size_t i = 0; i < n; i++ )
        hash = ( hash << 5 ) + hash + asBytes[ i ];
    return ( hash % this->cap / 4 ) + ( this->cap / 4 ) * 1;
}

size_t Map::hash_c ( const Buf & key ) const {
    size_t hash = 56923; // hand-rolled
    size_t n = key.length();
    const BufBytesView & asBytes = key.asBytes();
    for ( size_t i = 0; i < n; i++ )
        hash = ( hash << 7 ) ^ ( hash - asBytes[ i ] );
    return ( hash % this->cap / 4 ) + ( this->cap / 4 ) * 2;
}

size_t Map::hash_d ( const Buf & key ) const {
    size_t hash = 77317; // one-at-a-time
    size_t n = key.length();
    const BufBytesView & asBytes = key.asBytes();
    for ( size_t i = 0; i < n; i++ )
        hash = ( ( hash << 10 ) ^ ( hash >> 6 ) ) + asBytes[ i ];
    return ( hash % this->cap / 4 ) + ( this->cap / 4 ) * 3;
}

Map & Map::resize ( size_t new_size ) {
    Map tmp( new_size );
    for ( auto it = this->begin(); it; it++ )
        tmp.set( it.key(), it.val() );
    delete[] this->slots;
    this->slots = tmp.slots;
    this->cap = tmp.cap;
    tmp.slots = nullptr;
    return *this;
}

Map::Map () : Map( RILL_VAL_MAP_DEFAULTSIZE ) {

}

Map::Map ( size_t init_cap ) {
    if ( init_cap < RILL_VAL_MAP_MINSIZE )
        init_cap = RILL_VAL_MAP_MINSIZE;
    init_cap += ( 4 - ( init_cap % 4 ) );
    this->slots = new Map::Slot[ init_cap ];
    this->occ = 0;
    this->cap = init_cap;
}

Map::Map ( const Map & other ) : Map( other.cap ) {
    *this = other;
}

Map::~Map () {
    if ( this->slots )
        delete[] this->slots;
}

Val & Map::get ( const Buf & key ) const {

    {
        Slot & slot = this->slots[ this->hash_a( key ) ];
        if ( slot.key == key )
            return slot.val;
    }
    {
        Slot & slot = this->slots[ this->hash_b( key ) ];
        if ( slot.key == key )
            return slot.val;
    }
    {
        Slot & slot = this->slots[ this->hash_c( key ) ];
        if ( slot.key == key )
            return slot.val;
    }
    {
        Slot & slot = this->slots[ this->hash_d( key ) ];
        if ( slot.key == key )
            return slot.val;
    }

    throw std::runtime_error( "Invalid Map access." );

}

Map & Map::set ( const Buf & key, const Val & val ) {

    if ( Val & hit = this->get( key ) ) {
        hit = val;
        return *this;
    }

    RILL_VAL_MAP_LOADFN( this->occ + 1, this->cap ) > RILL_VAL_MAP_MAXLOAD
        ? this->resize( this->cap * RILL_VAL_MAP_GROWTHC ), 0
        : 1 ;

    Slot juggle;
    Slot::swap( juggle, this->slots[ this->hash_a( key ) ] );

    if ( juggle.isVacant() ) {
        this->occ++;
        return *this;
    }

    while ( juggle.key != key ) {

        Slot::swap( juggle, this->slots[ this->hash_b( key ) ] );
        if ( juggle.isVacant() ) {
            this->occ++;
            return *this;
        }

        Slot::swap( juggle, this->slots[ this->hash_c( key ) ] );
        if ( juggle.isVacant() ) {
            this->occ++;
            return *this;
        }

        Slot::swap( juggle, this->slots[ this->hash_d( key ) ] );
        if ( juggle.isVacant() ) {
            this->occ++;
            return *this;
        }

        Slot::swap( juggle, this->slots[ this->hash_a( key ) ] );
        if ( juggle.isVacant() ) {
            this->occ++;
            return *this;
        }

    }

    return this->resize( ( double ) this->occ * RILL_VAL_MAP_GROWTHC );

}

bool Map::has ( const Buf & key ) const {

    {
        Slot & slot = this->slots[ this->hash_a( key ) ];
        if ( slot.key == key )
            return true;
    }
    {
        Slot & slot = this->slots[ this->hash_b( key ) ];
        if ( slot.key == key )
            return true;
    }
    {
        Slot & slot = this->slots[ this->hash_c( key ) ];
        if ( slot.key == key )
            return true;
    }
    {
        Slot & slot = this->slots[ this->hash_d( key ) ];
        if ( slot.key == key )
            return true;
    }

    return false;

}

Map & Map::unset ( const Buf & key ) {

    {
        Slot & slot = this->slots[ this->hash_a( key ) ];
        if ( slot.key == key ) {
            slot.key = Val();
            slot.val = Val();
            this->occ--;
        }
    }
    {
        Slot & slot = this->slots[ this->hash_b( key ) ];
        if ( slot.key == key ) {
            slot.key = Val();
            slot.val = Val();
            this->occ--;
        }
    }
    {
        Slot & slot = this->slots[ this->hash_c( key ) ];
        if ( slot.key == key ) {
            slot.key = Val();
            slot.val = Val();
            this->occ--;
        }
    }
    {
        Slot & slot = this->slots[ this->hash_d( key ) ];
        if ( slot.key == key ) {
            slot.key = Val();
            slot.val = Val();
            this->occ--;
        }
    }

    return *this;

}

Map & Map::clear () {
    for ( auto it = this->begin(); it; it++ )
        it.remove();
    return *this;
}

size_t Map::size () const {
    return this->occ;
}

double Map::load () const {
    return RILL_VAL_MAP_LOADFN( this->occ, this->cap );
}

Map & Map::merge ( const Map & other ) {
    for ( ConstIter it = other.begin(); it++; it )
        this->set( it.key(), it.val() );
    return *this;
}

Val Map::keys () const {

}

Val Map::vals () const {

}

Map & Map::reserve ( size_t new_cap ) {
    if ( new_cap >= this->cap )
        return *this;
    return this->resize( new_cap );
}

Map & Map::compact () {
    size_t target = this->occ;
    if ( target < RILL_VAL_MAP_MINSIZE )
        target = RILL_VAL_MAP_MINSIZE;
    if ( target == this->cap )
        return *this;
    return this->resize( target );
}

Map::operator bool () const {
    return this->size();
}

Val Map::serialize () const {

}

Map::Iter::Iter ( Map & map ) : map( map ), pos( 0 ) {
    if ( map.slots[ 0 ].isVacant() )
        this->operator++(0);
}

Map::Iter & Map::Iter::operator++ (int) {
    while ( this->pos < map.cap && !map.slots[ pos ].isVacant() )
        pos++;
    return *this;
}

const Buf & Map::Iter::key () const {
    if ( !*this )
        throw std::runtime_error( "Bad Map::Iter access." );
    return this->map.slots[ this->pos ].key.asBuf();
}

Val & Map::Iter::val () {
    if ( !*this )
        throw std::runtime_error( "Bad Map::Iter access." );
    return this->map.slots[ this->pos ].val;
}

Map::Iter & Map::Iter::remove () {
    if ( !*this )
        throw std::runtime_error( "Bad Map::Iter access." );
    this->map.slots[ this->pos ] = Slot();
    this->map.occ--;
    return *this;
}

Map::Iter::operator bool () const {
    return this->pos < map.cap;
}

Map::ConstIter::ConstIter ( const Map & map ) : map( map ), pos( 0 ) {

}

Map::ConstIter & Map::ConstIter::operator++ (int) {
    while ( this->pos < map.cap && !map.slots[ pos ].isVacant() )
        pos++;
    return *this;
}

const Buf & Map::ConstIter::key () const {
    if ( !*this )
        throw std::runtime_error( "Bad Map::Iter access." );
    return this->map.slots[ this->pos ].key.asBuf();
}

const Val & Map::ConstIter::val () {
    if ( !*this )
        throw std::runtime_error( "Bad Map::Iter access." );
    return this->map.slots[ this->pos ].val;
}

Map::ConstIter::operator bool () const {
    return this->pos < map.cap;
}

Map::Iter Map::begin () {
    return Iter( *this );
}

Map::ConstIter Map::begin () const {
    return ConstIter( *this );
}

}
