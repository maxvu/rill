#ifndef RILL_OBJECT
#define RILL_OBJECT

namespace rill {

    class source {
        vector<string> _lines;
    };

    class site {
        unsigned long _line;
        unsigned long _offset;
        string        _source_name;
    };

    class op {
        uint8_t _code;
        site *  _site;
    };

    class word {
        vector<op> _ops;
        site *     _site;
    };

    class object {
        hashmap<string,word>          _words;
        hashmap<string,source>        _sources;
        hashmap<string,unsigned long> _dependencies;
    };

}

#endif
