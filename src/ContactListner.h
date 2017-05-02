#ifndef CONTACTLISTNER_H
#define CONTACTLISTNER_H

#include <Box2D/Box2D.h>
#include "Grid.h"
using namespace std;

struct Contact
{
    b2Fixture* A;
    b2Fixture* B;
};


struct Group
{
    b2Body* A;
    b2Body* B;
};
 /**@brief La classe ContactListner permet de détécter les collisions entre deux objets distincts dans la map. 
  * @param destructions: les objets à détruire
  * @param objetcs: les objets courants
  * @param objetMap: 
  * @param map: la map 
  * */

class ContactListner : public b2ContactListener
{

private:
    vector<b2Body*> destructions;
    vector<b2Body*> objects;
    vector<b2Body*> objectsMap;
/**@brief Ajoute s'il existe body à destructions pour être détruit plus tard
 * @param body1: pointeur sur l'objet b2Body
 * @return none*/
	void destruct(b2Body* body);

	b2Body*map;
public:
/**@brief Ajoute un body à l'attribut objects
 * @param body1: pointeur sur l'objet b2Body
 * @return none*/
    void catchObject(b2Body* body1);
/**@brief Ajoute un body à l'attribut objectsMap
 * @param body1: pointeur sur l'objet b2Body
 * @return none*/
    void catchWithMap(b2Body* body1);
/**@brief mutateur de l'attribut map
 * @param body1: pointeur sur l'objet b2Body
 * @return none*/
    void setMap(b2Body* body1);
/**@brief supprime un body de la liste des objects, objetMap et destruction
 * @param body1: pointeur sur l'objet b2Body
 * @return none*/
    void removeObject(b2Body* body1);
/**@brief getteur de l'attribut destruction
 * @param none
 * @return vecteur de pointeur sur b2Body sui correspond à l'attribut destruction*/
    vector<b2Body*> getDestructions();
/**@brief supprime les éléments contenus dans destruction
 * @param none
 * @return none*/
    void resetDestructions();
/**@brief Detécte un début de collision
 * @param contact: pointeur sur l'objet b2Contact 
 * @return none*/
    virtual void BeginContact(b2Contact* contact);
/**@brief Detécte la fin de la collision
 * @param contact: pointeur sur l'objet b2Contact 
 * @return none*/
    virtual void EndContact(b2Contact* contact);
     ContactListner();
    virtual ~ContactListner();
};

#endif
