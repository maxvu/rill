#ifndef RILL_PACK_PACK
#define RILL_PACK_PACK

#include "debug_info/debug_info.hpp"

using debug_info = rill:debug_info::debug_info;

namespace rill {
namespace packer {

    class segment {

        public:

        virtual const string & type () const =0;
        virtual string data () const =0;

    };

    class header_segment {

        protected:

        string _version;

        public:

    };

    class info_segment {

        protected:

        string _title;
        string _version;
        string _author;
        string _license;

    };

    class bytecode_segment {

        protected:

        string codes;

    };

    class constants_segment {

        protected:

        vector<rval> _constants;

    };

    class debug_segment {

        protected:

        debug_info _info;

    };

    class link_segment {

        protected:



    };

    /*
        checksum
        version
        format
    */

    class reader {

        protected:

        const string & _input;

        public:

        operator bool () const;
        reader & next ();
        segment & current ();

    };

    class writer {

        protected:

        string & _output;

        public:

        writer & operator<< ( const segment & segment );
        string finish ();

    };

}
}

#endif
