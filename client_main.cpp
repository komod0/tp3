#include <iostream>
#include <fstream>
#include "common_client.h"
#include "common_utilities.h"
#include "common_Protocol.h"
#include "common_SocketExcept.h"
#include <vector>

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error: argumentos invalidos." << std::endl;
    return 1;
  }

  Client cli = Client();
  try {
    cli.connect(argv[1], argv[2]);
    cli();
  } catch(SocketException &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0; // Devuelve siempre 0 el cliente
}
