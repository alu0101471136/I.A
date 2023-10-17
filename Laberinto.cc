#include <fstream>
#include "Nodo.h"
#include "Laberinto.h"

Laberinto::Laberinto(std::string nombre_fichero) {
  std::ifstream fichero(nombre_fichero);
  std::string linea;
  int identificador = 0;
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