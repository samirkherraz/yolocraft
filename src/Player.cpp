#include "Player.h"

Player::Player()
{
Common::_Player++;

    dead = false;
    name = "";
    mobile = NULL;
    wallet = 0;
}

Player::Player(string _name)
{
Common::_Player++;

    dead = false;

    name = _name;
    mobile = NULL;
    wallet = 0;
}

Player::~Player()
{
Common::_Player--;

    delete mobile;
    box2dmobile = NULL;
    my_shapes.clear();
    name = "";
    mobile = NULL;
    wallet = 0;
}




void Player::live(){
    dead = false;
    }
    
bool Player::isDead(){
    return dead;
    }

void Player::die(){
    dead = true;
    }


void Player::newGain(unsigned int amount)
{

    wallet += amount;
}

void Player::buyShape(AbstractObject* part)
{
    for( auto shap : my_shapes){
        if(shap == part) return;
        }
    my_shapes.push_back(part);
}
vector<AbstractObject*> Player::getShapes()
{
    return my_shapes;
}
void Player::loseGain(unsigned int amount)
{

    if(amount <= wallet)
        wallet -= amount;
    else
        wallet = 0;
}

unsigned int Player::getGain()
{
    return wallet;
}

void Player::setMobile(Mobile* newMobile)
{

    mobile = newMobile;
}

Mobile* Player::getMobile()
{

    return mobile;
}

void Player::setName(string newName)
{

    name = newName;
}

string Player::getName()
{

    return name;
}

void Player::setFireTarget(Point target)
{
    fireTarget = target;
}

void Player::doAction(int ACTION)
{
    if(!isDead())
    switch(ACTION) {

    case GO_FORWARD:
        mobile->ApplyLinearImpulse(-5);
        break;

    case GO_BACKWARD:
        mobile->ApplyLinearImpulse(5);
        break;
    case GO_UPWARD:
        mobile->Jump();
        break;
    case GO_DOWNWARD:
        mobile->ApplyBrackImpulse(0);
        break;
    case STOP_MOTOR:
        mobile->ResetForce();

        break;
    case FIRE:
        mobile->Fire(fireTarget);

        break;
    }
}