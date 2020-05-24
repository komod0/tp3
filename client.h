#include <vector>

class Client {
private:
  int algo;
public:
  Client();

  ~Client();

  int send(std::vector<char>& msg);

  int recv()
};