#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>

#include "common_Protocol.h"
#include "common_Scorer.h"
#include "common_Socket.h"
#include "common_Thread.h"

class ClientHandler: public Thread{
private:
  int remaining_attempts;
  bool game_over;
  int secret_number;
  Socket peer;
  Protocol protocol;
  Scorer &score;

public:
  ClientHandler(int num, Socket sock, Scorer &sc);

  ~ClientHandler();

  ClientHandler(const ClientHandler &other) = delete; // No copy

  ClientHandler& operator=(const ClientHandler &other) = delete;
  
  // VER DE IMPLEMENTAR EL CONSTRUCTOR POR MOVIMIENTO, SINO MANDAR delete.

  ClientHandler(ClientHandler &&other);

  ClientHandler& operator=(ClientHandler &&other);

  void run();

  void accept();

  void send(const std::string &msg);

  void recv(std::vector<char> &buffer, size_t length);

  void process_msg(const int &guess, std::string& response);

  void process_msg(char c, std::string& response);

  bool finished();

private:
  int score_guess(const int &guess, std::string& response);

  void generate_score_response(const int &good, const int &regular,
                               std::string& response);
};

#endif
