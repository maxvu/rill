#ifndef RILL_TUPLE
#define RILL_TUPLE

namespace rill {

    template <typename T, typename U> struct Tuple {

        T first;
        U second;

        Tuple ( T fst, U snd );

    };

}

#endif
