#include "common_client.h"
#include <iostream>
#include <cstdint>
#include <arpa/inet.h>
#include <string>
#include <string.h>

enum exit_codes{SUCCESS, ERROR};

#define WIN "Ganaste"
#define LOSS "Perdiste"

Client::Client() {
}

Client::~Client() {
}

void Client::connect(const char* host, const char* service) {
  sock.s_connect(host, service);
}

void Client::send(std::vector<char>& msg) {
  sock.s_send(msg.data(), msg.size());
}

void Client::recv(std::vector<char>& buffer, size_t length) {
  sock.s_recv(buffer.data(), length);
}

void Client::run() {
  bool game_finished = false;
  std::string usr_input;
  std::vector<char> msg;
  std::string resp;
  while (!game_finished) {
    msg.clear();
    resp.clear();
    std::cin >> usr_input;
    if (protocol.encode_command(usr_input, msg) != SUCCESS) {
      continue;
    }
    send(msg);
    protocol.msg_recv(*this, resp);
    std::cout << resp.data() << std::endl;

    if (!strcmp(resp.data(), WIN) || !strcmp(resp.data(), LOSS)) {
      game_finished = true;
    }
  }
}

