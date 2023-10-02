/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file busqueda_no_inf_func.h
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Sep 27 2023
  * @brief Este es una cabecera que contiene la funcion para imprimir el camino encontrado
  * @bug No existen fallos conocidos
  */
#ifndef BUSQUEDA_NO_INF_FUNC_H
#define BUSQUEDA_NO_INF_FUNC_H

#include <iostream>
#include <fstream>
#include "Vertice.h"
#include "ArbolBusqueda.h"

void ImprimirCamino(Vertice& vertice_inicial, Vertice& vertice_final, std::vector<Vertice>& camino, 
                    std::vector<Vertice>& vertices_visitados, std::vector<Vertice>& vertices_generados, float& distacia_camino) {
  std::fstream fichero_salida;
  fichero_salida.open("salida.txt", std::ios::out);
  fichero_salida << "Vertice inicial: " << vertice_inicial.GetId() + 1 << std::endl;
  fichero_salida << "Vertice final: " << vertice_final.GetId() + 1 << std::endl;
  fichero_salida << "Camino: ";
  for (int i = camino.size() - 1; i >= 0; --i) {
    if (i == 0) {
      fichero_salida << camino[i].GetId() + 1;
    } else {
      fichero_salida << camino[i].GetId() + 1 << "-";
    }
  }
  fichero_salida << std::endl << "Vertices visitados: " << vertices_visitados[0].GetId() + 1;
  for (unsigned i = 1; i < vertices_visitados.size(); ++i) {
    fichero_salida << ", " << vertices_visitados[i].GetId() + 1;
  }
  fichero_salida << std::endl << "Vertices generados: " << vertices_generados[0].GetId() + 1;
  for (unsigned i = 1; i < vertices_generados.size(); ++i) {
    fichero_salida << ", " << vertices_generados[i].GetId() + 1;
  }
  fichero_salida << "  " << std::endl << "Coste del camino: " << distacia_camino << std::endl;
}

#endif