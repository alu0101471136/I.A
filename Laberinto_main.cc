/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Inteligencia Artificial 2023-2024
  *
  * @file laberinto_main.cc
  * @author Raúl Álvarez Pérez alu0101471136@ull.edu.es
  * @date Oct 17 2023
  * @brief Este es el programa main de laberinto
  * @bug No existen fallos conocidos
  */
#include <iostream>
#include <fstream>
#include "Laberinto.h"

int main(int argc, char* argv[]) {
  std::string fichero{argv[1]};
  Laberinto laberinto(fichero);
  laberinto.MostrarLaberinto();
  return 0;
}