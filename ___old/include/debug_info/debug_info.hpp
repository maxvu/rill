#ifndef RILL_VM_DEBUG_INFO_DEBUG_INFO
#define RILL_VM_DEBUG_INFO_DEBUG_INFO

#include "map.hpp"
#include "maybe.hpp"
#include "serializable.hpp"

namespace rill {
namespace debug_info {

    class source_file {

        protected:

        map<unsigned long,string> _lines;

        public:

        source_file ();

        source_file add_line ( unsigned long number, const string & text );
        const string * get_line ( unsigned long number );

    };

    class source_entry {

        protected:

        string        _file;
        unsigned long _line;
        unsigned long _offset;

        public:

        source_entry (
            const string & file,
            unsigned long line,
            unsigned long offset
        );

        const string & file () const;
        unsigned long line () const;
        unsigned long offset () const;

    };

    class debug_info : public serializable<debug_info> {

        protected:

        map<string,source_file> _files;
        vector<source_entry>    _entries;

        public:

        debug_info ();

        debug_info & add_line (
            const string & filename,
            unsigned long line_number,
            const string & text
        );

        unsigned long add_entry (
            const string & filename,
            unsigned long line_number,
            unsigned long offset
        );

        maybe<source_line> get_line (
            const string & filename,
            unsigned long line_number
        );

        maybe<source_entry> get_entry (
            unsigned long entry_number
        );

    };

}
}

#endif
