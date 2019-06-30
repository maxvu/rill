#ifndef RILL_BLOCK
#define RILL_BLOCK

namespace rill {
namespace builder {

    class block {};

    class segment {
        uint8_t _ops[4];

        segment ();
        segment (
            uint8_t a,
            uint8_t b,
            uint8_t c,
            uint8_t d,
        );
        segment & operator<< ( uint8_t op );
    };

    class block {

        public:
        virtual const string & build ();

    };

    class placeholder_block {

    };

    class jump_block {

        block & target;

    };

    class conditional_block {

        block & truthy;
        block & falsy;

    };

    class loop_block {

        block & body;

    };

    class load_imm_int_block {
        public:
        load_imm_int_block ( int i );
    };

    class load_imm_uint_block {
        public:
        load_imm_uint_block ( unsigned int i );
    };

    class load_imm_float_block {
        public:
        load_imm_float_block ( float i );
    };

    class load_const_block {
        public:
        load_const_block ( const rval & const_val );
    };

}
}

#endif
