#include "Map.h"

Map::Map()
{
Common::_Map++;

    background = "";
    foreground = "";
}

Map::~Map()
{
Common::_Map--;
    ground.clear();
    background = "";
    foreground = "";
}

string Map::getBackGround()
{

    return background;
}

void Map::setBackGround(string _background)
{

    background = _background;
}

string Map::getForeGround()
{

    return foreground;
}

void Map::setForeGround(string _foreground)
{

    foreground = _foreground;
}

vector<Point> Map::getGround()
{

    return ground;
}

void Map::setGround(vector<Point> _ground)
{
    ground = _ground;
}

Point Map::getSize()
{
    Point max(0, 0);

    for(unsigned int i = 0; i < ground.size(); i++) {

        if(ground.at(i).x > max.x)
            max.x = ground.at(i).x;
        if(ground.at(i).y > max.y)
            max.y = ground.at(i).y;
    }

    return max;
}
