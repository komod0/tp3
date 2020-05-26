#ifndef SERVER_H
#define SERVER_H

#include "common_Protocol.h"
#include "common_Socket.h"

class ClientHandler {
private:
  int remaining_attempts;
  bool game_over;
  int secret_number;
  Protocol protocol;
  Socket sock;
  Socket peer;
public:
  ClientHandler(int num);

  ~ClientHandler();

  ClientHandler(const ClientHandler &other) = delete; // No copy

  ClientHandler& operator=(const ClientHandler &other) = delete;
  
  // VER DE IMPLEMENTAR EL CONSTRUCTOR POR MOVIMIENTO, SINO MANDAR delete.

  ClientHandler(ClientHandler &&other);

  ClientHandler& operator=(ClientHandler &&other);

  void run();

  void accept();

  void bind_and_listen(const char* serv);

  void send(const std::string &msg);

  void recv(std::vector<char> &buffer, size_t length);

  void process_msg(const int &guess, std::string& response);

  void process_msg(char c, std::string& response);

private:
  int score_guess(const int &guess, std::string& response);

  void generate_score_response(const int &good, const int &regular,
                               std::string& response);
};

#endif