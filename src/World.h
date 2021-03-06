#ifndef WORLD_H
#define WORLD_H

#include <Box2D/Box2D.h>
#include <vector>
#include <unistd.h>
#include "Point.h"
#include "Player.h"
#include "Map.h"
#include "Mobile.h"
#include "ContactListner.h"
using namespace std;
/**@brief: BOX2D 
 *  Box2d est une bibliothèque logicielle libre de moteur physique 2D.Il simule un système de corps rigides sur un plan. 
 * Cette classe va contenir tous les éléments présents dans une partie de jeu. Elle va gérer le positionnement des élémnts, leur intéractions et leur suppression. Elle définit également la condition d'environnement (gravité)  
 * @param bodies: pointeur sur un vecteur de b2Body (objets dynamiques affichés à l'écran) 
 * @param map:
 * @param world:
 * @param player:pointeur sur la classeur PLayer. 
 * @param gravity: Point 
 * @param velocityIterations: constante de box2d, sert d'itération dans box2d
 * @param positionIterations: */
class World
{

private:
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    const float32 box_size = BOX_SIZE / BOX2D_SCALE;

    vector<b2Body*> bodies;
    vector<b2Body*> players_index;
    vector<Player *> players;

    b2Body* map;

    b2World* world;

    Player* player;

    ContactListner* listener;
/**@brief Crée une fixture avec une position et une taille définies ainsi qu'une densité.
 * @param body: pointeur sur un b2Body
 * @param pos: Point de position de la fixture
 * @param size: Point qi définit la taille
 * @param density: double qui définit la 
 * @return pointeur sur b2Fixture*/   

    b2Fixture* createBoxFixture(b2Body* body,const Point &pos,const Point &size,const double &density);
    b2Fixture* createRocketFixture(b2Body* body,const Point &pos,const Point &size,const double &density);
/**@brief
 * @param body: pointeur sur un b2Body
 * @param pos: Point de position de la fixture
 * @param size: entier */
    b2Fixture* createCircleFixture(b2Body* body,const Point &pos,const int &size);

/**@brief rée un body de type bodyshape
 * @param mobileBody: pointeur sur un b2Body
 * @param body: pointeur sur la classe Mobile
 * @param p: Point */
    void createShape(b2Body* mobileBody, Mobile* body,const Point &p);
/**@brief Crée un body de type roue
 * @param mobileBody: pointeur sur un b2Body
 * @param body: pointeur sur la classe Mobile
 * @param p: Point */
    void createWheel(b2Body* mobileBody, Mobile* body,const Point &p);
/**@brief Crée un body de type arme
 * @param mobileBody: pointeur sur un b2Body
 * @param body: pointeur sur la classe Mobile
 * @param p: Point */
    void createRocket(b2Body* mobileBody, Mobile* body,const Point &p);

/**@brief Ajoute un player dans le world
 * @param mobileBody: pointeur sur un b2Body
 * @param body: pointeur sur la classe Mobile
 * @param p: Point */
    void AddPlayer(Player* mobile);
    void removeBody(b2Body* body);
/**@brief REnvoie la position d'un bloc
 * @param mobileSize: Point
 * @param gridPos: Point 
 * @return b2Vec2*/
    b2Vec2 getGoodPositionOfBlock(const Point& mobileSize, const Point& gridPos) const;
/**@brief Crée un body vide à une position précise
 * @param point: Point 
 * @return pointeur sur b2Vec2*/
    b2Body* createVoidBody(const Point &pos);
/**@brief Permet de créer un body non vide.
 * @param body: Pointeur sur la classe Mobile
 * @return b2Body*/
    b2Body* createBody(Player* body);
    void rechargeBody(Mobile* body);

     int getPlayerIndex(b2Body* mobile)const;

public:
    World();
    ~World();
/**@brief Définit le pas 
 * @param timeStep:  flaot32 qui détermine .......
 * @return none*/
    void step(float32 timeStep);
/**@brief  Permet de créer une map 
 * @param mapTemplate: pointeur sur la classe Map
 * @return none*/
    void createMap(Map* mapTemplate);

    void setGravity(const Point &new_gravity);
/**@brief  Permet de créer un player
 * @param new_player: pointeur sur la classe Player
 * @param manual: adresse booleen
 * @return none*/
    void createPlayer(Player* new_player,const bool &manual);
    vector<b2Body*> getBodies() const;

    Player* getPlayer() const;
    b2Body* getMap() const;
    b2World* getWorld() const;
    void regressionTest();
};

#endif // WORLD_H
