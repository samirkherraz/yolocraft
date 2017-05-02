#include "ContactListner.h"

ContactListner::ContactListner()
{
Common::_ContactListner++;
}

void ContactListner::catchObject(b2Body* body1)
{
    objects.push_back(body1);
}

void ContactListner::catchWithMap(b2Body* body1)
{
    objectsMap.push_back(body1);
}

void ContactListner::setMap(b2Body* m)
{
    map = m;
}

void ContactListner::removeObject(b2Body* body1)
{
    for(unsigned int i = 0; i < objects.size(); i++) {
        if(body1 == objects.at(i)) {
            objects.erase(objects.begin() + i);
            i--;
        }
    }

    for(unsigned int i = 0; i < objectsMap.size(); i++) {
        if(body1 == objectsMap.at(i)) {
            objectsMap.erase(objectsMap.begin() + i);
            i--;
        }
    }

    for(unsigned int i = 0; i < destructions.size(); i++) {
        if(body1 == destructions.at(i)) {
            destructions.erase(destructions.begin() + i);
            i--;
        }
    }
}

vector<b2Body*> ContactListner::getDestructions()
{
    return destructions;
}

void ContactListner::resetDestructions()
{
    destructions.clear();
}
void ContactListner::BeginContact(b2Contact* contact)
{

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* body1 = fixtureA->GetBody();
    b2Body* body2 = fixtureB->GetBody();
    b2Body* collidWithMap = NULL;

    bool except = true;
    bool body1IsCatched = false;
    bool body2IsCatched = false;

    Grid* m1 = static_cast<Grid*>(body1->GetUserData());
    Grid* m2 = static_cast<Grid*>(body2->GetUserData());

    if(m1->getParent() == m2->getParent()) {
        return;
    }

    for(unsigned int i = 0; i < objects.size(); i++) {
        if(body1 == objects.at(i)) {
            body1IsCatched = true;
        } else if(body2 == objects.at(i)) {
            body2IsCatched = true;
        } else if(body1 == map) {
            for(unsigned int i = 0; i < objectsMap.size(); i++) {
                if(objectsMap.at(i) == body2) {
                    collidWithMap = body2;
                    except = false;
                    break;
                }
            }
        } else if(body2 == map) {
            for(unsigned int i = 0; i < objectsMap.size(); i++) {
                if(objectsMap.at(i) == body1) {
                    collidWithMap = body1;
                    except = false;
                    break;
                }
            }
        }

        if((body1IsCatched && body2IsCatched) || collidWithMap != NULL) {
            except = false;
            break;
        }
    }

    if(!except) {

        if(collidWithMap != NULL) {
            Grid* m = static_cast<Grid*>(collidWithMap->GetUserData());
            m->loseLife(100);

            if(m->getLife() == 0)
                destruct(collidWithMap);

        } else {
            if(body1IsCatched)
                m1->loseLife(m2->getDammage());
            if(body2IsCatched)
                m2->loseLife(m1->getDammage());

            if(m1 != NULL && m1->getLife() == 0)
                destruct(body1);
            if(m2 != NULL && m2->getLife() == 0)
                destruct(body2);
        }
    }
}

void ContactListner::destruct(b2Body* body)
{
    bool found = false;
    for(auto* b : destructions) {
        if(body == b) {
            found = true;
            break;
        }
    }

    if(!found)
        destructions.push_back(body);
}

void ContactListner::EndContact(b2Contact* contact)
{
}

ContactListner::~ContactListner()
{
    Common::_ContactListner--;
    destructions.clear();
    objects.clear();
    objectsMap.clear();
    map = NULL;
}