
#include <iostream>
#include "perso.hpp"
#include <memory>




int main(){


std::cout<<"Tu as trouvé un parchemin caché et tu dois le dechiffrer pour cela tu devras gagner un maximum de combat"<<std::endl;


std::cout<<"Pour commencer: voici une énigme pour toi :"<<std::endl;

std::cout<<"Combien de 9 y a-t-il entre 1 et 100 ?"<<std::endl;

std::cout<<"Alors ?"<<std::endl;

std::string a="";
std::getline(std::cin,a); /*Utilisation de getline pour éviter le bug de la saisie de la réponse en cas d'espace*/

bool b;

std::cout<<"Tu croyais pas avoir la réponse tout de suite ? Le sage a décidé de te faire patienter un peu"<<std::endl;

/*On verifie que l'utilisateur a saisi la bonne réponse*/

if(a=="20"){

    b=true;
}
else{
    b=false;
}

std::cout<<"Souhaites-tu être Mage(1), Guerrier (2), Voleur (3) ?"<<std::endl;

std::string classeChoisie;

std::cin >> classeChoisie;


std::shared_ptr<Perso> joueur; /*Utilisation d'un pointeur de classe pour l'utiliser comme pointeur vers une sous classe*/

    if (classeChoisie == "1") {
        joueur = std::make_shared<Mage>();
    } 
    else if (classeChoisie == "3") {
        joueur = std::make_shared<Voleur>();
    } 
    else if (classeChoisie == "2") {
        joueur = std::make_shared<Guerrier>();
    }

auto player = *joueur;



if(b==true){
std::cout<<"Le sage de l'enigme a décidé de t'offir une epee en bois"<<std::endl;
player.ajoutinventaire("Epeeenbois");
}


std::cout<<"Voici l'arme que tu as en main : "<<std::endl;
std::cout<<player.ptr_arme()->nom()<<" de durabilite:"<<player.ptr_arme()->dura()<<std::endl;

std::cout<<""<<std::endl;

std::cout<<"Et voici le stuff dans ton inventaire :"<<std::endl;
player.voirinventaire();

std::cout<<""<<std::endl;

/*On crée un vecteur d'ennemi*/
std::vector<std::shared_ptr<Perso>> Ennemis = {std::make_shared<Voleur>(),std::make_shared<Mage>(),std::make_shared<Guerrier>(),std::make_shared<Guerrier>(),std::make_shared<Guerrier>()};

/*On leur donne un stuff minimal et on les equipe si besoin*/

for(auto x: Ennemis){
    x->ajoutinventaire("Epeeenbois");
    if (x->ptr_arme()->nom()=="Mains"){
        x->changerarme(0);
    }
}

std::cout<<"Te voilà armé pour ton 1er combat"<<std::endl;



    std::string ent="";
    std::string so="";
    int j;
    while(true){
        
         for(std::shared_ptr<Perso> x: Ennemis){
        
            combat(player, *x);

            std::cout<<"Voici l'arme que tu as en main : "<<std::endl;
            
            std::cout<<player.ptr_arme()->nom()<<" de durabilite:"<<player.ptr_arme()->dura()<<std::endl;
            
            std::cout<<"Et voici le stuff dans ton inventaire :"<<std::endl;

            player.voirinventaire();

            std::cout<<"Veux tu changer d'arme ? oui (0) ou non (1)"<<std::endl;

            std::cin>>ent;

            if(ent=="0"){
                std::cout<<"Quel arme veux-tu ?"<<std::endl;
                std::cin>>j;
                player.changerarme(j);

            }

            std::cout<<player.getmotcrypte()<<std::endl;


            std::cout<<"Souhaites tu tenter ta chance pour décrypter le mot caché ? Oui (0) ou Non (1)"<<std::endl;
            std::cin>>so;


            if(so=="0"){
                std::string mot1;
                std::cout<<"Quel est le mot caché ?"<<std::endl;
                std::cin>>mot1;
                if(mot1==player.getmot()){
                    std::cout<<"Bravo ! Tu as gagné le jeu !"<<std::endl;
                    return 0;
                }
                else{
                    std::cout<<"C'est la mort subite ! Ton arrogance t'auras perdu !"<<std::endl;
                    return 0;
                }
            }



            }
        
        
        break;
        

        



    }

    return 0;
}

