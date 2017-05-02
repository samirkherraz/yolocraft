#include "World.h"

void World::AddPlayer(Player* player)
{
    players_index.push_back(player->getMobile()->getB2Mobile());
    players.push_back(player);
}

int World::getPlayerIndex(b2Body* body) const
{
    // On cherche l'index d'un body dans le tableau
    // si on le trouve, on renvoie son index
    // si non on -1;

    for(unsigned int i = 0; i < players_index.size(); i++) {
        if(players_index.at(i) == body) {
            return i;
        }
    }

    return -1;
}

World::World()
{
    // on crée un world et on lui donne une gravité par défault de (0,0)
    Common::_World++;

    world = new b2World(b2Vec2(0, 0));
    world->SetAutoClearForces(true);
    world->SetAllowSleeping(true);
    map = NULL;
    player = NULL;
    listener = new ContactListner();
    world->SetContactListener(listener);
}

World::~World()
{
    Common::_World--;

    for(auto b : bodies) {
        delete static_cast<Grid*>(b->GetUserData());
    }
    bodies.clear();
    players_index.clear();

    b2Joint* j = world->GetJointList();
    while(j != 0) {
        world->DestroyJoint(j);
        j = j->GetNext();
    }

    b2Body* b = world->GetBodyList();
    while(b != 0) {
        world->DestroyBody(b);
        b = b->GetNext();
    }

    delete listener;
    delete world;

    map = NULL;
    player = NULL;
}

b2Vec2 World::getGoodPositionOfBlock(const Point& mobileSize, const Point& gridPos) const
{

    Point center;
    center.x = (int)(mobileSize.x / 2);
    center.y = (int)(mobileSize.y / 2);

    if(int(mobileSize.x) % 2 == 0)
        center.x -= 0.5;
    if(int(mobileSize.y) % 2 == 0)
        center.y -= 0.5;
    if(mobileSize.x == 1)
        center.x = 0;
    if(mobileSize.y == 1)
        center.y = 0;

    b2Vec2 goodPos;
    goodPos.x = box_size * (gridPos.x - center.x);
    goodPos.y = -(box_size * (gridPos.y - center.y));

    return goodPos;
}

void World::createMap(Map* mapTemplate)
{

    vector<Point> vect = mapTemplate->getGround();

    b2Vec2 vs[vect.size()];

    for(unsigned int i = 0; i < vect.size(); i++) {

        vs[i].Set(vect.at(i).x / BOX2D_SCALE, vect.at(i).y / BOX2D_SCALE);
    }

    b2ChainShape chain;
    chain.CreateLoop(vs, vect.size());
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &chain;
    myFixtureDef.density = 1;
    myFixtureDef.filter.groupIndex = 0;

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;

    myBodyDef.position.Set(0, 0);
    map = world->CreateBody(&myBodyDef);
    map->CreateFixture(&myFixtureDef);
    map->SetUserData(mapTemplate);
    listener->setMap(map);
}

b2Body* World::createBody(Player* player)
{
    Mobile* body = player->getMobile();
    b2Body* mobileBody = body->getB2Mobile();

    Grid* bodyparts = static_cast<Grid*>(mobileBody->GetUserData());
    bodyparts->setParent(body);

    listener->catchObject(mobileBody);

    for(int i = 0; i < body->getSize().x; i++) {
        for(int j = 0; j < body->getSize().y; j++) {
            if(body->getPart(Point(i, j)) == NULL)
                continue;

            switch(body->getPart(Point(i, j))->getType()) {
            default: {
                createShape(mobileBody, body, Point(i, j));
            } break;
            case WHEEL:
                createWheel(mobileBody, body, Point(i, j));
                break;
            case WEAPON:
                createRocket(mobileBody, body, Point(i, j));
                break;
            case CELL:
                continue;
                break;
            }
        }
    }

    return mobileBody;
}

void World::rechargeBody(Mobile* body)
{
    b2Body* mobileBody;
    mobileBody = body->getB2Mobile();
    for(int i = 0; i < body->getSize().x; i++) {
        for(int j = 0; j < body->getSize().y; j++) {
            if(body->getPart(Point(i, j)) == NULL)
                continue;
            if(body->getPart(Point(i, j))->getType() == WEAPON) {
        
                body->getPart(Point(i,j))->setLife(1);
                createRocket(mobileBody, body, Point(i, j));
            }
        }
    }
}

b2Fixture* World::createBoxFixture(b2Body* body, const Point& pos, const Point& size, const double& density)
{

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(size.x * box_size / 2, size.y * box_size / 2, b2Vec2(pos.x, pos.y), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.restitution = 0.0f;
    fixtureDef.friction = 10.0f;
    fixtureDef.filter.groupIndex = -2 - getPlayerIndex(body);
    return body->CreateFixture(&fixtureDef);
}

b2Fixture* World::createRocketFixture(b2Body* body, const Point& pos, const Point& size, const double& density)
{

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(size.x * box_size / 2, size.y * box_size / 2, b2Vec2(pos.x, pos.y), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.restitution = 0.0f;
    fixtureDef.friction = 10.0f;
    fixtureDef.filter.groupIndex = -2 ;//-getPlayerIndex(body);

    return body->CreateFixture(&fixtureDef);
}

b2Fixture* World::createCircleFixture(b2Body* body, const Point& pos, const int& size)
{
    b2CircleShape dynamicBox;
    dynamicBox.m_p = b2Vec2(pos.x, pos.y);
    dynamicBox.m_radius = size * double(box_size / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 10.0f;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.restitution = 0.0f;
    fixtureDef.friction = 10.0f;
    fixtureDef.filter.groupIndex = -2 ;//getPlayerIndex(body);

    return body->CreateFixture(&fixtureDef);
}

void World::createWheel(b2Body* mobileBody, Mobile* body, const Point& pos)
{

    Grid* bodyparts = NULL;

    b2Vec2 _pos = getGoodPositionOfBlock(body->getSize(), pos);

    Point wheelPos;
    wheelPos.x = BOX2D_SCALE * mobileBody->GetWorldPoint(_pos).x;
    wheelPos.y = BOX2D_SCALE * mobileBody->GetWorldPoint(_pos).y;

    b2Body* wheelBody = createVoidBody(wheelPos);
    createCircleFixture(wheelBody, Point(0, 0), 1);
    bodyparts = static_cast<Grid*>(wheelBody->GetUserData());
    bodyparts->addPart(Point(0, 0), body->getPart(pos));
    bodyparts->setParent(body);
    //listener->catchObject(wheelBody);

    bodyparts = static_cast<Grid*>(mobileBody->GetUserData());
    bodyparts->addPart(pos, NULL);

    b2RevoluteJointDef* jointDef = new b2RevoluteJointDef();
    jointDef->bodyA = mobileBody;
    jointDef->bodyB = wheelBody;
    jointDef->localAnchorA = _pos;
    jointDef->localAnchorB = b2Vec2(0, 0);
    jointDef->enableMotor = false;
    jointDef->motorSpeed = 0;
    jointDef->maxMotorTorque = 10;

    b2RevoluteJoint* motorJoint = static_cast<b2RevoluteJoint*>(world->CreateJoint(jointDef));
    body->addMotorJoint(motorJoint);
}

void World::createRocket(b2Body* mobileBody, Mobile* body, const Point& pos)
{

    Grid* bodyparts = NULL;

    b2Vec2 _pos = getGoodPositionOfBlock(body->getSize(), pos);

    Point rocketPos;
    rocketPos.x = BOX2D_SCALE * mobileBody->GetWorldPoint(_pos).x;
    rocketPos.y = BOX2D_SCALE * mobileBody->GetWorldPoint(_pos).y;

    b2Body* rocketBody = createVoidBody(rocketPos);

    createRocketFixture(rocketBody, Point(0, 0), Point(1, 1), 1);
    bodyparts = static_cast<Grid*>(rocketBody->GetUserData());
    bodyparts->addPart(Point(0, 0), body->getPart(pos));
    bodyparts->setParent(body);
    //listener->catchObject(rocketBody);
    

    bodyparts = static_cast<Grid*>(mobileBody->GetUserData());
    bodyparts->addPart(pos, NULL);

    b2RevoluteJointDef* weldJointDef = new b2RevoluteJointDef();
    weldJointDef->bodyA = mobileBody;
    weldJointDef->bodyB = rocketBody;
    weldJointDef->enableMotor = false;
    weldJointDef->localAnchorA = _pos;
    weldJointDef->localAnchorB = b2Vec2(0, 0);
    world->CreateJoint(weldJointDef);
    body->addRocket(rocketBody);
}

void World::createShape(b2Body* mobileBody, Mobile* body, const Point& pos)
{
    Grid* bodyparts = NULL;
    b2Vec2 _pos = getGoodPositionOfBlock(body->getSize(), pos);
    createBoxFixture(mobileBody, Point(_pos.x, _pos.y), Point(1, 1), 1);
    bodyparts = static_cast<Grid*>(mobileBody->GetUserData());
    bodyparts->addPart(pos, body->getPart(pos));
}

b2Body* World::createVoidBody(const Point& pos)
{
    b2Body* mobileBody;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(pos.x / BOX2D_SCALE, pos.y / BOX2D_SCALE);
    bodyDef.awake = true;
    mobileBody = world->CreateBody(&bodyDef);
    mobileBody->SetUserData(new Grid());
    bodies.push_back(mobileBody);
    return mobileBody;
}

void World::createPlayer(Player* new_player, const bool& manual)
{

    if(manual)
        player = new_player;

    b2Body* mobileBody = createVoidBody(new_player->getMobile()->getPosition());

    new_player->getMobile()->setB2Mobile(mobileBody);
    new_player->getMobile()->setB2ContactListener(listener);
    AddPlayer(new_player);
        new_player->getMobile()->setIndex(-2-getPlayerIndex(mobileBody));
    createBody(new_player);
}

void World::setGravity(const Point& new_gravity)
{
    world->SetGravity(b2Vec2(new_gravity.x, new_gravity.y));
}

Player* World::getPlayer() const
{

    return player;
}

vector<b2Body*> World::getBodies() const
{
    return bodies;
}

void World::removeBody(b2Body* body)
{
    int fps_to_keep = 5;
    Grid* g = static_cast<Grid*>(body->GetUserData());
    int player_index = getPlayerIndex(body);

    bool allAreKilled = true;
    for(int i = 0; i < g->getSize().x; i++) {
        for(int j = 0; j < g->getSize().y; j++) {

            if(g->getPart(Point(i, j)) == NULL) {
                continue;
                // g->addPart(Point(i, j), NULL);
            }

            int l = g->getPart(Point(i, j))->getLife();
            g->getPart(Point(i, j))->setLife(l - 1);

            switch(g->getPart(Point(i, j))->getType()) {
            default: {
                allAreKilled = false;

                listener->removeObject(body);
                g->getPart(Point(i, j))->setLife(fps_to_keep);
                if(g->getPart(Point(i, j))->getType() == WEAPON) {

                    static_cast<Mobile*>(g->getParent())->removeRocket(body);
                }
                g->getPart(Point(i, j))->setType(EXPLOSION_1);
                Common::playAudio(AUDIO_EXPLODE);

            } break;
            case EXPLOSION_1: {
                allAreKilled = false;

                if(g->getPart(Point(i, j))->getLife() == 0) {
                    g->getPart(Point(i, j))->setLife(fps_to_keep);
                    g->getPart(Point(i, j))->setType(EXPLOSION_2);
                }
            } break;
            case EXPLOSION_2: {
                allAreKilled = false;

                if(g->getPart(Point(i, j))->getLife() == 0) {
                    g->getPart(Point(i, j))->setLife(fps_to_keep);
                    g->getPart(Point(i, j))->setType(EXPLOSION_3);
                }
            } break;
            case EXPLOSION_3: {
                allAreKilled = false;

                if(g->getPart(Point(i, j))->getLife() == 0) {
                    g->getPart(Point(i, j))->setLife(fps_to_keep);
                    g->getPart(Point(i, j))->setType(EXPLOSION_4);
                }
            } break;
            case EXPLOSION_4: {
                if(g->getPart(Point(i, j))->getLife() != 0) {
                    allAreKilled = false;
                }
            } break;
            }
        }
    }

    if(allAreKilled) {

        delete g;
        for(unsigned int i = 0; i < bodies.size(); i++) {
            if(body == bodies.at(i)) {
                bodies.erase(bodies.begin() + i);
                break;
            }
        }
        if(player_index != -1) {
            players.at(player_index)->die();
            players.erase(players.begin() + player_index);
            players_index.erase(players_index.begin() + player_index);
        }

        world->DestroyBody(body);
    }
}

void World::step(float32 timeStep)
{

    vector<b2Body*> destructions;

    destructions = listener->getDestructions();

    for(auto* body : bodies) {

        Grid* g = static_cast<Grid*>(body->GetUserData());

        if(g != NULL) {
            bool found = false;

            for(int i = 0; i < g->getSize().x; i++) {
                for(int j = 0; j < g->getSize().y; j++) {
                    if(g->getPart(Point(i, j)) == NULL)
                        continue;
                    switch(g->getPart(Point(i, j))->getType()) {
                    case EXPLOSION_1:
                    case EXPLOSION_2:
                    case EXPLOSION_3:
                    case EXPLOSION_4:
                        found = true;
                        break;
                    }
                    if(found)
                        break;
                }
                if(found)
                    break;
            }

            if(found)
                destructions.push_back(body);
        }

        if(body->GetPosition().y < -10)
            destructions.push_back(body);
    }

    for(auto* body : destructions) {
        removeBody(body);
    }

    listener->resetDestructions();
    world->Step(timeStep, velocityIterations, positionIterations);
    for(auto* player : players) {
        if(player->getMobile()->getNbRocket() == 0) {
            rechargeBody(player->getMobile());
        }
    }
}

b2Body* World::getMap() const
{
    return map;
}
b2World* World::getWorld() const
{
    return world;
}
