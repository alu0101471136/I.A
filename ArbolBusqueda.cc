#include <fstream>
#include <iostream>
#include "Nodo.h"
#include "Vertice.h"
#include "ArbolBusqueda.h"
#include <algorithm>
#include <queue>

ArbolBusqueda::ArbolBusqueda(std::string informacion_fichero) {
  std::ifstream fichero;
  fichero.open(informacion_fichero);
  if (fichero.is_open()) {
    fichero >> numero_vertices_;
    matriz_costes_.resize(numero_vertices_);
    for (int i = 0; i < numero_vertices_; i++) {
      matriz_costes_[i].resize(numero_vertices_);
    }
    float coste{-1};
    for (int i = 0; i < numero_vertices_; i++) {
      matriz_costes_[i][i] = std::make_pair(Vertice(i), -1);
      for (int j = i + 1; j < numero_vertices_; j++) {
        fichero >> coste;
        // std::cout << i << ", " << j << " Coste: " << coste << std::endl;
        matriz_costes_[i][j] = std::make_pair(Vertice(j), coste);
        matriz_costes_[j][i] = std::make_pair(Vertice(i), coste);
      }
    }
    fichero.close();
  } else {
    std::cout << "Error al abrir el fichero" << std::endl;
  }
}
/**
 * @name BusquedaAmplitud
 * @brief funcion que realiza una busqueda en anchura y genera un arbol de busqueda
 * 
 * @param vertice_inicial vertice inicial de la busqueda
 * @param vertice_final vertice final de la busqueda
 * @param camino vector que almacena el camino encontrado
 * @param vertices_visitados vector que almacena los vertices visitados
 * @param vertices_generados vector que almacena los vertices generados
 * @param distancia_camino coste del camino encontrado
*/
void ArbolBusqueda::BusquedaAmplitud(Vertice& vertice_inicial, Vertice& vertice_final, std::vector<Vertice>& camino, 
                                     std::vector<Vertice>& vertices_visitados, std::vector<Vertice>& vertices_generados, float& distancia_camino) {
  std::queue<Nodo*> cola;
  Nodo* nodo_inicial = new Nodo(vertice_inicial);
  vertices_generados.push_back(vertice_inicial);
  cola.push(nodo_inicial);
  while (!cola.empty()) {
    Nodo* nodo_actual = cola.front();
    cola.pop();
    if (nodo_actual->GetVertice() == vertice_final) {
      std::cout << "Camino encontrado" << std::endl;
      while (nodo_actual->GetPadre() != nullptr) {
        camino.push_back(nodo_actual->GetVertice());
        distancia_camino += nodo_actual->GetCostePadre();
        nodo_actual = nodo_actual->GetPadre();
      }
      camino.push_back(nodo_actual->GetVertice());
      return;
    } else {
      vertices_visitados.push_back(nodo_actual->GetVertice());
      for (int i = 0; i < numero_vertices_; ++i) {
        if (matriz_costes_[nodo_actual->GetVertice().GetId()][i].second != -1) {
          Vertice vertice_generado{matriz_costes_[nodo_actual->GetVertice().GetId()][i].first};
          if (nodo_actual->BuscarRama(vertice_generado) == false) {
            Nodo* nodo_generado = new Nodo(vertice_generado, nodo_actual, matriz_costes_[nodo_actual->GetVertice().GetId()][i].second);
            cola.push(nodo_generado);
            vertices_generados.push_back(vertice_generado);
          }
        }
      }
    }
  }
  std::cout << "Camino no encontrado" << std::endl;
}
