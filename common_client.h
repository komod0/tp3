#ifndef CLIENT_H
#define CLIENT_h

#include <vector>

#include "common_Protocol.h"
#include "common_Socket.h"

class Client {
private:
  Protocol protocol;
  Socket sock;
public:
  Client();

  ~Client();

  Client(const Client &other) = delete;

  Client& operator=(const Client &other) = delete;

  // VER SI TIENE SENTIDO DEJARLO

  Client(Client &&other);

  Client& operator=(Client &&other);

  void connect(const char* host, const char* service);

  void send(std::vector<char>& msg);

  void recv(std::vector<char>& msg, size_t length);

  void run();
};

#endif
