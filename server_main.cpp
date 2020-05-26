#include <fstream>

#include "common_client_handler.h"

int main() {
  ClientHandler ser = ClientHandler(123);
  ser.bind_and_listen("5555");
  ser.accept();
  ser.run();
  return 0;
}