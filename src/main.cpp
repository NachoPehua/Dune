#include "partida.h"
#include "UnidadesMovibles/raider.h"
#include "UnidadesMovibles/fabrica_unidades_movibles.h"
#include "UnidadesMovibles/unidad_movible.h"
#include "mapa.h"
#include "buscador_mejor_camino.h"
#include <iostream>
#include "nodo.h"
#include <vector>
#include <stack>
#include <cmath>
#include <iostream>

#define POSICION_INHABILITADA 1

/*int main() {
	//parametros
	std::pair<int ,int> inicio(0, 0);
	std::vector<std::vector<int>> mapa;
	std::pair<int, int> final(3, 1);
	//fin parametros

	for (int i = 0; i < 10; i++) {
		std::vector<int> fila;
		for (int j = 0; j < 10; j++) {
			fila.push_back(0);
		}
		mapa.push_back(fila);
	}
	mapa[1][1] = 1;
	mapa[2][1] = 1;

	Nodo nodo_inicio(NULL, inicio);
	nodo_inicio.poner_valor_g(0);
	nodo_inicio.poner_valor_h(0);
	Nodo nodo_final(NULL, final);

	std::vector<Nodo> posibles_nodos;
	std::vector<Nodo> nodos_visitados;

	posibles_nodos.push_back(nodo_inicio);

	while(posibles_nodos.size() > 0) {
		Nodo nodo_evaluado = posibles_nodos[0];
		int indice_nodo_evaluado = 0;
		int indice_auxiliar = 0;

		//Me quedo con el nodo de menor valor F
		for (std::vector<Nodo>::iterator it = posibles_nodos.begin(); 
  		it != posibles_nodos.end(); ++it) {
  			if ((*it).obtener_valor_f() < nodo_evaluado.obtener_valor_f()) {
  				nodo_evaluado = (*it);
  				indice_nodo_evaluado = indice_auxiliar;
  			}
  			indice_auxiliar++;
  		}

  		posibles_nodos.erase(posibles_nodos.begin() + indice_nodo_evaluado);
  		nodos_visitados.push_back(nodo_evaluado);

  		//Me fijo si llegue al nodo/posicion final y si es asi obtengo
  		//pila con camino
  		if (nodo_evaluado == nodo_final) {
  			std::stack<Nodo> camino;
  			Nodo nodo_actual = nodo_evaluado;
  			while(nodo_actual.obtener_padre() != NULL) {
  				camino.push(nodo_actual);
  				nodo_actual = *(nodo_actual.obtener_padre());
  			}
  			while (!camino.empty()) {
  				Nodo nodo = camino.top();
  				std::cout << std::get<0>(nodo.obtener_posicion()) << " " << std::get<1>(nodo.obtener_posicion()) << std::endl;
  				camino.pop();
  			}
  			for (std::vector<Nodo>::iterator it_posibles = posibles_nodos.
  			begin(); it_posibles != posibles_nodos.end(); ++it_posibles) {
  				if ((*it_posibles).obtener_padre()) {
  					delete ((*it_posibles).obtener_padre());
  				}
  			}

  			for (std::vector<Nodo>::iterator it_posibles = nodos_visitados.
  			begin(); it_posibles != nodos_visitados.end(); ++it_posibles) {
  				if ((*it_posibles).obtener_padre()) {
  					delete ((*it_posibles).obtener_padre());
  				}
  			}

  			break;
  		}

  		//Reviso hijos del nodo donde estoy parado para ver cuales faltan
  		//agregar a la lista de caminos posibles
  		std::vector<std::pair<int, int>> direcciones = {{0, 1}, {1, 0}, {-1,0}, 
  		{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, -1}};
  		std::vector<Nodo> nodos_hijos;
  		for (std::vector<std::pair<int, int>>::iterator it = direcciones.begin(); 
  		it != direcciones.end(); ++it) {
  			std::pair<int, int> posicion_adyacente((std::get<0>(nodo_evaluado.
  			obtener_posicion())) + it->first, (std::get<1>(nodo_evaluado.
  			obtener_posicion())) + it->second);

  			//Verfico que no se evalue una posicion fuera del mapa
  			if (std::get<0>(posicion_adyacente) > (int)(mapa.size() - 1) || 
  			std::get<0>(posicion_adyacente) < 0 || std::get<1>
  			(posicion_adyacente) > (int)(mapa[mapa.size() - 1]).size() || 
  			std::get<1>(posicion_adyacente) < 0) {
  				continue;
  			} 

  			//Evaluo el terreno. VER DIFERENTES TERRENOS Y MOVILIDADES
  			if (mapa[std::get<0>(posicion_adyacente)][std::get<1>
  			(posicion_adyacente)] == POSICION_INHABILITADA) {
  				continue;
  			}
  			Nodo *nodo_aux = new Nodo(nodo_evaluado);
  			Nodo nodo_nuevo(nodo_aux, posicion_adyacente);
  			nodos_hijos.push_back(nodo_nuevo);
  		}

  		std::vector<Nodo> no_agregados;
  		//Reviso nodos adyacentes, les asigno su valor g, h y f
  		//y los agrego en la lista de posibles nodos
  		for (std::vector<Nodo>::iterator it_hijos = nodos_hijos.begin(); 
  		it_hijos != nodos_hijos.end(); ++it_hijos) {
  			bool no_agregar = false;

  			//Si el nodo esta en dentro de los nodos visitados no lo evaluo
  			for (std::vector<Nodo>::iterator it_visitados = nodos_visitados.
  			begin(); it_visitados != nodos_visitados.end(); ++it_visitados) {
  				if ((*it_visitados) == (*it_hijos)) { 
  					no_agregar = true;
  				}
  			}

  			if (no_agregar) {
  				no_agregados.push_back(*it_hijos);
  				continue;
  			}

  			//G sera la distancia (cantidad de nodos, distancia manhattan)
  			//al nodo de inicio
  			(*it_hijos).poner_valor_g(nodo_evaluado.obtener_valor_g() + 1);
  			//H es una heuristica, es la distancia estimada desde el nodo
  			//evaluado hasta el nodo final (hago: los nodos que me faltan ir
  			//de manera horizontal al cuadrado mas los nodos que me faltan ir
  			//en linea vertical al cuadrado
  			(*it_hijos).poner_valor_h(pow(std::get<0>((*it_hijos).
  			obtener_posicion()) - std::get<0>(nodo_final.obtener_posicion()),2)
  			+ pow(std::get<1>((*it_hijos).obtener_posicion()) - std::get<1>
  			(nodo_final.obtener_posicion()),2));

  			//Si el nodo esta entre los posibles ya tenidos en cuenta
  			//y ademas su valor g es mayor, entonces no se agrega
  			for (std::vector<Nodo>::iterator it_posibles = posibles_nodos.
  			begin(); it_posibles != posibles_nodos.end(); ++it_posibles) {
  				if (((*it_hijos) == (*it_posibles)) && ((*it_hijos).
  				obtener_valor_g() > (*it_posibles).obtener_valor_g())) { 
  					no_agregar = true;
  				}
  			}

  			if (no_agregar) {
  				no_agregados.push_back(*it_hijos);
  				continue;
  			}

  			posibles_nodos.push_back(*it_hijos);
  		}

  		for (std::vector<Nodo>::iterator it_no_agregados = no_agregados.
  		begin(); it_no_agregados != no_agregados.end(); ++it_no_agregados) {
  			delete ((*it_no_agregados).obtener_padre());
  		}

	}
}*/
/*
int main() {
 Partida partida;
  partida.agregar_jugador("je");
  partida.agregar_jugador("asd");
  bool agregado = partida.agregar_edificio(0, std::pair<int, int>(400,400), 4);
  int danio = partida.atacar_edificio(0, 5, 0);
  std::cout << danio << agregado << std::endl;
  //std::cout << agregado;
  //Mapa mapa;
  //std::pair<int, int> objetivo = mapa.desenterrar_gusano();
  //std::cout << objetivo.first << " " << objetivo.second << std::endl;
}

*/int main() {
  Mapa mapa;

  BuscadorMejorCamino buscador;
  std::pair<int ,int> inicio(0, 0);
  std::pair<int, int> final(5, 5);
  buscador.buscar_mejor_camino(mapa, inicio, final);
  Partida partida;
  partida.agregar_jugador("harkonnen");
  //std::cout << partida.agregar_unidad(0,2, std::pair<int, int>(100,100), 5) << std::endl;
  std::cout << partida.agregar_edificio(0, std::pair<int, int>(400,400), 4) << std::endl;
  for (int i = 0; i < 26 ; i++){
    std::cout << partida.agregar_unidad(0,0,5) << std::endl;
  }
}