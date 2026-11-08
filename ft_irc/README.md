*This project has been created as part of the 42 curriculum by kmizuki, hfuki, ayamada*
# ft_irc
### Description
**ft_irc** is a custom implementation of an IRC (Internet Relay Chat) server written in C++98, built entirely from scratch without any external libraries.

The goal of this project is to understand the internals of a real-world network protocol by implementing a server capable of handling multiple clients simultaneously, in a fully non-blocking way, using **a single poll()** loop for all I/O operations (accepting connections, reading, and writing).

The server does not implement an IRC client, nor server-to-server communication (no IRC network). It is meant to be used with an existing, official IRC client as the reference client.

### Implemented features
* TCP/IP (v4) socket handling with a single `poll()` loop
* Non-blocking I/O on every file descriptor
* Password-protected server authentication (`PASS`)
* Nickname and username registration (`NICK`, `USER`)
* Channel management (`JOIN`, `PART`, `PRIVMSG` to channels/users)
* Message broadcasting to all channel members
* Regular users vs. channel operators
* Operator-only commands:
    * `KICK` — eject a client from a channel
    * `INVITE` — invite a client to a channel
    * `TOPIC` — view/change the channel topic
    * `MODE` — change channel modes:
        * `i` — invite-only channel
        * `t` — restrict TOPIC changes to operators
        * `k` — set/remove channel key (password)
        * `o` — give/take operator privilege
        * `l` — set/remove the user limit
* Handling of partial / fragmented TCP packets (commands are buffered and reassembled before parsing)

### Instruction
#### Compilation
```bash
make
```
This produces the `ircserv` executable.
Available Makefile rules: `all`, `clear`, `fclean`, `re`.

#### Execution
```bash
./ircserv <port> <password>
```
* `port` - the TCP port the server listens on
* `password` - the password required by clients to connectt

Example:
```bash
./ircserv 6667 your_password
```

#### Connectiong with a client
Using an IRC client of your choice, connect to `127.0.0.1` on the chosen port, and provide the password when prompted.

Quick manual test with `nc`:
```bash
nc -C 127.0.0.1 6667
PASS your_password
NICK nickname
USER nickname 0 * :user_name
```
### Resouces
* [Wikipedia](https://ja.wikipedia.org/wiki/Internet_Relay_Chat)
* `man poll`, `man socket`, `man fcntl`
* [IRCプロトコル解説記事](https://zenn.dev/rt3mis10/articles/ac5b35f8a3e1f2)

### AI Usage
AI (Claude) was used during this project for:
* Clarifying ambiguous points of the RFC/subject (e.g. how partial message buffering should behave, MODE command semantics)
* Reviewing and debugging specific pieces of logic (e.g. the poll() event loop, non-blocking I/O edge cases)
* Discussing design choices (class structure for Client/Channel/Server) before implementation