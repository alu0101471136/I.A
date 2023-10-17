#ifndef LABERINTO_H
#define LABERINTO_H
#include <vector>
#include <string>
#include "Nodo.h"

class Laberinto {
 public:
  Laberinto(std::string nombre_fichero);
  void BusquedaAEstrella();
  void MostrarLaberinto();
 private:
  std::vector<std::vector<int>> laberinto_;
  std::pair<int, int> posicion_inicial_;
  std::pair<int, int> posicion_final_;
  int numero_filas_;
  int numero_columnas_;
};

#endif