#include "reassembler.hh"
#include <stdexcept>

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  /*   (void)first_index;
    (void)data;
    (void)is_last_substring; */

  if ( writer().is_closed() ) {
    throw runtime_error( "inserted data after closed" );
    output_.set_error();
  } else if ( output_.has_error() ) {
    throw runtime_error( "Something went wrong in output_" );
  } else if ( first_index >= ( prev_index_ + writer().available_capacity() ) ) {
    // throw runtime_error( "first_index lies beyond memory capacity" );
    return;
  }

  if ( is_last_substring ) {
    _eof = true;
  }

  if ( _eof and bytes_pending_ == 0 and data.size() == 0 ) {
    output_.writer().close();
  }

  if ( first_index < prev_index_ and first_index + data.size() - 1 >= prev_index_ ) {
    data = data.substr( size_t( prev_index_ - first_index ) );
    first_index = prev_index_;
  }

  size_t size_data = data.size();

  size_t pending_capacity = writer().available_capacity();
  uint64_t offset = first_index - prev_index_;
  // 此处的 i 直接指向 pending_data_ 的下标
  for ( uint64_t i = first_index - prev_index_; i < pending_capacity and i < ( size_data + offset ); i++ ) {
    if ( pending_flag_[i] == true ) {
      continue;
    }
    pending_data_[i] = data[i - offset];
    pending_flag_[i] = true;
    bytes_pending_++;
  }

  // 从 pending_data_ 中取出数据写入 output_
  string out;
  while ( pending_flag_[0] == true and !pending_data_.empty() and pending_data_.front() ) {
    out += pending_data_.front();
    pending_data_.pop_front();
    pending_flag_.pop_front();
    pending_data_.push_back( '\0' );
    pending_flag_.push_back( false );
    bytes_pending_--;
  }
  if ( out.size() > 0 ) {
    output_.writer().push( out );
    prev_index_ = writer().bytes_pushed();
  }

  if ( _eof and bytes_pending_ == 0 ) {
    output_.writer().close();
  }

  return;
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return bytes_pending_;
}
