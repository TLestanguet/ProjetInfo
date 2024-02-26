
#pragma ounce

#include "perso.hpp"
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

/*Tirage aléatoire d'un nombre entre min et max*/

int nombrealea(int min,int max){
    std::random_device rd;
    std::mt19937 generator(rd());


    // Définition de la distribution pour générer des nombres entre min et max
    std::uniform_int_distribution<int> distribution(min, max);

    // Tirage du nombre aléatoire
    int nombreAleatoire = distribution(generator);

    // Affichage du nombre aléatoire

    return nombreAleatoire;
}

Arme::Arme()
{
}

Mains::Mains()
{
    m_degat = 5;
    m_dura = 1000000; /*Durabilite infinie*/
    m_nomArme = "Mains";
}


Epeeenbois::Epeeenbois()
{
    m_degat = 10;
    m_dura = 30;
    m_nomArme = "Epee en bois";
}

Epeeenfer::Epeeenfer()
{
    m_degat = 50;
    m_dura = 40;
    m_nomArme = "Epee en fer";
}


Leclerc::Leclerc() /*Arme pratique pour le debuggage.*/
{
    m_degat = 1000;
    m_dura = 1000;
    m_nomArme = "Char Leclerc";
} 

Perso::Perso()
{
    motcrypte = "*********";
    mot ="Archibald";
    indice=0;
}

Guerrier::Guerrier()
{
    m_vie = 100;
    m_nom="Guerrier";
    pointeur_arme = std::make_shared<Epeeenfer>();
}


Mage::Mage()
{
    m_vie = 200;
    m_nom="Mage";
    pointeur_arme = std::make_shared<Mains>();
}

Voleur::Voleur()
{
    m_vie = 100;
    m_nom="Voleur";
    pointeur_arme = std::make_shared<Mains>();
}


void Perso::recevoirDegats(int nbDegats)
{
    m_vie -= nbDegats;
    //On enlève le nombre de dégâts reçus à la vie du personnage

    if (m_vie < 0) //Pour éviter d'avoir une vie négative
    {
        m_vie = 0; //On met la vie à 0 (cela veut dire mort)
    }
}

std::string Perso::nom(){
    return m_nom;
}
/*Systeme de defens avec implementation d'alea dans le cas de l'esquive*/
void Perso::defense(Perso &cible, int i){
    if(i==0){
        std::cout<<"Parage"<<std::endl;
        pointeur_arme->usure((cible.ptr_arme()->degat())/2);
        cible.recevoirDegats((pointeur_arme->degat())/2);
        cible.ptr_arme()->usure((pointeur_arme->degat())/2);
    }
    if(i==1){
        std::cout<<"Tentative d'esquive"<<std::endl;
        std::cout<<""<<std::endl;
        std::cout<<"Esquive en cours ..."<<std::endl;
        std::cout<<""<<std::endl;
        int j= nombrealea(1,3);

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        if(j==1){
            std::cout<<"Esquive ratée"<<std::endl;
            cible.recevoirDegats(pointeur_arme->degat());
        }
        else{
            std::cout<<"Esquive réussie"<<std::endl;

        }



    }
}



void Perso::boirePotionDeVie(int quantitePotion)
{
    m_vie += quantitePotion;

}


bool Perso::estVivant()
{
    return m_vie > 0;
}

bool Arme::broken()
{
    return m_dura <= 0;

}

int Perso::pointdevie()
{
    return m_vie;
}




void Perso::changerarme(int i){
    
    
    std::shared_ptr<Arme> temp;
    temp = pointeur_arme;

    pointeur_arme = inventaire[i];

    if (temp->nom() != "Mains" and temp->dura() > 0) {
        inventaire[i] = temp;
    }
    else{
        inventaire.erase(inventaire.begin()+i);
    }

    
    

}


void Perso::ajoutinventaire(std::string nomNouvelleArme){

    if (nomNouvelleArme == "Epeeenbois") {
        inventaire.push_back(std::make_shared<Epeeenbois>());
    } 
    else if (nomNouvelleArme == "Epeeenfer") {
        inventaire.push_back(std::make_shared<Epeeenfer>());
    }
    else if (nomNouvelleArme == "Leclerc") {
        inventaire.push_back(std::make_shared<Leclerc>());
    }

}

void Perso::ajoutinventaire2(std::shared_ptr<Arme> ptra){

    inventaire.push_back(ptra);


}

std::string Arme::nom(){


    return m_nomArme;


}

void Perso::voirinventaire(){

    int i=0;
    for(std::shared_ptr<Arme> x: inventaire){
        
        std::cout<<i<<":"<<x->nom()<<" de durabilite:"<<x->dura()<<std::endl;
        i=i+1;

    }
    
}

int Arme::degat(){


    return m_degat;


}

int Arme::dura(){


    return m_dura;


}

void Arme::usure(int i){

    m_dura=m_dura-i;

}

std::shared_ptr<Arme> Perso::ptr_arme(){

    return pointeur_arme;
}

int Perso::stock(){

    return inventaire.size();
}

void Perso::main(){

    pointeur_arme=std::make_shared<Mains>();
}


/*Systeme de combat*/


int combat(Perso &player, Perso &ennemi){
    std::cout<<"Un combat s'engage"<<std::endl;
    int choix;

    while(player.estVivant() and ennemi.estVivant()){
            std::cout << "Veux-tu parer (0) ou esquiver (1) ?"<<std::endl;
            std::cin >> choix;
            ennemi.defense(player,choix);
            std::cout<<"Vie du joueur:"<<player.pointdevie()<<std::endl;
            std::cout << "Attaque en cours ..."<<std::endl;
            player.defense(ennemi,nombrealea(0,1));
            std::cout<<"Vie de l'ennemi:"<<ennemi.pointdevie()<<std::endl;
            /*Il faut vérifier constamment si l'arme des combattants n'est pas brisée*/
            if(player.ptr_arme()->broken()){
                if(player.stock()!=0){
                    int k;
                    std::cout<<"Ton arme est brisée, tu dois en changer"<<std::endl;
                    player.voirinventaire();
                    std::cout << "Quelle arme souhaites-tu ?"<<std::endl;
                    std::cin>>k;
                    player.changerarme(k);
                }
                else{
                    std::cout<<"Tu n'avais rien dans ton sac, tu te bas maintenant à mains nues !"<<std::endl;
                    player.main();
                }
            }

            if(ennemi.ptr_arme()->broken()){

                if(ennemi.stock()!=0){
                    /*Si l'ennemi a du stuff dans son inventaire il récupére une arme au hasard dans celui ci*/
                    int k=nombrealea(0,player.stock()-1);
                    ennemi.changerarme(k);
                }

                else{
                    std::cout<<"Tu as brisé l'arme de l'ennemi : Ton adversaire se bat maintenant à mains nues !"<<std::endl;
                    ennemi.main();
                }

            }
}

if (player.estVivant()){
    std::cout<<"Tu as gagné le combat et tu peux maintenant dechiffrer un peu plus du Parchemin"<<std::endl;
    player.reveal();
    ennemi.loot(player);
    std::cout<<""<<std::endl;
    std::cout<<"En remerciement de ta glorieuse victoire sur le mal des villageois ont choisis de t'offrir de la soupe aux oignons : tu gagnes 50 points de vie"<<std::endl;
    player.boirePotionDeVie(50);
    return true;
}
else{
    return false;
}
}


std::string Perso::getmotcrypte(){
    return motcrypte;
}

/*Systeme de loot permettant de récupérer le stuff de l'ennemi si celui-ci n'est pas trop dégradé*/
void Perso::loot(Perso &player){
    if(pointeur_arme->nom()!="Mains"){
        player.ajoutinventaire2(pointeur_arme);
        std::cout<<"Tu as récupéré sur l'ennemi: "<<pointeur_arme->nom()<<std::endl;
    }
    int i=0;
    for(std::shared_ptr<Arme> x: inventaire){
        
        player.ajoutinventaire2(x);
        std::cout<<"Tu as récupéré sur l'ennemi: "<<x->nom()<<std::endl;
        i=1;

    }


}

/*Systeme de révélation d'une lettre du mot caché*/

void Perso::reveal(){

    if (indice==mot.size()){
        std::cout<<"Tu as déjà tout découvert"<<std::endl;
        return;
    }

    int m=nombrealea(1,mot.size()-indice);
    int k=0;
    for(int j=0;j<motcrypte.size();j++){
        
        if(motcrypte[j]=='*'){
            k=k+1;
        }

        if(k==m){
            motcrypte[j]=mot[j];
            break;

        }
    indice = indice+1;



        
    }



}

std::string Perso::getmot(){
    return mot;
}

std::shared_ptr<Perso> creationperso(std::string numero,int i){
    if(numero=="1"){
        return std::make_shared<Mage>();
    }
    if(numero=="2"){
        return std::make_shared<Guerrier>();
    }
    if(numero=="3"){
        return std::make_shared<Voleur>();
    }
    else{
        if(i==0){
        std::cout<<"Tu n'as pas choisi de classe, tu es donc un guerrier"<<std::endl;
        return std::make_shared<Guerrier>();
        }
    }
}

void Perso::stuff(){
    std::cout<<"Voici l'arme que tu as en main : "<<std::endl;
    std::cout<<ptr_arme()->nom()<<" de durabilite:"<<ptr_arme()->dura()<<std::endl;

    std::cout<<""<<std::endl;

    std::cout<<"Et voici le stuff dans ton inventaire :"<<std::endl;
    voirinventaire();
}

void Perso::changement(){
            std::string ent="";
            std::cout<<"Veux tu changer d'arme ? oui (0) ou non (1)"<<std::endl;
            int j;
            std::cin>>ent;

            if(ent=="0"){
                std::cout<<"Quel arme veux-tu ?"<<std::endl;
                std::cin>>j;
                changerarme(j);

            }
}





