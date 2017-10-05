/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tests.h"
namespace state{

    void testsUnitaires(){
    
        cout << "Debut des tests sur les états :" << endl;
        
        cout << "Créons déjà un joueur, appelons le Moha !" << endl;
        Player p("Moha");
        cout << "Verifie qu'un joueur prénomé Moha a été créé...";
        if(p.getName() == "Moha") cout << "OK Moha est là !" << endl;
        else cout << "Oups erreur..." << endl;
        
        cout << "Tests sur les éléments" << endl;
        cout << "Création d'un élément de type paysage" << endl;
        
        Landscape l;
        cout << "Verifie qu'on à bien crée un paysage...";
        
        if(l.getTypeID()==1) cout << "OK" << endl;
        else cout << "Erreur" << endl;
        
        cout << "Verifie que ce paysage est bien statique et n'est pas interactif...";
        if(l.isStatic() && !l.isInteractive()) cout << "OK ça marché !" << endl;
        else cout << "Erreur" << endl;
        
        cout << "Voyons si on peut faire la bagarre en créant une armée et des colons...";
        Army a;
        Settlers s;
        
        if(a.getTypeID()==3 && s.getTypeID()==4) cout << "Ok !" << endl;
        else cout << "Oups ERREUR ! " << endl;
        
        cout << "Tests sur la ville " << endl;
        cout << "Construction d'une ville" << endl;
        City c;
        
        cout << "Verifie qu'elle a bien été construite...";
        if(c.getTypeID()==2) cout << "OK" << endl;
        else cout << "Oups ERREUR" << endl;
        
        cout << "Mettons y 3 constructions, le nombre max !" << endl;
        c.addConstruction(new Mine());
        c.addConstruction(new Farm());
        c.addConstruction(new Barrack());
        cout << "Verifions qu'on a bien 3 batiments dans la ville et qu'on ne peut plus en rajouter...";
        if(c.isFullOfConstructions()) cout << "OK jolie ville !" << endl;
        else cout << "Oups ERREUR " << endl;
        
        
        cout << "Test sur la grille du monde" << endl;
        
        cout << "Création d'un monde de dimension 2x2 avec 1 seul layer !" << endl;
        Monde m(2,2,1);
        cout << "Verification de la hauteur et la largeur..." << endl;
        if(m.getWidth() == 2 && m.getHeight() == 2) cout << "Ok jusqu'ici tout va bien !"<< endl;
        else cout << "Erreur ! " << endl;
        cout << "Largeur : " << m.getWidth() << " et Hauteur : " << m.getHeight() << endl;
        
        cout << "Mettons du paysage !" << endl;
        for(int i = 0; i< m.getWidth() ; i++)
            for(int j = 0; j < m.getHeight(); j++){
                m.set(i,j,0,new Landscape());
        }
        
        cout << "Vérifions que le monde est bien rempli de paysages...";
        bool result = true;
       
        for(int i = 0; i< m.getWidth() ; i++)
            for(int j = 0; j < m.getHeight(); j++){
                if(m.get(i,j,0)->getTypeID()!=1) result = false;
        }
        
        if(result) cout << "OK beau paysage !"<<endl;
        else cout << "Pfff Erreur..."<<endl;
        
        cout << "Pour finir créons un monde plus grand, de dimension 10x10 avec 2 layers" << endl;
        
        Monde m2(10,10,2);
        
        cout << "Verification de la hauteur et la largeur...";
        if(m2.getWidth() == 10 && m2.getHeight() == 10) cout << "Ok nickel !"<< endl;
        else cout << "Erreur ! " << endl;
        cout << "Largeur de " << m2.getWidth() << ", Hauteur de " << m2.getHeight() << " et Nombre de layers " << m2.getLayers().size()<<endl;
        
        cout << "Ajoutons un paysage sur le premier layer"<<endl;
        for(int i = 0; i< m2.getWidth() ; i++)
            for(int j = 0; j < m2.getHeight(); j++){
                m2.set(i,j,0,new Landscape());
        }
        cout << "Verifions le paysage...";
        result = true;
       
        for(int i = 0; i< m2.getWidth() ; i++)
            for(int j = 0; j < m2.getHeight(); j++){
                if(m2.get(i,j,0)->getTypeID()!=1) result = false;
        }
        
        if(result) cout << "OK encore un beau paysage !"<<endl;
        else cout << "Pfff Erreur..."<<endl;
        
        cout << "Ajoutons une ville en haut à gauche et une en bas à droite !"<<endl;
        m2.set(0,0,1,new City());
        m2.set(9,9,1,new City());
        cout << "Verifions qu'on a bien 2 villes au bon endroit...";
        if(m2.get(0,0,1)->getTypeID() == 2 && m2.get(9,9,1)->getTypeID() == 2) cout << "Okay" <<endl;
        else cout << "Erreur, Aucune ville"<<endl;
        
        cout << "Finnissons avec 2 armées ! on en créé deux en (3,3) et (4,3)" << endl;
        
        m2.set(3,3,1,new Army());
        m2.set(4,3,1,new Army());
        
        cout << "Verifions qu'elles sont au bon endroit...";
        if(m2.get(3,3,1)->getTypeID() == 3 && m2.get(4,3,1)->getTypeID() == 3) cout << "Ok elles sont là, ca va chauffer !" <<endl;
        else cout<<"ERREUR !!!"<<endl;
        
        
        
    }

}

