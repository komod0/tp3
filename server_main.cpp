#include <fstream>

#include "common_server.h"

int main() {
  Server ser = Server(123);
  ser.bind_and_listen("5555");
  ser.accept();
  ser.run();
  return 0;
}