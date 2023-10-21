#include <fstream>
#include "Nodo.h"
#include "Laberinto.h"

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

void Laberinto::MostrarLaberinto() {
  std::cout << "Posicion inicial: " << posicion_inicial_.first + 1 << " " << posicion_inicial_.second + 1 << std::endl;
    std::cout << "Posicion final: " << posicion_final_.first + 1 << " " << posicion_final_.second + 1 << std::endl;
  for (int i = 0; i < numero_filas_; i++) {
    for (int j = 0; j < numero_columnas_; j++) {
      std::cout << laberinto_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool Laberinto::MovimientoValido(std::pair<int,int> coordenadas) {
  if (coordenadas.first < 0 || coordenadas.first > numero_filas_ || coordenadas.second < 0 || coordenadas.second > numero_columnas_) {
    return false;
  } else if (laberinto_[coordenadas.first][coordenadas.second] == 1) {
    return false;
  }
  return true;
}

bool Laberinto::NodoAbierto(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_abiertos, int& iterador) {
  for (unsigned i = 0; i < nodos_abiertos.size(); i++) {
    if (nodos_abiertos[i]->GetCoordenadas() == coordenadas) {
      iterador = i;
      return true;
    }
  }
  return false;
}

bool Laberinto::NodoCerrado(std::pair<int,int> coordenadas, std::vector<Nodo*>& nodos_cerrados) {
  for (unsigned i = 0; i < nodos_cerrados.size(); i++) {
    if (nodos_cerrados[i]->GetCoordenadas() == coordenadas) {
      return true;
    }
  }
  return false;
}

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
      while (nodo_actual->GetCoordenadas() != posicion_inicial_) {
        camino.push_back(nodo_actual);
        nodo_actual = nodo_actual->GetPadre();
      }
      camino.push_back(nodo_actual);
      for (int i = camino.size() - 1; i >= 0; i--) {
        std::cout << camino[i]->GetCoordenadas().first + 1 << " " << camino[i]->GetCoordenadas().second + 1 << std::endl;
      }
      return;
    }
    GetPosiblesVecinos(nodos_abiertos, nodos_cerrados,nodo_actual, opcion);
  }
  std::cout << "No se ha encontrado camino" << std::endl;
}