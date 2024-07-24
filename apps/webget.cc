#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  // Your code here.

  // You will need to connect to the "http" service on
  // the computer whose name is in the "host" string,
  // then request the URL path given in the "path" string.

  // Then you'll need to print out everything the server sends back,
  // (not just one call to read() -- everything) until you reach
  // the "eof" (end of file).

  // 1. 创建socket对象
  // 2. 使用host实例化Address对象
  // 3. 使用Address对象连接socket
  TCPSocket socket;
  socket.connect( Address( host, "http" ) );

  // 4. 构造HTTP请求
  std::string request = "GET " + path + " HTTP/1.1\r\n";
  request += "Host: " + host + "\r\n";
  request += "Connection: close\r\n\r\n";

  // 5. 发送HTTP请求
  socket.write( request );

  // 6. 读取并输出服务器响应，在EOF时停止
  std::string response;
  while ( socket.eof() == false ) {
    socket.read( response );
    cout << response;
  }

  // 7. 关闭socket
  socket.close();

  /*   cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    cerr << "Warning: get_URL() has not been implemented yet.\n"; */
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
