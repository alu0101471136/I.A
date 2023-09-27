#ifndef BUSQUEDA_NO_INF_FUNC_H
#define BUSQUEDA_NO_INF_FUNC_H
#include <iostream>
#include "Vertice.h"
#include "ArbolBusqueda.h"

void ImprimirCamino(Vertice& vertice_inicial, Vertice& vertice_final, std::vector<Vertice>& camino, 
                    std::vector<Vertice>& vertices_visitados, std::vector<Vertice>& vertices_generados, float& distacia_camino) {
  std::cout << "v0: " << vertice_inicial.GetId() << " | vd: " << vertice_final.GetId() << std::endl;
  std::cout << "Camino: ";
  for (int i = camino.size() - 1; i >= 0; --i) {
    if (i == 0) {
      std::cout << camino[i].GetId();
    } else {
      std::cout << camino[i].GetId() << "-";
    }
  }
  std::cout << std::endl << "Vertices visitados: " << vertices_visitados[0].GetId();
  for (unsigned i = 1; i < vertices_visitados.size(); ++i) {
    std::cout << ", " << vertices_visitados[i].GetId();
  }
  std::cout << std::endl << "Vertices generados: " << vertices_generados[0].GetId();
  for (unsigned i = 1; i < vertices_generados.size(); ++i) {
    std::cout << ", " << vertices_generados[i].GetId();
  }
  std::cout << "  " << std::endl << "Coste del camino: " << distacia_camino << std::endl;
}

#endif