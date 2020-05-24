#include <iostream>
#include <fstream>
#include "Client.h"
#include "utilities.h"
#include "Protocol.h"
#include <vector>

enum exit_codes{SUCCESS, ERROR};

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error: argumentos invalidos." << std::endl;
    return 1;
  }
  Client cli = Client();
  int status = cli.run();
  return status;
}