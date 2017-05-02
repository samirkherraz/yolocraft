#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <iostream>
#include "Point.h"
#include "Common.h"
using namespace std;
/**@brief La classe Map permet de créer une carte dans laquelle le joueur va évoluer.
 * @param VectorPoint: est un vecteur de points.
 * @param background: est une chaine de caractères qui représentera l'arrière plan
 * @param foreground: est une chaine de caractères qui représentera l'avant plan
 * @param ground: est de type VectorPoint.C'est donc "le chemin" sur lequel le joueur va rouler.
 * */

class Map
{

private:
    string background;
    string foreground;
    vector<Point> ground;

public:
    Map();
    ~Map(); 
//getteur/mutateur
    string getBackGround();
    void setBackGround(string _background);

    string getForeGround();
    void setForeGround(string _foreground);

    vector<Point> getGround();
    void setGround(vector<Point> _ground);
/**@brief La fonctions getSize() permet de récupérer la taille de la carte.
 * @param none
 * @return le point le plus élogné de la carte*/
    Point getSize();

   
};

#endif
