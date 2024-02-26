# ProjetInfo


Le but de ce jeu est de déchiffrer un mot qui a été effacé du parchemin.

Chaque combat permet de récupérer une lettre de ce mot. On peut alors tenter de découvrir le mot caché mais le moindre échec conduit à la défaite.

Les principaux problèmes rencontrés lors de la programmation:

-> Gestion des pointeurs et utilisation d'un pointeur vers une classe mère pour y stocker un pointeur vers une classe fille dans le cadre des classes d'armes et de persos.

-> Separation des classes dans des fichiers différents qui conduisaient à des bugs que je ne parvenais pas à résoudre d'où l'usage d'un seul hpp ce qui rend la structure moins claire.

-> Penser le problème en terme de classe pas seulement d'attribut du perso.


Piste d'amélioration:

-> Complexifier le système d'attaque dans les combats car il y a deux défenses possibles mais une seule attaque.

-> Gérer tous les cas où l'utilisateur renvoie des champs qui n'entre pas dans les possibilités offertes par le jeu.

-> Rendre le système d'inventaire plus réaliste en le limitant en volume.

-> Générer aléatoirement des mots à retrouver.



