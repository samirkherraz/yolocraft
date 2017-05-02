#ifndef ABSTRACOBJET_H
#define ABSTRACOBJET_H

#include "Point.h"
#include <iostream>

using namespace std;
/** @breif La classe AbstractObject permet de générer un objet quelconque du véhicule, c'est à dire: une roue, une arme ou le bodyshape.Chaque oubjet est défini par une position, une taille, 
 * un poids, un état et un type.
 * @attr position: un point position dans l'écran 
 * @attr size: doit être supprimé
 * @attr weight: le poids de l'objet
 * @attr life: indique l'état de l'objet
 * @attr type: indique le type de l'objet (i.e: roue, arme, bodyshape) 
 * */
class AbstractObject
{
private:
    Point position;
    Point size;
    unsigned int weight;
    unsigned int life;
    unsigned int dammage;
    unsigned int type;

public:
    // Constructeur par default
    AbstractObject();

    // Constructeur par copie pointeur
    AbstractObject(AbstractObject* ao);
    
    // Constructeur par copie
    AbstractObject(const AbstractObject& ao);

    ~AbstractObject();
/**@brief Les fonctions suivantes sont des getteurs. 
 * @param none
 * @return la valeur de l'attribut demandé.
 * */
    Point getPosition() const;
    Point getSize() const;

    unsigned int getWeight() const;
    unsigned int getLife() const;
    unsigned int getDammage() const;
    unsigned int getType() const;
/**@brief Les procédures suivantes sont des mutateurs.
 * @param la nouvelle valeur de l'attribut à modifier.
 * @return none 
 * */
    void setPosition(Point new_position);
    void setSize(Point new_size);
    void setWeight(unsigned int new_weight);
    void setDammage(unsigned int new_dammage);
    void setLife(unsigned int new_life);
    void setType(unsigned int new_type);

    void regressionTest();
};

#endif
