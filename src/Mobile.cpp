#include "Mobile.h"

Mobile::Mobile()
{

    Common::_Mobile++;
}

void Mobile::setB2Mobile(b2Body* newMobile)
{

    box2dmobile = newMobile;
}

void Mobile::Jump()
{
    box2dmobile->ApplyLinearImpulse(b2Vec2(1, 2), box2dmobile->GetWorldCenter(), true);
}

b2Body* Mobile::getB2Mobile()
{

    return box2dmobile;
}

unsigned int Mobile::getNbRocket() const
{

    return fires.size();
}

Mobile::~Mobile()
{

    Common::_Mobile--;

    listener = NULL;
    box2dmobile = NULL;
    motors.clear();
    fires.clear();
}

Point Mobile::getPosition() const
{
    return position;
}
void Mobile::setPosition(Point new_position)
{
    position = new_position;
}

void Mobile::addMotorJoint(b2RevoluteJoint* fix)
{

    motors.push_back(fix);
}

void Mobile::addRocket(b2Body* fix)
{

    fires.push_back(fix);
}

void Mobile::removeRocket(b2Body* fix)
{
    for(unsigned int i = 0; i < fires.size(); i++) {
        if(fix == fires.at(i)) {
            fires.erase(fires.begin() + i);
            i--;
            cout << "Delete "<<fix<< endl;
        }
    }
}

void Mobile::ResetForce()
{
    for(unsigned int i = 0; i < motors.size(); i++) {

        motors.at(i)->EnableMotor(false);
    }
}

void Mobile::Fire(Point target)
{
    if(lastFire > 5) {
        if(!fires.empty()) {
            Common::playAudio(AUDIO_FIRE);
            for(auto rocket : fires) {
                double X = target.x - rocket->GetPosition().x > 0 ? 1 : -1;
                b2Vec2 force;
                force.x = 0.8 * X;
                force.y = 0.4;
                Grid* g = static_cast<Grid*>(rocket->GetUserData());
                g->getPart(Point(0, 0))->setType(ROCKET);
                rocket->GetWorld()->DestroyJoint(rocket->GetJointList()->joint);
                

                
                rocket->ApplyLinearImpulse(force, rocket->GetPosition(), true);
                b2Filter f;
                f.groupIndex = index;   
                rocket->GetFixtureList()->SetFilterData(f);        
                rocket->GetFixtureList()->Refilter ();
                listener->catchObject(rocket);
                listener->catchWithMap(rocket);
            }
            fires.clear();
            lastFire = 0;
        }
    } else {
        lastFire++;
    }
}

void Mobile::setIndex(int i){
	index = i;
};

void Mobile::setB2ContactListener(ContactListner* l)
{

    listener = l;
}

void Mobile::ApplyBrackImpulse(double force)
{

    for(unsigned int i = 0; i < motors.size(); i++) {
        motors.at(i)->EnableMotor(true);
        motors.at(i)->SetMotorSpeed(motors.at(i)->GetMotorSpeed() * force);
    }
}

void Mobile::ApplyLinearImpulse(double force)
{

    for(unsigned int i = 0; i < motors.size(); i++) {
        Common::playAudio(AUDIO_MOTOR);
        motors.at(i)->EnableMotor(true);
        if(motors.at(i)->GetMotorSpeed() + force < MAX_MOTOR_SPEED &&
           motors.at(i)->GetMotorSpeed() + force > -MAX_MOTOR_SPEED)
            motors.at(i)->SetMotorSpeed(motors.at(i)->GetMotorSpeed() + force);
    }
}
