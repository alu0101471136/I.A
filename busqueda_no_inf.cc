#include <iostream>
#include "Vertice.h"
#include "ArbolBusqueda.h"

int main(int argc, char* argv[]) {
  std::string informacion_fichero{argv[1]};
  ArbolBusqueda arbol(informacion_fichero);
  int opcion{0};
  std::cout << "¿Qué desea hacer?" << std::endl;
  std::cout << "1. Busqueda en anchura" << std::endl;
  std::cout << "2. Busqueda en profundidad" << std::endl;
  std::cin >> opcion;
  std::cout << "¿Cuál es el vertice inicial?" << std::endl;
  int vertice_aux{0};
  std::cin >> vertice_aux;
  Vertice vertice_inicial(vertice_aux);
  std::cout << "¿Cuál es el vertice final?" << std::endl;
  std::cin >> vertice_aux;
  if (vertice_aux < 0 || vertice_aux >= arbol.GetNumeroVertices()) {
    std::cout << "Vertice no válido" << std::endl;
    return 0;
  }
  Vertice vertice_final(vertice_aux);
  std::vector<Vertice> camino;
  std::vector<Vertice> vertices_visitados;
  std::vector<Vertice> vertices_generados;
  float distacia_camino{0};
  if (opcion == 1) {
    arbol.BusquedaAmplitud(vertice_inicial, vertice_final, camino, vertices_visitados, vertices_generados, distacia_camino);
    std::cout << "v0: " << vertice_inicial.GetId() << " | vd: " << vertice_final.GetId() << std::endl;
    std::cout << "Camino: ";
    for (int i = camino.size() - 1; i >= 0; --i) {
      if (i == 0) {
        std::cout << camino[i].GetId();
      } else {
        std::cout << camino[i].GetId() << "-";
      }
    }
    std::cout << "  " << "Vertices visitados: " << vertices_visitados[0].GetId();
    for (unsigned i = 1; i < vertices_visitados.size(); ++i) {
      std::cout << ", " << vertices_visitados[i].GetId();
    }
    std::cout << "  " << "Vertices generados: " << vertices_generados[0].GetId();
    for (unsigned i = 1; i < vertices_generados.size(); ++i) {
      std::cout << ", " << vertices_generados[i].GetId();
    }
    std::cout << "  " << std::endl << "Coste del camino: " << distacia_camino << std::endl;
  } else if (opcion == 2) {
    std::cout << "Busqueda en profundidad" << std::endl;
  } else {
    std::cout << "Opción no válida" << std::endl;
  }
}