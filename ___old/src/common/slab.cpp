#include "slab.hpp"

namespace rill {

slab::slab ( unsigned long size ) : _buffer(  ) {

}

slab::slab ( const slab & other ) {

}

slab::slab ( slab && other ) {

}

slab::~slab () {

}

slab::operator T * () {

}

slab::operator const T * () const {

}

unsigned long slab::size () const {

}

slab<T> & slab::resize ( unsigned long new_size ) {

}

slab<T> & slab::operator= ( const slab & other ) {

}

slab<T> & slab::operator= ( slab && other ) {

}


}
