/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file laberinto_main.cc
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Oct 24 2023
  * @brief Este es el programa main de laberinto
  * @bug No existen fallos conocidos
  */
#include <iostream>
#include <fstream>
#include "Laberinto.h"

int main(int argc, char* argv[]) {
  std::ofstream archivo("Solucion.txt", std::ios::trunc);
  std::string fichero{argv[1]};
  Laberinto laberinto(fichero);
  std::cout << "¿Desea cambiar las casillas de incio y final?" << std::endl;
  std::cout << "1. Sí   2. No" << std::endl;
  int opcion;
  std::cin >> opcion;
  if (opcion == 1) {
    std::cout << "Introduzca las coordenadas de la casilla de inicio: " << std::endl;
    int fila, columna;
    std::cin >> fila >> columna;
    laberinto.SetPosicionInicial(std::make_pair(fila - 1, columna - 1));
    std::cout << "Introduzca las coordenadas de la casilla de final: " << std::endl;
    std::cin >> fila >> columna;
    laberinto.SetPosicionFinal(std::make_pair(fila - 1, columna - 1));
  } else if (opcion != 2) {
    std::cout << "No existe esa opción" << std::endl;
    return 0;
  }
  std::cout << "¿Qué heurística desea utilizar?" << std::endl;
  std::cout << "1. Distancia Manhattan   2. Distancia Euclídea   3. Distancia Propia" << std::endl;
  std::cin >> opcion;
  if (opcion < 1 || opcion > 3) {
    std::cout << "No existe esa opción" << std::endl;
    return 0;
  }
  int condicion_parada{0};
  std::vector<Nodo*> camino;
  std::vector<Nodo*> nodos_abiertos;
  std::vector<Nodo*> nodos_cerrados;
  do {
  laberinto.BusquedaAEstrella(camino, nodos_abiertos, nodos_cerrados, opcion);
  laberinto.MarcarCamino(camino);
  laberinto.MostrarLaberinto(nodos_abiertos, nodos_cerrados, camino);
  laberinto.DesmarcarCamino(camino);
  camino.clear();
  nodos_abiertos.clear();
  nodos_cerrados.clear();
  ++condicion_parada;
  } while (condicion_parada < 10);
  return 0;
} 