#include "Server.h"
#include "utilities.h"

#define INITIAL_ATTEMPTS 10
#define NUM_OF_DIGITS 3

Server::Server(int num)
  : remaining_attempts(INITIAL_ATTEMPTS),
    game_over(false),
    protocol(Protocol()),
    secret_number(num) {}

Server::~Server() {}

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
  remaining_attempts -= 1;
  std::string aux = std::to_string(guess);
  if (aux.length() != NUM_OF_DIGITS || !non_repeating_string(aux)) {
    response = "Número inválido. Debe ser de 3 cifras no repetidas";
    return;
  }
  if (score_guess(guess, response) == NUM_OF_DIGITS||remaining_attempts == 0) {
    game_over = true;
  }
}

int Server::score_guess(int guess, std::string& response) {
  std::string secret = std::to_string(secret_number);
  std::string guess_s = std::to_string(guess);
  int good = 0;
  int regular = 0;
  for (int i = 0; i < guess_s.length(); i++) {
    if (guess_s[i] == secret[i]) {
      good += 1;
    } else if (secret.find(guess_s[i]) != std::string::npos) {
      regular += 1;
    }
  }
  generate_score_response(good, regular, response);

  return good;
}

void Server::generate_score_response(int good, int regular,
                                     std::string& response) {
  if (good == NUM_OF_DIGITS) {
    response = "Ganaste";
  } else if (remaining_attempts == 0) {
    response = "Perdiste";
  } else if (good != 0) {
    response = std::to_string(good) + " bien";
    if (regular != 0) {
      response += ", " + std::to_string(regular) + " regular";
    }
  } else if (regular != 0) {
    response = std::to_string(regular) + " regular";
  } else {
    response = std::to_string(NUM_OF_DIGITS) + " mal";
  }
}
