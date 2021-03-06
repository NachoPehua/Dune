#include "fabrica_unidades_movibles.h"
#include "infanteria_ligera.h"
#include "infanteria_pesada.h"
#include "fremen.h"
#include "sardaukar.h"
#include "trike.h"
#include "raider.h"
#include "tanque.h"
#include "tanque_sonico.h"
#include "desviador.h"
#include "devastador.h"
#include "cosechadora.h"

#define INFANTERIA_LIGERA 0
#define INFANTERIA_PESADA 1
#define FREMEN 2
#define SARDAUKAR 3
#define TRIKE 4
#define RAIDER 5
#define TANQUE 6
#define TANQUE_SONICO 7
#define DESVIADOR 8
#define DEVASTADOR 9
#define COSECHADORA 10

std::shared_ptr<UnidadMovible> FabricaUnidadesMovibles::
crear_unidad_movible(int id_tipo_unidad_movible, int id, 
int id_duenio, std::pair<int, int> centro) {
	if(id_tipo_unidad_movible == INFANTERIA_LIGERA) {
		std::shared_ptr<InfanteriaLigera> infanteria_ligera(
		new InfanteriaLigera(id, id_duenio, centro));
		return infanteria_ligera;
	} else if (id_tipo_unidad_movible == INFANTERIA_PESADA) {
		std::shared_ptr<InfanteriaPesada> infanteria_pesada(
		new InfanteriaPesada(id, id_duenio, centro));
		return infanteria_pesada;
	} else if (id_tipo_unidad_movible == FREMEN) {
		std::shared_ptr<Fremen> fremen(
		new Fremen(id, id_duenio, centro));
		return fremen;
	} else if (id_tipo_unidad_movible == SARDAUKAR) {
		std::shared_ptr<Sardaukar> sardaukar(new 
		Sardaukar(id, id_duenio, centro));
		return sardaukar;
	} else if (id_tipo_unidad_movible == TRIKE) {
		std::shared_ptr<Trike> trike(
		new Trike(id, id_duenio, centro));
		return trike;
	} else if (id_tipo_unidad_movible == RAIDER) {
		std::shared_ptr<Raider> raider(
		new Raider(id, id_duenio, centro));
		return raider;
	} else if (id_tipo_unidad_movible == TANQUE) {
		std::shared_ptr<Tanque> tanque(
		new Tanque(id, id_duenio, centro));
		return tanque;
	} else if (id_tipo_unidad_movible == TANQUE_SONICO) {
		std::shared_ptr<TanqueSonico> tanque_sonico(
		new TanqueSonico(id, id_duenio, centro));
		return tanque_sonico;
	} else if (id_tipo_unidad_movible == DESVIADOR) {
		std::shared_ptr<Desviador> desviador(
		new Desviador(id, id_duenio, centro));
		return desviador;
	} else if (id_tipo_unidad_movible == DEVASTADOR) {
		std::shared_ptr<Devastador> devastador(
		new Devastador(id, id_duenio, centro));
		return devastador;
	} else {
		std::shared_ptr<Cosechadora> cosechadora(
		new Cosechadora(id, id_duenio, centro));
		return cosechadora;
	}
}