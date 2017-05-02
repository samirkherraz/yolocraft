
#include "AbstractObject.h"

AbstractObject::AbstractObject()
{

  //  Common::AbstractObject++;

    position.x = 0;
    position.y = 0;
    size.x = 0;
    size.y = 0;
    life = 100;
    dammage = 1;
    type = -1;
}


AbstractObject::AbstractObject(AbstractObject * ao)
{
//Common::AbstractObject++;

    position.x = ao->position.x;
    position.y = ao->position.y;
    size.x = ao->size.x;
    size.y = ao->size.y;
    life = ao->life;
    dammage = ao->dammage;
    type = ao->type;
}
AbstractObject::AbstractObject(const AbstractObject &ao)
{
   // Common::AbstractObject++;

    position.x = ao.position.x;
    position.y = ao.position.y;
    size.x = ao.size.x;
    size.y = ao.size.y;
    life = ao.life;
    dammage = ao.dammage;
    type = ao.type;
}



AbstractObject::~AbstractObject()
{
  //  Common::AbstractObject--;

}
Point AbstractObject::getPosition()const
{

    return position;
}
Point AbstractObject::getSize()const
{

    return size;
}
unsigned int AbstractObject::getWeight()const
{
    return weight;
}

unsigned int AbstractObject::getLife()const
{
    
    return life;
}

unsigned int AbstractObject::getType()const
{

    return type;
}


unsigned int AbstractObject::getDammage()const
{

    return dammage;
}
void AbstractObject::setDammage(unsigned int new_dammage)
{

    dammage = new_dammage;
}

void AbstractObject::setPosition(Point new_position)
{
    position = new_position;
}
void AbstractObject::setSize(Point new_size)
{
    size = new_size;
}
void AbstractObject::setWeight(unsigned int new_weight)
{
    weight = new_weight;
}
void AbstractObject::setLife(unsigned int new_life)
{
    life = new_life;
}
void AbstractObject::setType(unsigned int new_type)
{
    type = new_type;
}

void AbstractObject::regressionTest()
{

    AbstractObject atest;

    Point ptest;
    Point tpos(4, 4);
    Point tsize(1, 2);

    unsigned int tweight = 2, tlife = 3;
    unsigned int ttype = 10;

    cout << "Regression test for AbstractObject class" << endl;
    cout << "_________Test contenant of data member_________" << endl;
    assert(typeid(position) == typeid(ptest));
    cout << "the position (" << position.x << "," << position.y << ") is ok" << endl;
    assert(typeid(size) == typeid(ptest));
    cout << "the size(" << size.x << "," << size.y << ") is ok" << endl;
    assert(typeid(weight) == typeid(unsigned int));
    cout << "weight " << weight << " is ok" << endl;
    assert(typeid(life) == typeid(unsigned int));
    cout << "life " << life << " is ok" << endl;
    assert(typeid(type) == typeid(int));
    cout << "type " << type << " is ok" << endl;

    cout << "_________Test returns of getteurs_________" << endl;
    assert(typeid(atest.getPosition()) == typeid(ptest));
    cout << "getPosition() returns a Point" << endl;
    assert(typeid(atest.getSize()) == typeid(ptest));
    cout << "getSize() returns a Point" << endl;
    assert(typeid(atest.getWeight()) == typeid(unsigned int));
    cout << "getWeight() returns an unsigned int " << endl;
    assert(typeid(atest.getLife()) == typeid(unsigned int));
    cout << "getLife() returns an unsigned int " << endl;
    assert(typeid(atest.getType()) == typeid(int));
    cout << "getType() returns an int " << endl;

    cout << "_________Test changement of member data_________" << endl;
    atest.setPosition(tpos);
    assert(atest.getPosition() == tpos);
    cout << "the new position of this point is: (" << tpos.x << "," << tpos.y << ")" << endl;

    atest.setSize(tsize);
    assert(atest.getSize() == tsize);
    cout << "the new size of this point is: (" << tsize.x << "," << tsize.y << ")" << endl;

    atest.setWeight(tweight);
    assert(atest.getWeight() == tweight);
    cout << "its new weight is: " << tweight << endl;

    atest.setLife(tlife);
    assert(atest.getLife() == tlife);
    cout << "its new life score is: " << tlife << endl;

    atest.setType(ttype);
    assert(atest.getType() == ttype);
    cout << "its new type is: " << ttype << endl;
}

