/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file ArbolBusqueda.cc
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Sep 27 2023
  * @brief Este es el programa que implementa los métodos de la clase ArbolBusqueda
  * @bug No existen fallos conocidos
  */
#include <fstream>
#include <iostream>
#include "Nodo.h"
#include "Vertice.h"
#include "ArbolBusqueda.h"
#include <algorithm>
#include <stack>
#include <queue>
#include <cstdlib>
/**
 * @name ArbolBusqueda
 * @brief constructor de la clase ArbolBusqueda
 * 
 * @param informacion_fichero fichero que contiene la informacion del grafo
*/
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
        std::cout << i << ", " << j << " Coste: " << coste << std::endl;
        matriz_costes_[i][j] = std::make_pair(Vertice(j), coste);
        matriz_costes_[j][i] = std::make_pair(Vertice(i), coste);
      }
    }
    for (int i = 0; i < numero_vertices_; i++) {
      int numero_hijos{0};
      for (int j = 0; j < numero_vertices_; j++) {
        if (matriz_costes_[i][j].second != -1) {
          numero_hijos++;
        }
      }
      numero_hijos_.push_back(numero_hijos);
    }
    fichero.close();
  } else {
    std::cout << "Error al abrir el fichero" << std::endl;
  }
}
/**
 * @name GenerarNumeroAleatorio
 * @brief funcion que genera un numero aleatorio entre un rango
 * 
 * @param max valor maximo del rango
 * @param min valor minimo del rango
*/
int GenerarNumeroAleatorio(int max, int min = 0) {
  srand(time(NULL));
  return rand() % (max - min) + min;
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
      vertices_visitados.push_back(nodo_actual->GetVertice());
      std::cout << "Camino encontrado" << std::endl;
      distancia_camino = nodo_actual->GetCostePadre();
      while (nodo_actual->GetPadre() != nullptr) {
        camino.push_back(nodo_actual->GetVertice());
        nodo_actual = nodo_actual->GetPadre();
      }
      camino.push_back(nodo_actual->GetVertice());
      return;
    } else {
      vertices_visitados.push_back(nodo_actual->GetVertice());
      std::vector<Nodo*> nodos_frontera;
      for (int i = 0; i < numero_vertices_; ++i) {
        if (matriz_costes_[nodo_actual->GetVertice().GetId()][i].second != -1) {
          Vertice vertice_generado{matriz_costes_[nodo_actual->GetVertice().GetId()][i].first};
          if (nodo_actual->BuscarRama(vertice_generado) == false) {
            // std::cout << "Aleatorio " << GenerarNumeroAleatorio(numero_hijos_[nodo_actual->GetVertice().GetId()]) + 1 << std::endl;
            Nodo* nodo_generado = new Nodo(vertice_generado, nodo_actual, matriz_costes_[nodo_actual->GetVertice().GetId()][i].second);
            nodo_generado->SetCostePadre(matriz_costes_[nodo_actual->GetVertice().GetId()][i].second + nodo_actual->GetCostePadre());
            // cola.push(nodo_generado);
            nodos_frontera.push_back(nodo_generado);
            vertices_generados.push_back(vertice_generado);
          }
        }
      }
      float min{0}, segundo_min{0};
      int iterador_min{0}, iterador_segundo_min{0};
      if (nodos_frontera.size() > 0) {
        min = nodos_frontera[0]->GetCostePadre();
        segundo_min = nodos_frontera[0]->GetCostePadre();
      }
      for (unsigned i = 0; i < nodos_frontera.size(); ++i) {
        if (min > nodos_frontera[i]->GetCostePadre()) {
          segundo_min = min;
          iterador_segundo_min = iterador_min;
          min = nodos_frontera[i]->GetCostePadre();
          iterador_min = i;
        }
      }
      GenerarNumeroAleatorio(2);
      if (nodos_frontera.size() > 0) {
        if (GenerarNumeroAleatorio(2) == 1) {
          cola.push(nodos_frontera[iterador_min]);
          cola.push(nodos_frontera[iterador_segundo_min]);
          if (iterador_min < iterador_segundo_min) {
            nodos_frontera.erase(nodos_frontera.begin() + iterador_segundo_min - 1);
          } else {
            nodos_frontera.erase(nodos_frontera.begin() + iterador_segundo_min);
          }
        } else {
          cola.push(nodos_frontera[iterador_segundo_min]);
          cola.push(nodos_frontera[iterador_min]);
          if (iterador_min < iterador_segundo_min) {
            nodos_frontera.erase(nodos_frontera.begin() + iterador_min);
          } else {
            nodos_frontera.erase(nodos_frontera.begin() + iterador_min - 1);
          }
        }
      }
    }
  }
  std::cout << "Camino no encontrado" << std::endl;
}
/**
 * @name BusquedaProfundidad
 * @brief funcion que realiza una busqueda en profundidad y genera un arbol de busqueda
 * 
 * @param vertice_inicial vertice inicial de la busqueda
 * @param vertice_final vertice final de la busqueda
 * @param camino vector que almacena el camino encontrado
 * @param vertices_visitados vector que almacena los vertices visitados
 * @param vertices_generados vector que almacena los vertices generados
 * @param distancia_camino coste del camino encontrado
*/
void ArbolBusqueda::BusquedaProfundidad(Vertice& vertice_inicial, Vertice& vertice_final, std::vector<Vertice>& camino, 
                        std::vector<Vertice>& vertices_visitados, std::vector<Vertice>& vertices_generados, float& distancia_camino) {
  std::stack<Nodo*> pila;
  Nodo* nodo_inicial = new Nodo(vertice_inicial);
  vertices_generados.push_back(vertice_inicial);
  pila.push(nodo_inicial);
  while (!pila.empty()) {
    Nodo* nodo_actual = pila.top();
    pila.pop();
    if (nodo_actual->GetVertice() == vertice_final) {
      std::cout << "Camino encontrado" << std::endl;
      vertices_visitados.push_back(nodo_actual->GetVertice());
      while (nodo_actual->GetPadre() != nullptr) {
        camino.push_back(nodo_actual->GetVertice());
        distancia_camino += nodo_actual->GetCostePadre();
        nodo_actual = nodo_actual->GetPadre();
      }
      camino.push_back(nodo_actual->GetVertice());
      return;
    } else {
      vertices_visitados.push_back(nodo_actual->GetVertice());
      for (int i = numero_vertices_; i >= 0; --i) {
        if (matriz_costes_[nodo_actual->GetVertice().GetId()][i].second != -1) {
          Vertice vertice_generado{matriz_costes_[nodo_actual->GetVertice().GetId()][i].first};
          if (nodo_actual->BuscarRama(vertice_generado) == false) {
            Nodo* nodo_generado = new Nodo(vertice_generado, nodo_actual, matriz_costes_[nodo_actual->GetVertice().GetId()][i].second);
            pila.push(nodo_generado);
            vertices_generados.push_back(vertice_generado);
          }
        }
      }
    }
  }
}