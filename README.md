# 🔁 TCP Echo Server and Client in C

A simple, low-level **TCP echo server and client** implementation in **C** using **POSIX socket APIs**. This project demonstrates how basic client-server communication works over TCP/IP using system-level networking calls on Linux or any POSIX-compliant OS.

---

## 📌 Overview

This project consists of:
- A **server** that listens on a TCP port (`8080` by default), accepts a client connection, and echoes back whatever message it receives.
- A **client** that connects to the server, sends user input, and displays the echoed response.

This is useful for:
- Learning **network programming** in C
- Understanding **sockets and POSIX system calls**
- Practicing debugging with `gdb`
- Building **embedded or telecom-ready** networking applications

---

## 🗂️ Project Structure

tcp_echo/
├── server.c # TCP Echo Server
├── client.c # TCP Echo Client
├── Makefile # Build system
└── README.md # Project documentation

## 🛠️ Build Instructions

Make sure you have GCC installed. Then:

```bash
git clone https://github.com/yourusername/tcp-echo.git
cd tcp-echo
make
```

``` bash 
./server #(Run the Server)
```

``` bash 
./client #(Run the Client)
```

🔧 How It Works
#Server Flow
Creates a socket using socket()

Binds it to an IP and port using bind()

Listens for incoming connections with listen()

Accepts a connection using accept()

Reads data from the client and sends it back using read() and send()

#Client Flow
Creates a socket

Connects to the server using connect()

Takes input from the user and sends it to the server

Reads the server’s response and prints it

All socket APIs follow POSIX standards, making this code portable across UNIX-like systems.

🔍 Debugging with gdb
Since the code is compiled with the -g flag (via Makefile), you can debug it easily:
```bash 
gdb ./server
(gdb) run
# After crash or breakpoint:
(gdb) bt     # Backtrace
(gdb) list   # Show source
(gdb) print buffer  # Inspect variables
```
