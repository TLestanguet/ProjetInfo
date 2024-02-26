#pragma once

#include <string>
#include <memory>
#include <vector>
#include <random>




class Arme
{
    public:

    Arme();
    std::string nom();
    int degat();
    int dura();
    void usure(int i);
    bool broken();
    std::string durabilite();
    


    protected:

    int m_degat;
    int m_dura;
    std::string m_nomArme; 
};


class Perso
{
    public:

    Perso();
    void recevoirDegats(int nbDegats);
    void defense(Perso &cible, int i);
    void boirePotionDeVie(int quantitePotion);
    bool estVivant();
    int pointdevie();
    void changerdetape();
    std::shared_ptr<Arme> ptr_arme();
    void ajoutinventaire(std::string nomNouvelleArme);
    void changerarme(int i);
    void voirinventaire();
    int stock();
    void main();
    void loot(Perso &player);
    void reveal();
    void ajoutinventaire2(std::shared_ptr<Arme> ptra);
    std::string getmotcrypte();
    std::string getmot();
    void stuff();
    std::string nom();
    void changement();

    protected:

    std::string m_nom;
    int indice; /*Nombre d'indice sur le mot caché reçu */
    std::string mot;
    std::string motcrypte;
    int m_vie;
    std::shared_ptr<Arme> pointeur_arme;
    std::vector<std::shared_ptr<Arme>> inventaire;

};


class Guerrier : public Perso
{
    public:
    Guerrier();
};

class Mage : public Perso
{
    public:
    Mage();
};

class Voleur : public Perso
{
    public:
    Voleur();
};



class Mains : public Arme
{
    public:
    Mains();
};

class Epeeenbois : public Arme
{
    public:
    Epeeenbois();
};

class Epeeenfer : public Arme
{
    public:
    Epeeenfer();
};

class Leclerc: public Arme
{
public:

    Leclerc();

};

int combat(Perso &player, Perso &ennemi);

int nombrealea(int i,int j);

std::shared_ptr<Perso> creationperso(std::string numero,int i);





