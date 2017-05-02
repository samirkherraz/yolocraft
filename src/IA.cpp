#include "IA.h"

IA::IA(string name, Player * j){
	
	player = j;
	ia = new Player(name);
	
	precision = rand() % 100 / 10000 + 0.5; // 0.005-1.005 %
	distance = rand() % 5 + 2; // 0-7
	
	reaction = rand() % 5; // 0-2 secondes
	time(&lastShoot);
	time(&lastMove);

}

IA::~IA(){
	delete ia;
	player = NULL;
	ia = NULL;
	
	precision = 0;
	distance = 0;
	reaction = 0;
	lastShoot = 0;
	lastMove = 0;
}

void IA::setPlayer(Player * new_player){

	player = new_player;

}

Player * IA::getPlayer(){

	return player;

}

void IA::setIA(Player * new_ia){

	ia = new_ia;

}

Player * IA::getIA(){

	return ia;

}

Mobile * IA::getMobile(){

	return ia->getMobile();

}

void IA::step(){

	//this->afficheDonnees();

	bool willMove = true, willShoot = true;
	
	willMove = (rand() % 100 > 66); // 2 chance sur 3 de bouger ou de tirer
	willShoot = (rand() % 100 > 66);
	
	//cout << "IA::step : willMove = " << willMove << ", willShoot = " << willShoot << endl;

	if(difftime(time(NULL), lastMove) >= reaction && willMove){ // Si on appelle step, on vérifie de bien avoir bougé au minimum 10 secondes et s'il a le droit de bouger
		this->move();
	}else if(difftime(time(NULL), lastMove) > 2){ // Peut-être à faire passer à 0,5 ou 1 seconde
		lastMove = time(NULL);
		ia->doAction(STOP_MOTOR);
	}

	if(difftime(time(NULL), lastShoot) >= reaction && willShoot){
		this->shoot();
	}
	
}

int IA::getDistanceFromPlayer(){

	double distance;

	Point iaPos = Point(ia->getMobile()->getB2Mobile()->GetPosition().x, ia->getMobile()->getB2Mobile()->GetPosition().y);
	
	Point playerPos = Point(player->getMobile()->getB2Mobile()->GetPosition().x, player->getMobile()->getB2Mobile()->GetPosition().y);
	
	distance = iaPos.x - playerPos.x;
	
	return (int)distance;
}

void IA::shoot(){ // Faire le shoot avec la précision
	lastShoot = time(NULL);
	Point p(player->getMobile()->getB2Mobile()->GetPosition().x*precision, player->getMobile()->getB2Mobile()->GetPosition().y*precision);
	
	getIA()->setFireTarget(p);
	getIA()->doAction(FIRE);
}

void IA::move(){
	
	assert(ia->getMobile() != NULL);
	
	int currentDistance = getDistanceFromPlayer();
	
	if(currentDistance < WINDOW_W / (BOX2D_SCALE*2)){
		if(currentDistance > distance) // avance vers le joueur
			ia->doAction(GO_BACKWARD);
		else if(currentDistance == distance) // Freine
			ia->doAction(GO_DOWNWARD);
		else
			ia->doAction(GO_FORWARD);
	}

}

void IA::afficheDonnees(){
	
	cout << "/=== Données " << this->getIA()->getName() << " ===/" << endl;
	
	cout << "Mon est " << ia->getName() << ", voici mes informations : \n\t réaction (reaction): " << reaction << "\n\t précision (precision): " << precision << "\n\t distance (distance): " << distance << endl;
	
	cout << "Mon dernier mouvement date de : " << difftime(time(NULL), lastMove) << " secondes et mon dernier shoot de : " << difftime(time(NULL), lastShoot) << " secondes" << endl;
	
	cout << "/=== Fin données " << this->getIA()->getName() << " ===/" << endl;
}

void IA::defineMobile(Point start_position, int which){

	Mobile* game_mobile_ia = new Mobile();
	//game_mobile_ia->setSize(Point(4, 4));
	game_mobile_ia->setPosition(start_position);

	switch(which){
		case 0: {// Mec normal
			game_mobile_ia->addPart(Point(0, 1), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(1, 0), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(3, 0), Common::getObjectOfType(WEAPON));

			game_mobile_ia->addPart(Point(1, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 2), Common::getObjectOfType(BODYWORK));
	
			game_mobile_ia->addPart(Point(1, 3), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(5, 3), Common::getObjectOfType(WHEEL));
        }break;
		case 1: {// Gros bloc
			game_mobile_ia->addPart(Point(0, 1), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(0, 3), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(0, 5), Common::getObjectOfType(WEAPON));

			game_mobile_ia->addPart(Point(1, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 6), Common::getObjectOfType(BODYWORK));

			game_mobile_ia->addPart(Point(1, 7), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(2, 7), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(5, 7), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(6, 7), Common::getObjectOfType(WHEEL));
        }break;
		case 2: // Super armé
			{
            game_mobile_ia->addPart(Point(0, 3), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(1, 2), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(4, 0), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(4, 2), Common::getObjectOfType(WEAPON));

			game_mobile_ia->addPart(Point(5, 0), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 2), Common::getObjectOfType(BODYWORK));

			game_mobile_ia->addPart(Point(1, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 3), Common::getObjectOfType(BODYWORK));

			game_mobile_ia->addPart(Point(1, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 4), Common::getObjectOfType(BODYWORK));

			game_mobile_ia->addPart(Point(1, 5), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(5, 5), Common::getObjectOfType(WHEEL));
			}break;
		default: // Boss Croix
			{game_mobile_ia->addPart(Point(0, 1), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(0, 2), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(0, 3), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(1, 0), Common::getObjectOfType(WEAPON));
			game_mobile_ia->addPart(Point(1, 6), Common::getObjectOfType(WEAPON));
            
			game_mobile_ia->addPart(Point(1, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(1, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(2, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(3, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 0), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 1), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 2), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 5), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(4, 6), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 0), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(5, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 0), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(6, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(7, 3), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(7, 4), Common::getObjectOfType(BODYWORK));
			game_mobile_ia->addPart(Point(7, 5), Common::getObjectOfType(BODYWORK));
            game_mobile_ia->getPart(Point(7, 5))->setLife(1000);
            game_mobile_ia->setLife(1000);
			
			game_mobile_ia->addPart(Point(2, 7), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(3, 7), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(4, 7), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(5, 6), Common::getObjectOfType(WHEEL));
			game_mobile_ia->addPart(Point(7, 6), Common::getObjectOfType(WHEEL));
			}
			break;
	}
			
	
	this->getIA()->setMobile(game_mobile_ia);
}

/*

	Gros bloc
	
	game_mobile_ia->addPart(Point(0, 1), Common::getObjectOfType(WEAPON));
	game_mobile_ia->addPart(Point(0, 3), Common::getObjectOfType(WEAPON));
	game_mobile_ia->addPart(Point(0, 5), Common::getObjectOfType(WEAPON));

	game_mobile_ia->addPart(Point(1, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(6, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(1, 2), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 2), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 2), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 2), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 2), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(6, 2), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(1, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(6, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(1, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(6, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(1, 5), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 5), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 5), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 5), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 5), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(6, 5), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(1, 6), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 6), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 6), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 6), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 6), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(6, 6), Common::getObjectOfType(BODYWORK));
	
	game_mobile_ia->addPart(Point(1, 7), Common::getObjectOfType(WHEEL));
	game_mobile_ia->addPart(Point(2, 7), Common::getObjectOfType(WHEEL));
	game_mobile_ia->addPart(Point(5, 7), Common::getObjectOfType(WHEEL));
	game_mobile_ia->addPart(Point(6, 7), Common::getObjectOfType(WHEEL));
	
	Un super armé
	
	
	game_mobile_ia->addPart(Point(0, 3), Common::getObjectOfType(WEAPON));
	game_mobile_ia->addPart(Point(1, 2), Common::getObjectOfType(WEAPON));
	game_mobile_ia->addPart(Point(4, 0), Common::getObjectOfType(WEAPON));
	game_mobile_ia->addPart(Point(4, 2), Common::getObjectOfType(WEAPON));
	
	game_mobile_ia->addPart(Point(5, 0), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 1), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 2), Common::getObjectOfType(BODYWORK));
	
	game_mobile_ia->addPart(Point(1, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 3), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 3), Common::getObjectOfType(BODYWORK));
	
	game_mobile_ia->addPart(Point(1, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(2, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(3, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(4, 4), Common::getObjectOfType(BODYWORK));
	game_mobile_ia->addPart(Point(5, 4), Common::getObjectOfType(BODYWORK));

	game_mobile_ia->addPart(Point(1, 5), Common::getObjectOfType(WHEEL));
	game_mobile_ia->addPart(Point(5, 5), Common::getObjectOfType(WHEEL));
	
	Un rapide
	
	
	Croix gammée (boss)

*/
