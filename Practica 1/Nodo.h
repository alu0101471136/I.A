/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file Nodo.h
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Sep 27 2023
  * @brief Este es la cabecera de la clase Nodo
  * @bug No existen fallos conocidos
  */
#include "Vertice.h"
/** 
 * @name Nodo
 * @brief clase que representa un nodo del arbol de busqueda
 * 
*/
class Nodo {
 public:
  Nodo() : vertice_{Vertice()}, padre_{nullptr}, coste_padre_{0} {};
  Nodo(Vertice vertice, Nodo* padre = nullptr, float coste_padre = 0) : 
       vertice_{vertice}, padre_{padre}, coste_padre_{coste_padre} {};
  Vertice GetVertice() const { return vertice_; }
  Nodo* GetPadre() const { return padre_; }
  float GetCostePadre() const { return coste_padre_; }
  void SetPadre(Nodo* padre) { padre_ = padre; }
  void SetCostePadre(float coste_padre) { coste_padre_ = coste_padre; }
  bool BuscarRama(Vertice& vertice) const;
  bool operator==(const Nodo& nodo) const { return this->vertice_ == nodo.vertice_; }
  bool operator!=(const Nodo& nodo) const { return vertice_ != nodo.vertice_; }
 private:
  Vertice vertice_;
  Nodo* padre_;
  float coste_padre_;
};