# YOLOCRAFT

# À PROPOS DE CE PROJET: 

Notre projet consistait à réaliser un jeu de véhicule. Celui-ci devra parcourir une map, tuer ses ennemis afin de récolter des gains et ainsi pouvoir s'acheter
de nouvelles pièces . Nous avons tenu à laisser au yolocrafteur une libérté sur le choix la forme de son véhicule qu'il construira lui-même, néanmoins il doit 
rester terrestre.Une fois YOLOCRAFT lancé, vous aurez le choix entre un nombre restreint de pièce (que vous pourrez enrichir au fur et à mesure) pour construire 
votre véhicule. Faites des choix jusdicieux dans l'emplacement de vos objets. Serrez votre ceinture et en avant l'aventure!

# PLAN DE L'ARCHIVE:
\dossiers
- bin: contient l'executable ainsi qu'un dossier data contenant les asserts
- obj: contient les *.o 
- doc: la documentation de l'appication, le diagramme des modules, la diapo de présentation
- src: le code.
\makefile: vous permet de compiler le code.

# COMMENT LANCER YOLOCRAFT:

- Assurez vous que les libréries libsdl2,libsdl2-image,libsdl2-ttf,libsdl2-mixer et box2d sont bien instalées.
- Mettez vous au premier niveau de l'archive et ouvrez un Terminal;
- Tapez la ligne de commande "make";
- Une fois la compilation achevée, tapez la ligne de commande "cd bin";
- Ensuite, tapez "./bin/yolocraft";



# LES 7 COMMANDEMENTS D'UN YOLOCRAFTEUR:

1. De ton intellignce tu useras.
2. Ta forme tu construiras.
3. Survivre tu devras.
4. Tes ennemis tu tueras.
5. Avare tu seras.
6. De la mort quelques fois tu ressussiteras.
7. Une bonne note tu mettras.



# COMMENT YOLOCRAFTER:

- Une fois le jeu lancé,vous arrivez sur un ecran contenant une grille. 
- Cliquez sur "Magasin", séléctionnez une pièce qui vous intéresse et cliquez sur "Acheter". Celle-ci sera ajoutée automatiquement à votre "Garage".
- Vous pouvez recommencez autant que vous voulez. 
	
## Il existe trois types de pièces:

Bodyshape: représente la carcasse du véhicule. ils sont deux types différents: un bodyshape normal et un bodyshape protector.
Ce dernier rend le déplacement plus lent mais protège plus efficacement le yolocrafteur.
Roue: représent el'élément qui permet d'avancer dans la map. 
Arme: Elles peuvent envoyer des projectils afin d'attaquer l'ennemi. 

- Une fois votre shopping fini, cliquez sur "Garage" pour revenir à la grille de départ afin de construire votre véhicule. 
- Vous êtes maintenant devant la grille, Respectez les régles de contruction et recommencez autant que vous voulez avec une même pièce. 

## RÉGLES DE CONTRUCTION:
- Les armes doivent être rattachées  un bodyshape.
- Les roues doivent être rattachées  un bodyshape. 
- Toutes les pièces doivent être rattachées entre elles. 

## RÉGLES DE YOLOCRAFT:
- Appuyez sur les flèches directionnelles pour vous déplacer dans map.
- Dirigez votre souris vers votre cible, faite un clic pour tirer.
- Yolocraft s'arrêtera quand vous n'aurez plus de vie. 
- Pour quitter, appuyez sur le bouton "Quitter" sur le menu principal.


# RÉSENTATION::Noms(){
les étudiants ayant paticipé à ce projet sont:
- Samir Kherraz
- Kevin Saddeki
- Axel Lasseur
- Cylia Boutata

