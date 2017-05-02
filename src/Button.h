#ifndef BUTTON_H
#define BUTTON_H

#include "Point.h"
#include "Common.h"
#include <string>

using namespace std;

class Button
{
private:
	int onclick;
	Point pos;
	Point size;
	int status;
	string name;
     int type;

public:
	
	Button();
	~Button();
	
    
    void setOnClick( int action);
    void setPosition(Point position);
    void setSize(Point _size);
    void setName(string _name);
    
    
	int getOnClick();
	Point getPosition();
	Point getSize();
	int getStatus();
	string getName();
	void setType( int type);
	 int getType();
	void setStatus(int s);
};

#endif // BUTTON_H
