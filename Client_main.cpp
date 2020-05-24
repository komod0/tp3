#include <iostream>
#include <fstream>
#include "client.h"
#include <cstdint>
#include <arpa/inet.h>
#include <vector>

#define HELP "AYUDA"
#define SURRENDER "RENDIRSE"
#define MAX_NUMBER 65536

enum exit_codes{SUCCESS, ERROR};

bool is_uint16(std::string& s) {
  bool isanumber = s.find_first_not_of("0123456789") == s.npos;
  bool not_too_long = s.length() < 6; // Me aseguro que no explote el stoi
  return isanumber && not_too_long && (std::stoi(s) < MAX_NUMBER);
}

int parse_command(std::string& command, std::vector<char>& msg) {
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

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error: argumentos invalidos." << std::endl;
    return 1;
  }
  Client cli = Client();
  int status;
  bool game_finished = false;
  std::string usr_input;
  std::vector<char> msg;
  while (!game_finished) {
    msg.clear();
    std::cin >> usr_input;
    if (parse_command(usr_input, msg) != SUCCESS) {
      continue;
    }
    status = cli.send(msg);
  }
  return 0;
}