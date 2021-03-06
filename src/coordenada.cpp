#include "coordenada.h"

#define VACIA 0
#define OCUPADA 1

Coordenada::Coordenada(int estado, Terreno terreno): estado(estado), 
terreno(terreno) {}

bool Coordenada::poner_objeto(std::shared_ptr<ObjetoDune> objeto_dune) {
	if (estado == OCUPADA) {
		return false;
	} else {
		objeto = objeto_dune;
		estado = OCUPADA;
		return true;
	}
}

std::string Coordenada::obtener_terreno() {
	return terreno.obtener_nombre_material();
}

void Coordenada::sacar_objeto() {
	objeto = NULL;
	estado = VACIA;
}

bool Coordenada::esta_ocupada() {
	if(estado == OCUPADA) return true;
	return false;
}

int Coordenada::obtener_id_objeto_contenido() {
	return objeto->pedir_id();
}