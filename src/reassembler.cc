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
    throw runtime_error( "Something went wrong" );
  }

  size_t size_data = data.size();
  if ( first_index == prev_index_ ) {                            // 如果 first_index 是连续于 prev_index_ 的
    if ( free_pending_data( first_index, (size_t)size_data ) ) { // 腾出空间，push
      output_.writer().push( data );
      prev_index_ += (uint64_t)size_data;
    }

    // 将 pending_data_ 中的合适数据写入 output_
    for ( auto it = pending_data_.begin(); it != pending_data_.end() and it->first == prev_index_; ) {
      output_.writer().push( it->second );
      prev_index_ += (uint64_t)it->second.size();
      it = pending_data_.erase( it );
    }
  } else if ( first_index > prev_index_ ) {
    if ( free_pending_data( first_index, (size_t)size_data ) ) { // 依 index 决定是否保留
      pending_data_.insert( make_pair( first_index, data ) );
    }
  }

  if ( is_last_substring ) {
    output_.writer().close();
  }

  return;
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  uint64_t bytes_pending = 0;
  for ( const auto& entry : pending_data_ ) {
    bytes_pending += entry.second.size();
  }

  return bytes_pending;
}

bool Reassembler::free_pending_data( uint64_t index, size_t size_data )
{
  // 删除 pending_data_ 中的index偏大的数据，使 size_data + pending_data_.size() <= available_capacity
  if ( (uint64_t)size_data + bytes_pending() <= writer().available_capacity() ) {
    return true;
  }

  auto it = pending_data_.rbegin();
  uint64_t current_size = bytes_pending();
  while ( ( it != pending_data_.rend() ) and ( !pending_data_.empty() )
          and ( uint64_t ) size_data + current_size >= writer().available_capacity() ) {
    if ( index > it->first ) {
      break;
    }
    current_size -= it->second.size();
    // 删除 it 指向数据
    it = map<uint64_t, std::string>::reverse_iterator( pending_data_.erase( std::next( it ).base() ) );
  }

  return (uint64_t)size_data + current_size <= writer().available_capacity();
}
