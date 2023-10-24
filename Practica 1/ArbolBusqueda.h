/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file ArbolBusqueda.h
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Sep 27 2023
  * @brief Este es la cabecera de la clase vertice
  * @bug No existen fallos conocidos
  */
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
  std::vector<int> numero_hijos_;
};

#endif