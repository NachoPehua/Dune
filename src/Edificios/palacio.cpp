#include "palacio.h"

#define ID_PALACIO 7 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Palacio::Palacio(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(800, 2000, std::pair<int, int>(3, 3), 1000, id, id_duenio,
	300, 300, centro) {
		id_tipo = ID_PALACIO;
	}

void Palacio::crear_infanteria_avanzada(std::string nombre_infanteria) {

}