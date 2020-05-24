#ifndef SERVER_H
#define SERVER_H

#include "Protocol.h"

class Server {
private:
  int remaining_attempts;
  bool game_over;
  Protocol protocol;
  int secret_number;
public:
  Server(int num);

  ~Server();

  void run();

  void send();

  void process_msg(int num, std::string& response);

  void process_msg(char c, std::string& response);
};

#endif