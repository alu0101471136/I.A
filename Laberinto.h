#ifndef LABERINTO_H
#define LABERINTO_H
#include <vector>
#include <string>
#include "Nodo.h"

class Laberinto {
 public:
  Laberinto(std::string nombre_fichero);
  void BusquedaAEstrella(std::vector<Nodo*>& camino, std::vector<Nodo*>& nodos_abiertos, std::vector<Nodo*>& nodos_cerrados);
  void MostrarLaberinto();
  bool MovimientoValido(std::pair<int,int> coordenadas);
  bool NodoAbierto(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_abiertos);
  bool NodoCerrado(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_cerrados);
  void GetPosiblesVecinos(std::vector<Nodo*>& nodos_abiertos, std::vector<Nodo*>& nodos_cerrados, Nodo* nodo_actual);
 private:
  std::vector<std::vector<int>> laberinto_;
  std::pair<int, int> posicion_inicial_;
  std::pair<int, int> posicion_final_;
  int numero_filas_;
  int numero_columnas_;
};

#endif