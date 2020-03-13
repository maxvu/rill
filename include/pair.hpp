#ifndef RILL_PAIR
#define RILL_PAIR

namespace rill {

    template <typename T1, typename T2>
    class pair {

        protected:
            T1 _fst;
            T2 _snd;

        public:
            pair ( const T1 & fst, const T2 & snd );

            T1 & first ();
            const T1 & first () const;

            T2 & second ();
            const T2 & second () const;

    };

}

#endif
