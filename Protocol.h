#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <arpa/inet.h>

class Server;

class Protocol {
private:
  int ALGO;
public:
  Protocol();

  ~Protocol();

  int encode_command(std::string& command, std::vector<char>& msg);

  void encode_str(std::string& msg, std::string& buff);

  void msg_recv();

  void recv_command_and_process(Server& server, std::string& response);
};

#endif