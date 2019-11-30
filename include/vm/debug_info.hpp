#ifndef RILL_VM_DEBUG_INFO
#define RILL_VM_DEBUG_INFO

namespace rill {
namespace vm {

    class debug_entry {
        
        protected:
            
        unsigned long _line;
        unsigned long _offset;
        string        _file;
        string        _text;
        
        public:
        
    };

    class debug_info {
        
        vector<debug_entry> _entries;
        
    };
    
}
}

#endif