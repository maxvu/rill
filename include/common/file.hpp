#ifndef RILL_FILE
#define RILL_FILE

namespace rill {

    class file {

        protected:
        FILE *       _file;
        unsigned int _size;

        public:
        virtual operator bool () const =0;
        unsigned int size () const;
        void close ();

    };

    class input_file : public file {

        public:
        input_file ( const char * location );

        input_file & operator<< ( const string & data );
        operator bool () const =0;

    };

    class output_file : public file {

        public:
        output_file ( const char * location );

        string read_line ();
        operator bool () const =0;

        void close ();

    };

}

#endif
