#include "Server.h"

#define INITIAL_ATTEMPTS 10

Server::Server(int num)
  : remaining_attempts(INITIAL_ATTEMPTS),
    game_over(false),
    protocol(Protocol()),
    secret_number(num) {
}

Server::~Server() {
}

void Server::run() {
  std::string response;
  while (!game_over) {
    protocol.recv_command_and_process(*this, response);
    std::cout << response << std::endl;
  }
  std::cout << "It's a game over!\n";
}

void Server::process_msg(char c, std::string& response) {
  if (c == 's') {
    game_over = true;
    // Aca se aumentaria el contador de perdidos en 1
    response = "Perdiste";
  } else {
    response = "Comandos válidos:​\n\t​AYUDA: despliega la lista de comandos \
válidos​\n\t​RENDIRSE: pierde el juego automáticamente​\n\t​XXX: Número de \
3 cifras a ser enviado al servidor para adivinar el número secreto";
  }
}

void Server::process_msg(int guess, std::string& response) {
  std::string aux = std::to_string(guess);
  // Aca la lógica quilombera
}

