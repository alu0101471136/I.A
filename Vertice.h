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