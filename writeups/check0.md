Checkpoint 0 Writeup
====================

My name: Homan

My SUNet ID: 22122811

I collaborated with: [list sunetids here]

I would like to credit/thank these classmates for their help: [list sunetids here]

This lab took me about [n] hours to do. I [did/did not] attend the lab session.

My secret code from section 2.1 was: [code here]

I was surprised by or edified to learn that: [describe]

Describe ByteStream implementation. [Describe data structures and
approach taken. Describe alternative designs considered or tested.
Describe benefits and weaknesses of your design compared with
alternatives -- perhaps in terms of simplicity/complexity, risk of
bugs, asymptotic performance, empirical performance, required
implementation time and difficulty, and other factors. Include any
measurements if applicable.]

- Optional: I had unexpected difficulty with: [describe]

- Optional: I think you could make this lab better by: [describe]

- Optional: I'm not sure about: [describe]

- Optional: I contributed a new test case that catches a plausible bug
  not otherwise caught: [provide Pull Request URL]

---

# Notes

## 2 Network By Hand

### 2.1 Fetch a Web page

#### code

```shell
telnet cs144.keithw.org http

GET /lab0/22122811 HTTP/1.1
Host: cs144.keithw.org
Connection: close
```

#### Result

- SUNet ID = `22122811`
- `X-Your-Code-Is = 171510`

```shell
Trying 104.196.238.229...
Connected to cs144.keithw.org.
Escape character is '^]'.
GET /lab0/22122811 HTTP/1.1
Host: cs144.keithw.org
Connection: close

HTTP/1.1 200 OK
Date: Sat, 13 Jul 2024 09:26:30 GMT
Server: Apache
X-You-Said-Your-SunetID-Was: 22122811
X-Your-Code-Is: 171510
Content-length: 112
Vary: Accept-Encoding
Connection: close
Content-Type: text/plain

Hello! You told us that your SUNet ID was "22122811". Please see the HTTP headers (above) for your secret code.
Connection closed by foreign host.
```

### 2.2 Send yourself an email

```shell
telnet 148.163.153.234 smtp
HELO mycomputer.stanford.edu
MAIL FROM: sunetid@stanford.edu
RCPT TO: sunetid@stanford.edu

```

Mjc2OTA5MjUyMA==

Uk44Q2JJOEZwVGlEZUZ1UA==**RN8CbI8FpTiDeFuP**

## 3 Writing a network program using an OS stream socket

### 3.1 关于socket和filedescriptor的理解

TODO…

### 3.2 实现思路

`void get_URL( const string& host, const string& path )`

1. **解析主机名**

DNS解析，这里直接使用host实例化Address类即可

2. **创建socket**

函数调用（如 `socket()`）在客户端创建一个套接字。对于 HTTP 请求，通常使用 TCP 套接字，因为 HTTP 是基于 TCP 的协议。

3. **connect**

直接调用`socket.connect()`

4. **构建并发送HTTP请求**

```http
GET {path} HTTP/1.1
Host: {host}
Connection: close

```

后使用`socket.write()`发送请求即可。

注意每一行最后应该都是`\r\n`，并且最后应有一空行

5. **接受响应**

使用`socket.read()`从socket中不断读取服务器响应，并在EOF时停止

6. **关闭连接**

`socket.close()`

## 4. An in-memory reliable byte stream

### 4.1 Result

```shell
Test project /home/homan/Downloads/CS144/workspace/CS144-minnow/build
      Start  1: compile with bug-checkers
 1/10 Test  #1: compile with bug-checkers ........   Passed    0.14 sec
      Start  2: t_webget
 2/10 Test  #2: t_webget .........................   Passed    1.08 sec
      Start  3: byte_stream_basics
 3/10 Test  #3: byte_stream_basics ...............   Passed    0.01 sec
      Start  4: byte_stream_capacity
 4/10 Test  #4: byte_stream_capacity .............   Passed    0.01 sec
      Start  5: byte_stream_one_write
 5/10 Test  #5: byte_stream_one_write ............   Passed    0.01 sec
      Start  6: byte_stream_two_writes
 6/10 Test  #6: byte_stream_two_writes ...........   Passed    0.01 sec
      Start  7: byte_stream_many_writes
 7/10 Test  #7: byte_stream_many_writes ..........   Passed    0.03 sec
      Start  8: byte_stream_stress_test
 8/10 Test  #8: byte_stream_stress_test ..........   Passed    0.01 sec
      Start 37: compile with optimization
 9/10 Test #37: compile with optimization ........   Passed    0.08 sec
      Start 38: byte_stream_speed_test
             ByteStream throughput: 1.62 Gbit/s
10/10 Test #38: byte_stream_speed_test ...........   Passed    0.11 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) =   1.49 sec
Built target check0
```