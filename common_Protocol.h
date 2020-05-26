#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <arpa/inet.h>

class Client;
class ClientHandler;

class Protocol {
private:
  int ALGO;
public:
  Protocol();

  ~Protocol();

  Protocol(const Protocol &other) = delete; // Don't copy

  Protocol& operator=(const Protocol &other) = delete;

  Protocol(Protocol &&other);

  Protocol& operator=(Protocol &&other);

  int encode_command(const std::string& command, std::vector<char>& msg);

  void encode_str(const std::string& msg, std::string& buff) const;

  void msg_recv(Client &cli, std::string &resp) const;

  void recv_command_and_process(ClientHandler& server, 
                                std::string& response) const;
};

#endif