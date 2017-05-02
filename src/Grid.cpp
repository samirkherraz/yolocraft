#include "Grid.h"

Grid::Grid()
{
Common::_Grid++;

    size = Point(0, 0);
    parent = NULL;
    life = 0;
    dammage = 0;
    id = Common::gridID;
    Common::gridID++;
    
}

Grid::~Grid()
{
    Common::_Grid--;
	for(auto p : parts){
		delete p.obj;
		}
    parts.clear();
}

int Grid::getDammage()
{

    return dammage;
}



void Grid::setLife(int i)
{

    life +=i;
}
int Grid::getLife()
{
    cout << "life :"<< life << endl;
    return life;
}
void* Grid::getParent()
{
    return parent;
}
void Grid::setParent(void* p)
{
    parent = p;
}

void Grid::loseLife(unsigned int dammage)
{
    life -= dammage;
    if(life < 0)
	life = 0;
}

void Grid::addPart(Point pos, AbstractObject* part)
{

    AbstractObjectPart p;
    p.obj = part != NULL ? new AbstractObject(part) : new AbstractObject();
    p.pos = pos;

    size.x = max(size.x - 1, pos.x) + 1;
    size.y = max(size.y - 1, pos.y) + 1;

    if(part != NULL) {
	dammage += part->getDammage();
	life += part->getLife();
    }
    parts.push_back(p);
}


int Grid::getChildrenLife()
{

    int _life = 0;
    for(auto p : parts) {
        if(p.obj == NULL)
            continue;
        _life += p.obj->getLife();
    }
    return _life;
}

void Grid::removePart(Point pos)
{
    int i = getPosOfPart(pos);
    if(i != -1)
	parts.erase(parts.begin() + i);
}

int Grid::getPosOfPart(Point pos)
{
    unsigned int i;
    bool found = false;
    for(i = 0; i < parts.size(); ++i) {

	if(parts.at(i).pos == pos) {
	    found = true;
	    break;
	}
    }

    if(found)
	return i;
    else
	return -1;
}

AbstractObject* Grid::getPart(Point pos)
{
    int i = getPosOfPart(pos);
    if(i != -1)
	return parts.at(i).obj;
    else
	return NULL;
}

Point Grid::getSize()
{
    return size;
}

string Grid::getHash()
{
    hash = id;
    for(auto part : parts) {
        if(part.obj != NULL)
            hash += part.obj->getType();
    }

    return hash;
}
