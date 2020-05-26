#include <iostream>
#include <mutex>

class Scorer
{
private:
  int wins;
  int losses;
  std::mutex m;
public:
  Scorer();

  ~Scorer();

  void increase_wins();

  void increase_loss();

  friend std::ostream& operator<<(std::ostream& os, const Scorer &sc);
};
