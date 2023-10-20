#ifndef NODO_H
#define NODO_H
#include <iostream>

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
  void FuncionHeuristicaManhattan(std::pair<int,int> posicion_final) {
    coste_estimado_ = (abs(posicion_final.first - coordenadas_.first) + abs(posicion_final.second - coordenadas_.second)) * 3;
  }
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