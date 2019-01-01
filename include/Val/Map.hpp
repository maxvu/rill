#ifndef RILL_VAL_MAP
#define RILL_VAL_MAP

#include "Val/Val.hpp"

#include <cstddef>
#include <unordered_map>

namespace Rill {

class Map : public Refcounted {

    struct BufHash {

        size_t operator() ( const Buf & bufref ) const noexcept;

    };

    protected:

    std::unordered_map<Buf, Val, BufHash> pairs;

    public:

    Map ();
    Map ( const Map & other );
    ~Map ();

    Val get ( const Buf & key ) const;
    Map & set ( const Buf & key, const Val & val );
    bool has ( const Buf & key ) const;
    Map & unset ( const Buf & key );

    Map & merge ( const Map & other );

    Val keys () const;
    Val vals () const;

    Map & compact (); // no-op?
    operator bool () const;
    Val serialize () const;

};

}

#endif
