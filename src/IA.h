#ifndef IA_H
#define IA_H

#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#include "Common.h"
#include "Player.h"
#include "Mobile.h"
#include "Point.h"
#include "SDL.h"
#include "AbstractObject.h"

using namespace std;

/**
	@brief: Classe définissant et permettant aux IA d'être déplacées et de tirer
*/
class IA
{

private:

Player * player, * ia;
double precision, distance, reaction;
time_t lastShoot, lastMove;

public:

/**
	@brief: Constructeur de l'IA sans joueur ni nom
*/
IA();
/**
	@brief: Constructeur de l'IA avec un nom défini pour son Player et le joueur humain
	@param name: le nom de l'IA
	@param j: le pointeur sur le joueur humain
*/
IA(string name, Player * j);
/**
	@brief: Destructeur de la classe
*/
~IA();

/**
	@brief: Permet de définir ou redéfinir le pointeur vers le joueur principal pour chaque IA
	@param new_player: Pointeur vers le joueur humain
*/
void setPlayer(Player * new_player);

/**
	@brief: Renvoie le pointeur vers le joueur principal
*/
Player * getPlayer();

/**
	@brief: Définit le pointeur vers le player de l'IA
	@param new_player: Pointeur vers le joueur IA
*/
void setIA(Player * new_ia);

/**
	@brief: Renvoie le pointeur du player de l'IA
*/
Player * getIA();

/**
	@brief: Renvoie le pointeur vers le mobile du player l'IA
*/
Mobile * getMobile();

/**
	@brief: Définit les actions de chaque étape de mouvement
*/
void step();

/**
	@brief: Renvoie la différence entre la position de l'IA et celle du joueur pour définir le sens du mouvement
*/
int getDistanceFromPlayer();

/**
	@brief: Tire
*/
void shoot();

/**
	@brief: Bouge
*/
void move();

/**
	@brief: Affiche les données de l'objet
*/
void afficheDonnees();

/**
	@brief: Définit selon which un véhicule pour l'IA
	@param start_position: Point auquel faire apparaître le véhicule
	@param which: Entier choisissant le véhicule
*/
void defineMobile(Point start_position, int which);

};
#endif

