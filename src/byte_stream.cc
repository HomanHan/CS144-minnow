#include "byte_stream.hh"
#include <stdexcept>

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), bytes_popped_( 0 ), bytes_pushed_( 0 ), error_( false ), closed_( false ), buffer_( "" )
{}

bool Writer::is_closed() const
{
  // Your code here.
  return closed_;
}

void Writer::push( string data )
{
  // Your code here.
  // (void)data; // (void)data 并不会改变 data 的值或类型，它只是告诉编译器忽略 data
  // 的类型，即告诉编译器这个参数是故意未使用的。
  if ( is_closed() and data.size() > 0 ) {
    throw runtime_error( "pushed data after closed" );
    set_error();
  } else if ( has_error() ) {
    throw runtime_error( "Something went wrong" );
  }

  if ( available_capacity() < data.size() ) {
    data = data.substr( 0, available_capacity() );
  }
  buffer_ += data;
  bytes_pushed_ += data.size();
  return;
}

void Writer::close()
{
  // Your code here.
  closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return ( capacity_ - buffer_.size() );
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return ( bytes_popped() == bytes_pushed_ and closed_ and buffer_.empty() );
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return bytes_popped_;
}

string_view Reader::peek() const
{
  // Your code here.
  return string_view( buffer_ );
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  // (void)len;
  if ( buffer_.empty() or len == 0 ) {
    return;
  }

  len = len > buffer_.size() ? buffer_.size() : len;

  buffer_ = buffer_.substr( len, buffer_.size() );
  bytes_popped_ += len;

  return;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffer_.size();
}
