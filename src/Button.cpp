#include "Button.h"

Button::Button()
{
    pos = Point(0, 0);
    size = Point(0, 0);
    type = 0;
    onclick = NOACTION;
    name = "";
    status = UNSELECTED;
}

Button::~Button()
{
}

int Button::getOnClick()
{
    return this->onclick;
}

Point Button::getPosition()
{
    return this->pos;
}

Point Button::getSize()
{
    return this->size;
}

int Button::getStatus()
{
    return this->status;
}

string Button::getName()
{
    return this->name;
}


void Button::setStatus(int s)
{
    this->status = s;
}

void Button::setType( int s)
{
    this->type = s;
}

 int Button::getType()
{
    return this->type;
}
void Button::setOnClick( int action)
{
    onclick = action;
}
void Button::setPosition(Point position)
{
    pos = position;
}
void Button::setSize(Point _size)
{
    size = _size;
}
void Button::setName(string _name)
{
    name = _name;
}
