/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file Laberinto.cc
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Oct 24 2023
  * @brief Este es el programa que implementa los métodos de la clase Laberinto
  * @bug No existen fallos conocidos
*/
#include <fstream>
#include "Nodo.h"
#include "Laberinto.h"
/**
 * @name Laberinto
 * 
 * @brief Constructor de la clase Laberinto
 * @param nombre_fichero Nombre del fichero que contiene el laberinto
 * @return No devuelve nada
 *
*/
Laberinto::Laberinto(std::string nombre_fichero) {
  std::ifstream fichero(nombre_fichero);
  std::string linea;
  if (fichero.is_open()) {
    fichero >> numero_filas_;
    fichero >> numero_columnas_;
    for (int i = 0; i < numero_filas_; i++) {
      std::vector<int> fila;
      for (int j = 0; j < numero_columnas_; j++) {
        int valor;
        fichero >> valor;
        if (valor == 3) {
          posicion_inicial_ = std::make_pair(i,j);
        } else if (valor == 4) {
          posicion_final_ = std::make_pair(i,j);
        }
        fila.push_back(valor);
      }
      laberinto_.push_back(fila);
    }
  }
}
/**
 * @name MostrarLaberinto 
 *
 * @brief Destructor de la clase Laberinto
 * @param No tiene parámetros
 * @return No devuelve nada
 * 
*/
void Laberinto::MostrarLaberinto() {
  std::cout << "Posicion inicial: " << posicion_inicial_.first + 1 << " " << posicion_inicial_.second + 1 << std::endl;
    std::cout << "Posicion final: " << posicion_final_.first + 1 << " " << posicion_final_.second + 1 << std::endl;
  for (int i = 0; i < numero_filas_; i++) {
    for (int j = 0; j < numero_columnas_; j++) {
      if (laberinto_[i][j] == 0)
        std::cout << " ";
      else if (laberinto_[i][j] == 1)
        std::cout << "#";
      else if (laberinto_[i][j] == 2)
        std::cout << "█";
      else if (laberinto_[i][j] == 3)
        std::cout << "S";
      else if (laberinto_[i][j] == 4)
        std::cout << "F";
    }
    std::cout << std::endl;
  }
}
/**
 * @name MarcarCamino
 * 
 * @brief Marca el camino en el laberinto
 * @param camino Vector que contiene el camino
 * @return No devuelve nada
 * 
*/
void Laberinto::MarcarCamino(const std::vector<Nodo*>& camino) {
  for (unsigned i = 0; i < camino.size(); i++) {
    if (laberinto_[camino[i]->GetCoordenadas().first][camino[i]->GetCoordenadas().second] != 3 && laberinto_[camino[i]->GetCoordenadas().first][camino[i]->GetCoordenadas().second] != 4) {
      laberinto_[camino[i]->GetCoordenadas().first][camino[i]->GetCoordenadas().second] = 2;
    }
  }
}
/**
 * @name MovimientoValido
 * 
 * @brief Comprueba si el movimiento es válido
 * @param coordenadas Coordenadas del movimiento
 * @return Devuelve true si el movimiento es válido y false si no lo es
 * 
*/
bool Laberinto::MovimientoValido(std::pair<int,int> coordenadas) {
  if (coordenadas.first < 0 || coordenadas.first >= numero_filas_ || coordenadas.second < 0 || coordenadas.second >= numero_columnas_) {
    return false;
  } else if (laberinto_[coordenadas.first][coordenadas.second] == 1) {
    return false;
  }
  return true;
}
/**
 * @name NodoAbierto
 * 
 * @brief Comprueba si el nodo está en la lista de nodos abiertos
 * @param coordenadas Coordenadas del nodo
 * @param nodos_abiertos Vector que contiene los nodos abiertos
 * @param iterador Iterador que indica la posición del nodo en el vector
 * @return Devuelve true si el nodo está en la lista de nodos abiertos y false si no lo está
 * 
*/
bool Laberinto::NodoAbierto(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_abiertos, int& iterador) {
  for (unsigned i = 0; i < nodos_abiertos.size(); i++) {
    if (nodos_abiertos[i]->GetCoordenadas() == coordenadas) {
      iterador = i;
      return true;
    }
  }
  return false;
}
/**
 * @name NodoCerrado
 * 
 * @brief Comprueba si el nodo está en la lista de nodos cerrados
 * @param coordenadas Coordenadas del nodo
 * @param nodos_cerrados Vector que contiene los nodos cerrados
 * @return Devuelve true si el nodo está en la lista de nodos cerrados y false si no lo está
 * 
*/
bool Laberinto::NodoCerrado(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_cerrados) {
  for (unsigned i = 0; i < nodos_cerrados.size(); i++) {
    if (nodos_cerrados[i]->GetCoordenadas() == coordenadas) {
      return true;
    }
  }
  return false;
}
/**
 * @name GetPosiblesVecinos
 * 
 * @brief Obtiene los posibles vecinos de un nodo
 * @param nodos_abiertos Vector que contiene los nodos abiertos
 * @param nodos_cerrados Vector que contiene los nodos cerrados
 * @param nodo_actual Nodo del que se obtienen los vecinos
 * @param opcion Opción que indica la heurística a utilizar
 * @return No devuelve nada
 * 
*/
void Laberinto::GetPosiblesVecinos(std::vector<Nodo*>& nodos_abiertos, std::vector<Nodo*>& nodos_cerrados,Nodo* nodo_actual, int opcion) {
  std::pair<int,int> coordenadas = nodo_actual->GetCoordenadas();
  const int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
  const int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
  for (int i = 0; i < 8; i++) {
    std::pair<int,int> coordenadas_vecino = std::make_pair(coordenadas.first + dx[i], coordenadas.second + dy[i]);
    int iterador;
    if (MovimientoValido(coordenadas_vecino) && NodoAbierto(coordenadas_vecino, nodos_abiertos, iterador) && !NodoCerrado(coordenadas_vecino, nodos_cerrados)) {
      if (i >= 4) {
        if (nodo_actual->GetCosteAcumulado() + 7 < nodos_abiertos[iterador]->GetCosteAcumulado()) {
          nodos_abiertos[iterador]->SetCosteAcumulado(nodo_actual->GetCosteAcumulado() + 7);
          nodos_abiertos[iterador]->FuncionHeuristica(posicion_final_, opcion);
          nodos_abiertos[iterador]->SetPadre(nodo_actual);
        }
      } else {
        if (nodo_actual->GetCosteAcumulado() + 5 < nodos_abiertos[iterador]->GetCosteAcumulado()) {
          nodos_abiertos[iterador]->SetCosteAcumulado(nodo_actual->GetCosteAcumulado() + 5);
          nodos_abiertos[iterador]->FuncionHeuristica(posicion_final_, opcion);
          nodos_abiertos[iterador]->SetPadre(nodo_actual);
        }
      }
    } else if (MovimientoValido(coordenadas_vecino) && !NodoAbierto(coordenadas_vecino, nodos_abiertos, iterador) && !NodoCerrado(coordenadas_vecino, nodos_cerrados)) {
      if (i >= 4) {
        Nodo* nodo_vecino = new Nodo(coordenadas_vecino, nodo_actual->GetCosteAcumulado() + 7, nodo_actual->GetCosteEstimado(), nodo_actual);
        nodo_vecino->FuncionHeuristica(posicion_final_, opcion);
        nodos_abiertos.push_back(nodo_vecino);
      } else {
        Nodo* nodo_vecino = new Nodo(coordenadas_vecino, nodo_actual->GetCosteAcumulado() + 5, nodo_actual->GetCosteEstimado(), nodo_actual);
        nodo_vecino->FuncionHeuristica(posicion_final_, opcion);
        nodos_abiertos.push_back(nodo_vecino);
      }
    }
  }
}
/**
 * @name BusquedaAEstrella
 * 
 * @brief Realiza la búsqueda A*
 * @param camino Vector que contiene el camino
 * @param nodos_abiertos Vector que contiene los nodos abiertos
 * @param nodos_cerrados Vector que contiene los nodos cerrados
 * @param opcion Opción que indica la heurística a utilizar
 * @return No devuelve nada
 * 
*/
void Laberinto::BusquedaAEstrella(std::vector<Nodo*>& camino, std::vector<Nodo*>& nodos_abiertos, std::vector<Nodo*>& nodos_cerrados, int opcion) {
  Nodo* nodo_inicial = new Nodo(posicion_inicial_);
  nodo_inicial->FuncionHeuristica(posicion_final_, opcion);
  nodos_abiertos.push_back(nodo_inicial);
  while (!nodos_abiertos.empty()) {
    if (nodos_abiertos.size() > 1) {
      for (unsigned i = 0; i < nodos_abiertos.size(); i++) {
        if (nodos_abiertos[i]->GetCosteTotal() < nodos_abiertos[0]->GetCosteTotal()) {
          std::swap(nodos_abiertos[i], nodos_abiertos[0]);
        }
      }
    }
    Nodo* nodo_actual = nodos_abiertos[0];
    nodos_abiertos.erase(nodos_abiertos.begin());
    nodos_cerrados.push_back(nodo_actual);
    if (nodo_actual->GetCoordenadas() == posicion_final_) {
      std::cout << "Camino encontrado" << std::endl;
      std::cout << "Coste total: " << nodo_actual->GetCosteTotal() << std::endl;
      while (nodo_actual->GetCoordenadas() != posicion_inicial_) {
        camino.push_back(nodo_actual);
        nodo_actual = nodo_actual->GetPadre();
      }
      camino.push_back(nodo_actual);
      std::cout << "Nodos abiertos: ";
      for (unsigned i = 0; i < nodos_abiertos.size(); i++) {
        std::cout << "(" << nodos_abiertos[i]->GetCoordenadas().first + 1 << ", " << nodos_abiertos[i]->GetCoordenadas().second + 1 << ") ";
      }
      std::cout << std::endl << "Nodos cerrados: ";
      for (unsigned i = 0; i < nodos_cerrados.size(); i++) {
        std::cout << "(" << nodos_cerrados[i]->GetCoordenadas().first + 1 << ", " << nodos_cerrados[i]->GetCoordenadas().second + 1 << ") ";
      }
      std::cout << std::endl;
      return;
    }
    GetPosiblesVecinos(nodos_abiertos, nodos_cerrados,nodo_actual, opcion);
  }
  std::cout << "No se ha encontrado camino" << std::endl;
}