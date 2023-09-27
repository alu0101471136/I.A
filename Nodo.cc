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