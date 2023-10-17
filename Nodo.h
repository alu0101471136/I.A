#ifndef NODO_H
#define NODO_H
#include <iostream>

class Nodo {
 public:
  Nodo();
  Nodo(int identificador, int coste_total, int coste_acumulado, int coste_estimado) : identificador_(identificador), 
       coste_total_(coste_total), coste_acumulado_(coste_acumulado), coste_estimado_(coste_estimado) {};
 private:
  Nodo* padre_; 
  int identificador_;
  int coste_total_;     /// F(n)
  int coste_acumulado_; /// G(n)
  int coste_estimado_;  /// H(n)
};

#endif