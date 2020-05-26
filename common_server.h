#ifndef SERVER_H
#define SERVER_H

#include "common_Protocol.h"
#include "common_Socket.h"

class Server {
private:
  int remaining_attempts;
  bool game_over;
  int secret_number;
  Protocol protocol;
  Socket sock;
  Socket peer;
public:
  Server(int num);

  ~Server();

  Server(const Server &other) = delete; // No copy

  Server& operator=(const Server &other) = delete;
  
  // VER DE IMPLEMENTAR EL CONSTRUCTOR POR MOVIMIENTO, SINO MANDAR delete.

  Server(Server &&other);

  Server& operator=(Server &&other);

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