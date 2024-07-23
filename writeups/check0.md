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