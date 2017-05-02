#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <Box2D/Box2D.h>
#include "Mobile.h"
#include "Common.h"

using namespace std;
/**@brief Cette classe permet de définir un joueur et de le gérer. 
*/
class Player
{

private:
    string name;
    Mobile* mobile;
    b2Body* box2dmobile;
    unsigned int wallet;
    bool dead;
    Point fireTarget;
    vector<AbstractObject*> my_shapes;

public:
    Player();
    Player(string _name);
    virtual ~Player();

    void newGain(unsigned int amount);  /**@briefAjoute amount au wallet*/
    void loseGain(unsigned int amount); /**@brief Retire amount au wallet*/
    unsigned int getGain();             /**@brief Renvoie le wallet*/

    void buyShape(AbstractObject* part);
    vector<AbstractObject*> getShapes();

    void setMobile(Mobile* newMobile); /**@brief Défini le mobile*/
    Mobile* getMobile();               /**@brief Renvoie le mobile*/

    void setName(string newName); /** @brief Défini le nom du player*/
    string getName();             /** @brief Renvoie le nom du player*/
    void doAction(int ACTION);
    void setB2Mobile(b2Body* newMobile);
    b2Body* getB2Mobile();
    void setFireTarget(Point target);

    void live();

    bool isDead();

    void die();
};
#endif
