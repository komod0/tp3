#include <cstdint>
#include <arpa/inet.h>

#include <stdio.h>

#include "Protocol.h"
#include "Server.h"
#include "utilities.h"

#define HELP "AYUDA"
#define SURRENDER "RENDIRSE"

Protocol::Protocol() {
}

Protocol::~Protocol() {
}

int Protocol::encode_command(std::string& command, std::vector<char>& msg) {
  if (command == HELP) {
    msg.push_back('h');
  } else if (command == SURRENDER) {
    msg.push_back('s');
  } else if(is_uint16(command)) {
    msg.push_back('n');
    uint16_t num = std::stoi(command);
    num = htons(num);
    msg.push_back(((char*)&num)[0]);
    msg.push_back(((char*)&num)[1]);
  } else {
    std::cerr << "Error: comando inválido. Escriba AYUDA para obtener ayuda\n";
    return 1;
  }
  return 0;
}

void Protocol::msg_recv() {
  // BEGIN el prosi
  std::string prue_msg = "Esto es una cadena de long 29";
  std::string prue_encod;
  encode_str(prue_msg, prue_encod);
  // END el prosi
  //uint32_t msg_len = ntohl(*(int*)(prue_encod.c_str()));

}

void Protocol::encode_str(std::string& msg, std::string& buff) {
  uint32_t msg_len = msg.length();
  msg_len = htonl(msg_len);
  buff.append((char*)&msg_len, sizeof(uint32_t));
  buff.append(msg);
}

void Protocol::recv_command_and_process(Server& server, std::string& response) {
  uint16_t guess;
  // Aca leeria del socket 1 byte
  char op_code = 's';
  if (op_code == 'n') {
    // Aca leeria 2 bytes del socket
    guess = 123;
    server.process_msg(guess, response);
  } else {
    server.process_msg(op_code, response);
  }
}
