#include "common_Scorer.h"

Scorer::Scorer() : wins(0), losses(0) {}

Scorer::~Scorer() {}

void Scorer::increase_wins() {
  std::unique_lock<std::mutex> l(m);
  wins += 1;
}

void Scorer::increase_loss() {
  std::unique_lock<std::mutex> l(m);
  losses += 1;
}

std::ostream& operator<<(std::ostream& os, const Scorer &sc)
{
    os << "Estadísticas:\n\tGanadores: " << sc.wins << "\n\tPerdedores: " << 
    sc.losses << "\n";
    return os;
}

