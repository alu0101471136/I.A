#ifndef ARBOLBUSQUEDA_H
#define ARBOLBUSQUEDA_H

#include "Vertice.h"
#include <vector>

/** 
 * @name ArbolBusqueda
 * @brief clase que representa el arbol de busqueda
 * 
*/
class ArbolBusqueda {
 public:
  ArbolBusqueda(std::string informacion_fichero);
  int GetNumeroVertices() { return numero_vertices_; };
  void BusquedaAmplitud(Vertice& vertice_inicial, Vertice& vertice_final, std::vector<Vertice>& camino, 
                        std::vector<Vertice>& vertices_visitados, std::vector<Vertice>& vertices_generados, float& distancia_camino);
  void BusquedaProfundidad(Vertice& vertice_inicial, Vertice& vertice_final, std::vector<Vertice>& camino, 
                        std::vector<Vertice>& vertices_visitados, std::vector<Vertice>& vertices_generados, float& distancia_camino);
 private:
  int numero_vertices_;
  std::vector<std::vector<std::pair<Vertice,float>>> matriz_costes_;
};

#endif