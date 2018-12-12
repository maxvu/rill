#include "Val/Buf.hpp"

namespace Rill {

Buf::Buf () {

}

Buf::Buf ( size_t initial_capacity ) {

}

Buf::Buf ( const Buf & other ) {

}

Buf::~Buf () {

}

Val & Buf::lease () {

}

int Buf::release () {

}

Val & Buf::exclude () {

}

Val * Buf::clone () const {

}

operator bool () const {

}

bool Buf::containsRef ( const Val * needle ) {

}

size_t Buf::length () const {

}

size_t Buf::capacity () const {

}

Buf & Buf::reserve ( size_t min_capacity ) {

}

Buf & Buf::compact () {

}

operator uint8_t & () {

}

Buf::operator const uint8_t & () const {

}

Buf & Buf::operator= ( const Buf & other ) {

}

Buf & Buf::operator= ( const char * cstr ) {

}

Buf & Buf::operator+= ( const Buf & other ) {

}

Buf & Buf::operator+= ( const char * cstr ) {

}

bool Buf::operator== ( const Buf & other ) const {

}

bool Buf::operator== ( const char * cstr ) const {

}

Buf Buf::substr ( size_t start, size_t len ) const {

}

Buf & Buf::clear () {

}

}
