#include <cstdint>
#include <arpa/inet.h>

#include <stdio.h>

#include "common_utilities.h"
#include "common_Protocol.h"
#include "common_client.h"
#include "common_client_handler.h"

#define HELP "AYUDA"
#define SURRENDER "RENDIRSE"
#define SIZEOF_MSG_LEN 4
#define SIZEOF_GUESS 2

Protocol::Protocol() {
}

Protocol::~Protocol() {
}

int Protocol::encode_command(const std::string& command,
                            std::vector<char>& msg) {
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

void Protocol::msg_recv(Client &cli, std::string &resp) const{
  std::vector<char> aux;
  aux.resize(SIZEOF_MSG_LEN);
  cli.recv(aux, SIZEOF_MSG_LEN);
  uint32_t msg_len = ntohl(*(int*)(aux.data()));

  aux.resize(msg_len);
  cli.recv(aux, msg_len);

  resp.append(aux.data(), aux.size());
  resp.push_back('\0');
}

void Protocol::encode_str(const std::string& msg, std::string& buff) const {
  uint32_t msg_len = msg.length();
  msg_len = htonl(msg_len);
  buff.append((char*)&msg_len, sizeof(uint32_t));
  buff.append(msg);
}

void Protocol::recv_command_and_process(ClientHandler& handler, 
                                        std::string& response) const{
  uint16_t guess;
  std::vector<char> aux;
  aux.resize(1);
  handler.recv(aux, 1);
  if (aux[0] == 'n') {
    // Aca leeria 2 bytes del socket
    aux.resize(SIZEOF_GUESS);
    handler.recv(aux, SIZEOF_GUESS);
    guess = ntohs(*(int*)(aux.data()));
    handler.process_msg(guess, response);
  } else {
    handler.process_msg(aux[0], response);
  }
}
