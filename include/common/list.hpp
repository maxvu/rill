#ifndef RILL_LIST
#define RILL_LIST

namespace rill {

    template <typename T> List {

        protected:
            class Node {
                T value;
                Node * next;
            };

            Node * head;
            size_t len;

        public:
            List ();
            List ( const List & that );
            List ( List && that );
            ~List ();

            size_t length () const;
            List<T> & push ( const T & value );
            List<T> & pop ();

    };

}

#endif
