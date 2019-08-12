#ifndef RILL_EXTENSION
#define RILL_EXTENSION

#include "string.hpp"

namespace rill {

template <typename T> class extension_type {
    public:
    virtual const string & name () const =0;
    virtual T * clone ( extension_type * ) const =0;
    virtual T & operator= ( const T & other ) const =0;
    virtual bool operator== ( const T & other ) const =0;
    virtual bool operator!= ( const T & other ) const;
    virtual ~extension_type () const =0;
};

class extension_word {
    public:
    virtual const string & name () const =0;
    virtual void invoke ( runtime & vm ) =0;
};

class extension {
    public:
    virtual const string & name () const =0;
    virtual unsigned long () revision () const =0;
    virtual hashmap<string,extension_type> & types () const =0;
    virtual hashmap<string,extension_word> & words () const =0;
};

class extension_set {
    protected:
    hashmap<string,extension_type> _types;
    hashmap<string,extension_word> _words;
    vector<string>                 _type_seq;

    public:
    extension_set (
        hashmap<string,extension_type> types,
        hashmap<string,extension_word> words
    );

    const extension_type & get_type ( const string & name ) const;
    const extension_type & get_type ( unsigned long n ) const;
    const extension_word & get_word ( const string & name ) const;
};

class extension_manager {

    protected:
    hashmap<string,extension> _extensions;

    public:
    extension_manager ();

    extension_manager & add ( const extension & ext );
    extension_manager & remove ( const extension & ext );

    extension_set compile () const;
};

}
