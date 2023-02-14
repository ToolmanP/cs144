#include "byte_stream.hh"

#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity): remaining(capacity),nreads(0),nwrites(0){
    this->buf = std::string();
    this->_input_ended = false;
    this->_error = false;
}

size_t ByteStream::write(const string &data) {
    size_t ret = std::min(this->remaining,data.length());
    this->buf += data.substr(0,ret);
    this->remaining -= ret;
    this->nwrites += ret;
    return ret;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return this->buf.substr(0,std::min(len,this->buf.length()));
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    auto npos = std::min(len,this->buf.length());
    auto ret = this->buf.substr(0,npos);
    this->nreads += npos;
    this->remaining += npos;
    this->buf.replace(0,npos,"");
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    auto ret = this->peek_output(len);
    this->pop_output(len);
    return ret;
}

void ByteStream::end_input() {
    this->_input_ended = true;
}

bool ByteStream::input_ended() const { return this->_input_ended; }

size_t ByteStream::buffer_size() const { return this->buf.length(); }

bool ByteStream::buffer_empty() const { return this->buf.empty(); }

bool ByteStream::eof() const { return this->_input_ended && this->buf.empty();}

size_t ByteStream::bytes_written() const { return this->nwrites; }

size_t ByteStream::bytes_read() const { return this->nreads; }

size_t ByteStream::remaining_capacity() const { return this->remaining; }
