#include "common_client_handler.h"
#include "common_utilities.h"

#define INITIAL_ATTEMPTS 10
#define NUM_OF_DIGITS 3

ClientHandler::ClientHandler(int num)
  : remaining_attempts(INITIAL_ATTEMPTS),
    game_over(false),
    secret_number(num) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
  std::string response;
  std::string encoded_resp;
  while (!game_over) {
    encoded_resp.clear();
    protocol.recv_command_and_process(*this, response);
    std::cout << response << std::endl;
    protocol.encode_str(response, encoded_resp);
    send(encoded_resp);
  }
  std::cout << "It's a game over!\n";
}

void ClientHandler::recv(std::vector<char> &buffer, size_t length) {
  peer.s_recv(buffer.data(), length);
}

void ClientHandler::send(const std::string &msg) {
  peer.s_send(msg.c_str(), msg.length());
}

void ClientHandler::accept() {
  peer = sock.s_accept();
}

void ClientHandler::bind_and_listen(const char* serv) {
  sock.s_bind(serv);
  sock.s_listen();
}

void ClientHandler::process_msg(char c, std::string& response) {
  if (c == 's') {
    game_over = true;
    // Aca se aumentaria el contador de perdidos en 1
    response = "Perdiste";
  } else {
    response = "Comandos válidos:\n\tAYUDA: despliega la lista de comandos \
válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: Número de \
3 cifras a ser enviado al servidor para adivinar el número secreto";
  }
}

void ClientHandler::process_msg(const int &guess, std::string& response) {
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

int ClientHandler::score_guess(const int &guess, std::string& response) {
  std::string secret = std::to_string(secret_number);
  std::string guess_s = std::to_string(guess);
  int good = 0;
  int regular = 0;
  for (size_t i = 0; i < guess_s.length(); i++) {
    if (guess_s[i] == secret[i]) {
      good += 1;
    } else if (secret.find(guess_s[i]) != std::string::npos) {
      regular += 1;
    }
  }
  generate_score_response(good, regular, response);

  return good;
}

void ClientHandler::generate_score_response(const int &good, const int &regular,
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
