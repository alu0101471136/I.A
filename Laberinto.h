#ifndef LABERINTO_H
#define LABERINTO_H
#include <vector>
#include <string>
#include "Nodo.h"

class Laberinto {
 public:
  Laberinto(std::string nombre_fichero);
  void BusquedaAEstrella(std::vector<Nodo*>& camino, std::vector<Nodo*>& nodos_abiertos, std::vector<Nodo*>& nodos_cerrados, int opcion);
  void MostrarLaberinto();
  bool MovimientoValido(std::pair<int,int> coordenadas);
  bool NodoAbierto(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_abiertos, int& iterador);
  bool NodoCerrado(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_cerrados);
  void MarcarCamino(const std::vector<Nodo*>& camino);
  void GetPosiblesVecinos(std::vector<Nodo*>& nodos_abiertos, std::vector<Nodo*>& nodos_cerrados, Nodo* nodo_actual, int opcion);
  void SetPosicionInicial(std::pair<int,int> posicion_inicial) { 
    laberinto_[posicion_inicial_.first][posicion_inicial_.second] = 0;
    posicion_inicial_ = posicion_inicial; 
    laberinto_[posicion_inicial_.first][posicion_inicial_.second] = 3;
  };
  void SetPosicionFinal(std::pair<int,int> posicion_final) { 
    laberinto_[posicion_final_.first][posicion_final_.second] = 0;
    posicion_final_ = posicion_final; 
    laberinto_[posicion_final_.first][posicion_final_.second] = 4;
  };
 private:
  std::vector<std::vector<int>> laberinto_;
  std::pair<int, int> posicion_inicial_;
  std::pair<int, int> posicion_final_;
  int numero_filas_;
  int numero_columnas_;
};

#endif