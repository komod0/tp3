#include "Client.h"
#include <iostream>
#include <cstdint>
#include <arpa/inet.h>

enum exit_codes{SUCCESS, ERROR};

Client::Client() : protocol(Protocol()){

}

Client::~Client() {
}

int Client::send(std::vector<char>& msg) {
  if (msg[0] == 'h') {
    std::cout << "AYUDA" << std::endl;
  } else if (msg[0] == 's') {
    std::cout << "Te rendiste" << std::endl;
  } else if (msg[0] == 'n') {
    uint16_t num = *(int*)(msg.data() + 1);
    num = ntohs(num);
    std::cout << "El numero que me pasate es el: " << num << std::endl;
  }
  return 0;
}

int Client::recv() {
  return 0;
}

int Client::run() {
  int status;
  bool game_finished = false;
  std::string usr_input;
  std::vector<char> msg;
  while (!game_finished) {
    msg.clear();
    std::cin >> usr_input;
    if (protocol.encode_command(usr_input, msg) != SUCCESS) {
      continue;
    }
    status = send(msg);
    protocol.msg_recv();
  }
  return status;
}

