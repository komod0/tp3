#include <iostream>
#include <fstream>
#include "common_client.h"
#include "common_utilities.h"
#include "common_Protocol.h"
#include "common_SocketExcept.h"
#include <vector>

enum exit_codes{SUCCESS, ERROR};

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error: argumentos invalidos." << std::endl;
    return 1;
  }

  int status = SUCCESS;
  Client cli = Client();
  try {
    cli.connect(argv[1], argv[2]);
    cli();
  } catch(SocketException &e) {
    std::cerr << e.what() << std::endl;
    status = ERROR;
  }
  return status;
}
