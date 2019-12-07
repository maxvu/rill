#ifndef RILL_PAIR
#define RILL_PAIR

namespace rill {

    template <
        typename T1,
        typename T2 = void,
        typename T3 = void,
        typename T4 = void,
        typename T5 = void,
        typename T6 = void,
        typename T7 = void,
        typename T8 = void
    > class tuple;

    template <typename T1, typename T2> class pair {

        pair ( T1 first, T2 second );
        pair ( const pair<T1,T2> & other );
        pair ( pair<T1,T2> && other );

        pair<T1, T2> & operator= ( const pair<T1,T2> & other );
        pair<T1, T2> & operator= ( pair<T1,T2> && other );

        bool operator== ( const pair<T1,T2> & other );

        T1 & first ();
        const T1 & first () const;

        T2 & second ();
        const T2 & second () const;

        pair swap () const;

    };

}

#endif
