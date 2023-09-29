/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file Nodo.cc
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Sep 27 2023
  * @brief Este es el programa que implementa la busqueda en la rama de un nodo
  * @bug No existen fallos conocidos
  */
#include "Nodo.h"

bool Nodo::BuscarRama(Vertice& vertice) const {
  Nodo* nodo_aux = this->padre_;
  while (nodo_aux != nullptr) {
    if (nodo_aux->GetVertice() == vertice) {
      return true;
    }
    nodo_aux = nodo_aux->GetPadre();
  }
  return false;
}