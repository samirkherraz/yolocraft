#ifndef MOBILE_H
#define MOBILE_H
#include <vector>
#include <Box2D/Box2D.h>
#include "Point.h"
#include "Grid.h"
#include "Common.h"
#include "ContactListner.h"
/**@brief La classe Mobile permet d'appliquer une force sur un objet se trouvant à une position donnée. Cela a pour effet de bouger l'objet. 
 * @param position: Point ou la force sera appliquée. 
 * @param forces: Pointeur sur un tableau de b2RevoluteJoint. Permet de décrir les forces à appliquer. 
 * */
class Mobile : public Grid
{

public:
    Mobile();
    virtual ~Mobile();
    Point getPosition() const;
    void setIndex(int i);
    void setPosition(Point new_position);
    void addMotorJoint(b2RevoluteJoint* fix);
    void addRocket(b2Body* fix);
    void removeRocket(b2Body* fix);
    unsigned int getNbRocket() const;
    void Fire(Point target);
/**@brief resetForce permet d'arrêter le moteur et de mettre la force à 0.
 * @param none.
 * @return none. 
 * */
    void ResetForce();
    void ApplyBrackImpulse(double force);
    void setB2Mobile(b2Body* newMobile);
    void setB2ContactListener(ContactListner* l);

    b2Body* getB2Mobile();

    void ApplyLinearImpulse(double force);
    void Jump();

protected:
    unsigned int lastFire = 0;
    void* world;
    int index;
    ContactListner* listener;
    b2Body* box2dmobile;
    Point position;
    vector<b2RevoluteJoint*> motors;
    vector<b2Body*> fires;
};

#endif // MOBILE_H