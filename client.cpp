#include "client.h"
#include <iostream>
#include <cstdint>
#include <arpa/inet.h>


Client::Client() {
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

