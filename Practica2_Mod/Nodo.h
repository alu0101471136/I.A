/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file Nodo.h
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Oct 24 2023
  * @brief Este es el programa que implementa la clase Nodo
  * @bug No existen fallos conocidos
*/
#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <cmath>

class Nodo {
 public:
  Nodo();
  Nodo(std::pair<int,int> coordenadas, int coste_acumulado = 0, int coste_estimado = 0, Nodo* padre = NULL) : coordenadas_(coordenadas),
      coste_acumulado_(coste_acumulado), coste_estimado_(coste_estimado), padre_{padre} {};
  int GetCosteTotal() { return coste_acumulado_ + coste_estimado_; };
  int GetCosteAcumulado() { return coste_acumulado_; };
  int GetCosteEstimado() { return coste_estimado_; };
  std::pair<int,int> GetCoordenadas() { return coordenadas_; };
  Nodo* GetPadre() { return padre_; };
  void FuncionHeuristica(std::pair<int,int> posicion_final, int opcion) {
    if (opcion == 1) {
      coste_estimado_ = (abs(posicion_final.first - coordenadas_.first) + abs(posicion_final.second - coordenadas_.second)) * 3;
    } else if (opcion == 2) {
      coste_estimado_ = sqrt(pow(posicion_final.first - coordenadas_.first, 2) + pow(posicion_final.second - coordenadas_.second, 2));
    } else if (opcion == 3) {
      coste_estimado_ = (abs(posicion_final.second - coordenadas_.second) - abs(posicion_final.first - coordenadas_.first)) * 5 
                        + abs(posicion_final.first - coordenadas_.first) * 7;
    }
  };
  bool operator==(const Nodo& nodo) const {
    return coordenadas_ == nodo.coordenadas_;
  };
  bool operator<(const Nodo& nodo) const {
    return (coste_acumulado_ + coste_estimado_) < (nodo.coste_acumulado_ + nodo.coste_estimado_);
  };
  void SetCosteAcumulado(int coste_acumulado) { coste_acumulado_ = coste_acumulado; }; 
  void SetPadre(Nodo* padre) { padre_ = padre; };
 private:
  std::pair<int,int> coordenadas_;
///  int coste_total_;     /// F(n)
  int coste_acumulado_; /// G(n)
  int coste_estimado_;  /// H(n)
  Nodo* padre_; 
};

#endif