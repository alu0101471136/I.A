/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file Vertice.h
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Sep 27 2023
  * @brief Este es la cabecera de la clase vertice
  * @bug No existen fallos conocidos
  */
#ifndef VERTICE_H
#define VERTICE_H

#include <vector>
/** 
 * @name Vertice
 * @brief clase que representa un vertice del grafo
 * 
*/
class Vertice {
 public:
  Vertice() : identificador_{0}, visitado_{false} {};
  Vertice(int identificador, bool visitado = false) : identificador_{identificador}, visitado_{visitado} {};
  Vertice(const Vertice& vertice) : identificador_{vertice.identificador_}, visitado_{vertice.visitado_} {};
  int GetId() { return identificador_; }
  bool GetVisitado() { return visitado_; }
  bool operator==(const Vertice& vertice) const { return this->identificador_ == vertice.identificador_; }
  bool operator!=(const Vertice& vertice) const { return identificador_ != vertice.identificador_; }
  bool operator<(const Vertice& vertice) const { return this->identificador_ < vertice.identificador_; }
  void VerticeVisitado(bool visitado) { visitado_ = visitado; }
 private:
  int identificador_;
  bool visitado_;
};

#endif