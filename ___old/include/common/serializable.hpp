#ifndef RILL_SERIALIZABLE
#define RILL_SERIALIZABLE

namespace rill {

    template <typename T> class serializable {

        virtual string & serialize () const =0;

    };

}

#endif
