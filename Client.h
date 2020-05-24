#include <vector>

#include "Protocol.h"

class Client {
private:
  Protocol protocol;
public:
  Client();

  ~Client();

  int send(std::vector<char>& msg);

  int recv();

  int run();
};