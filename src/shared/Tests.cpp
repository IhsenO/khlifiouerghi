/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tests.hpp"


void testsAIRandom(Engine& engine, State& state){
    stack<Action*> pile;
    RandomAI random(state, engine);
    random.run(engine, pile);
    
}


void testsEngine(int i, Engine& engine, State& state){
    
    stack<Action*> pile;
    std::cout << "Epoque : " << i + 1 << std::endl;
    if(i == 0){
        std::cout << "Ajout de la commande qui déplace une armée dans un endroit accessible : "<< std::endl;
        MoveCharCommand move(4,4,6,6);
        engine.runCommand(&move, pile);
        std::cout << "Vérifie Déplacement... ";
        if(state.getMonde().get(4,4,2) == NULL && state.getMonde().get(6,6,2) != NULL)
            if(state.getMonde().get(6,6,2)->getTypeID() == 3) std::cout << "OK" <<std::endl;
    }
    else if(i == 1){
        std::cout << "Ajout de la commande qui déplace une armée dans un endroit accessible : "<< std::endl;
        MoveCharCommand move(6,6,8,8);
        engine.runCommand(&move, pile);
        std::cout << "Vérifie Déplacement... ";
        if(state.getMonde().get(6,6,2) == NULL && state.getMonde().get(8,8,2) != NULL)
            if(state.getMonde().get(8,8,2)->getTypeID() == 3) std::cout << "OK" <<std::endl;
   
    }
    else if(i == 2){
        std::cout << "Ajout de la commande qui déplace une armée dans un endroit inaccessible : "<< std::endl;
        MoveCharCommand move(8,8,10,10);
        engine.runCommand(&move, pile);
        std::cout << "Vérifie qu'il n'y a pas déplacement... ";
        if(state.getMonde().get(8,8,2) != NULL) std::cout << "OK" <<std::endl;
    }
    else if(i == 3){
        std::cout << "Ajout de la commande qui déplace une armée dans un endroit au delà de sa portée : "<< std::endl;
        MoveCharCommand move(8,8,4,4);
        engine.runCommand(&move, pile);
        std::cout << "Vérifie qu'il n'y a pas déplacement... ";
        if(state.getMonde().get(8,8,2) != NULL) std::cout << "OK" <<std::endl;
    }
    else if(i == 4){
        std::cout << "Essayons de construire une Caserne dans la ville :" << std::endl;
        ConstructCommand construct(2,2,new Barrack());
        engine.runCommand(&construct, pile);
        std::cout << "Vérifie la construction... ";
        if(state.getMonde().get(2,2,1) != NULL){
            if(state.getMonde().get(2,2,1)->getTypeID() == 2){
                City *c = (City*)state.getMonde().get(2,2,1);
                if(c->getListConst().size() == 1) std::cout << "OK" <<std::endl;
            }
        }
    }
    else if(i == 5){
        std::cout << "Essayons de construire une Ferme dans la ville :" << std::endl;
        ConstructCommand construct(2,2,new Farm());
        engine.runCommand(&construct, pile);
        std::cout << "Vérifie la construction... ";
        if(state.getMonde().get(2,2,1) != NULL){
            if(state.getMonde().get(2,2,1)->getTypeID() == 2){
                City *c = (City*)state.getMonde().get(2,2,1);
                if(c->getListConst().size() == 2) std::cout << "OK" <<std::endl;
            }
        }
    }
    else if(i == 6){
        std::cout << "Essayons de construire une Mine dans la ville :" << std::endl;
        ConstructCommand construct(2,2,new Mine());
        engine.runCommand(&construct, pile);
        std::cout << "Vérifie la construction... ";
        if(state.getMonde().get(2,2,1) != NULL){
            if(state.getMonde().get(2,2,1)->getTypeID() == 2){
                City *c = (City*)state.getMonde().get(2,2,1);
                if(c->getListConst().size() == 3) std::cout << "OK" <<std::endl;
            }
        }
    }
    else if(i == 7){
        std::cout << "Essayons de rajouter une construction dans une ville pleine :" << std::endl;
        ConstructCommand construct(2,2,new Mine());
        engine.runCommand(&construct, pile);
        std::cout << "Vérifie qu'il n'y a pas de construction... ";
        if(state.getMonde().get(2,2,1) != NULL){
            if(state.getMonde().get(2,2,1)->getTypeID() == 2){
                City *c = (City*)state.getMonde().get(2,2,1);
                if(!c->canBuild(2)) std::cout << "OK" <<std::endl;
            }
        }
    }
    else if(i == 8){
        std::cout << "Essayons d'améliorer une ville :" << std::endl;
        UpgradeCommand up(2,2);
        engine.runCommand(&up, pile);
        std::cout << "Vérifie qu'on a amélioré la ville... ";
        if(state.getMonde().get(2,2,1) != NULL){
            if(state.getMonde().get(2,2,1)->getTypeID() == 2){
                City *c = (City*)state.getMonde().get(2,2,1);
                if(c->getDefense()==2) std::cout << "OK" <<std::endl;
            }
        }
    }
    else if(i == 9){
        std::cout << "Essayons d'améliorer une ville encore :" << std::endl;
        UpgradeCommand up(2,2);
        engine.runCommand(&up, pile);
        std::cout << "Vérifie qu'on a encore amélioré la ville... ";
        if(state.getMonde().get(2,2,1) != NULL){
            if(state.getMonde().get(2,2,1)->getTypeID() == 2){
                City *c = (City*)state.getMonde().get(2,2,1);
                if(c->getDefense()==3) std::cout << "OK" <<std::endl;
            }
        }
    }
    else if(i == 10) {      
        std::cout << "Essayons la commande fin de tour, qui doit incrémenter nos ressources selon nos villes et batiments :" << std::endl;
        std::cout << "Avant Commande ---> OR : " << state.getPlayer(state.getIdPlayer())->getGold() <<" | Nourriture : " << state.getPlayer(state.getIdPlayer())->getFood() <<std::endl;
        EndOfTurnCommand end;
        engine.runCommand(&end, pile);
        std::cout << "Apres Commande ---> OR : " << state.getPlayer(state.getIdPlayer())->getGold() <<" | Nourriture : " << state.getPlayer(state.getIdPlayer())->getFood() <<std::endl;
        
    }
    
    else if(i == 11){
        std::cout << "Maintenant on va commencer la bagarre :" << std::endl;
        std::cout << "On ajoute une Armée adversaire : " << std::endl;
        state.getMonde().set(8,10,2,new Army());
        state.getMonde().get(8,10,2)->setIdPlayer(2);
        std::cout << "L'armée 1 va attaquer la seconde : " << std::endl;
    }    
        
    else if(i == 12){
        
        AttackArmyCommand attack(8,8,8,10);
        engine.runCommand(&attack, pile);    
    }
        
    else if(i == 13){
        std::cout << "Maintenant on va attaquer une ville, on met une armée en position : " << std::endl;
        state.getMonde().set(16,11,2,new Army());
        state.getMonde().get(16,11,2)->setIdPlayer(1);
                        
    }
    else if(i == 14){
        AttackCityCommand attCity(16,11,18,11);
        engine.runCommand(&attCity, pile);
    }
    else if(i == 15){
        std::cout << "On positionne une armée pour essayer une fuision entre 2 armées du meme camps : " << std::endl;
        state.getMonde().set(10,10,2,new Army());
        state.getMonde().get(10,10,2)->setIdPlayer(1);
        Army *a = (Army*)state.getMonde().get(10,10,2);
        std::cout << "L'armée cible possède "  << a->getSoldiers() << " soldats !"<< std::endl;
    }
    else if(i == 16){
        ArmyFusionCommand fusion(8,10,10,10);
        engine.runCommand(&fusion, pile);
        Army *a = (Army*)state.getMonde().get(10,10,2);
        std::cout << "Après la fusion il y a "  << a->getSoldiers() << " soldats !"<< std::endl;
    }
    else if(i == 17){
        std::cout << "Essaie de faire sortir des soldats d'une ville, on en sortira 50 : " << std::endl;
        City *c = (City*)state.getMonde().get(2,2,1);
        std::cout << "La ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        LeaveCityCommand leave(2,2,4,4,50);
        engine.runCommand(&leave, pile);
        std::cout << "Apres la création de l'armée, la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        Army *a = (Army*)state.getMonde().get(4,4,2);
        std::cout << "L'Armée possede : " << a->getSoldiers() << " Soldats !" << std::endl;
    }
    else if(i == 18){
        std::cout << "Essaie de rentrer des soldats dans une ville, on en rentre 25 : " << std::endl;
        City *c = (City*)state.getMonde().get(2,2,1);
        std::cout << "Pour l'instant la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        EnterCityCommand enter(4,4,2,2,25);
        engine.runCommand(&enter, pile);
        std::cout << "Apres l'ajout de l'armée, la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        Army *a = (Army*)state.getMonde().get(4,4,2);
        std::cout << "L'Armée possede : " << a->getSoldiers() << " Soldats !" << std::endl;
    }
    else if(i == 19){
        std::cout << "Essaie de rentrer des soldats dans une ville, on en rentre 25, soit toute l'armée : " << std::endl;
        City *c = (City*)state.getMonde().get(2,2,1);
        std::cout << "Pour l'instant la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        EnterCityCommand enter(4,4,2,2,25);
        engine.runCommand(&enter, pile);
        std::cout << "Apres l'ajout de l'armée, la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
    }
    else if(i == 20){
        std::cout << "On va essayer de créer des soldats : "  << std::endl;
        City *c = (City*)state.getMonde().get(2,2,1);
        std::cout << "Pour l'instant la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        std::cout << "Avant Commande ---> OR : " << state.getPlayer(state.getIdPlayer())->getGold() <<" | Nourriture : " << state.getPlayer(state.getIdPlayer())->getFood() <<std::endl;
        MakeSoldiersCommand make(2,2);
        engine.runCommand(&make, pile);
        std::cout << "Ensuite la ville possede : " << c->getSoldiers() << " Soldats !" << std::endl;
        std::cout << "Apres Commande ---> OR : " << state.getPlayer(state.getIdPlayer())->getGold() <<" | Nourriture : " << state.getPlayer(state.getIdPlayer())->getFood() <<std::endl;
    }
    else if(i == 21){
        std::cout << "On va essayer de diviser une armée : " << std::endl;
        Army *a = (Army*)state.getMonde().get(10,10,2);
        std::cout << "L'Armée possede : " << a->getSoldiers() << " Soldats avant !" << std::endl;
        SplitArmyCommand split(10,10,10,12,50);
        engine.runCommand(&split, pile);
        std::cout << "L'Armée 1 possede : " << a->getSoldiers() << " Soldats après !" << std::endl;
        Army *a2 = (Army*)state.getMonde().get(10,12,2);
        std::cout << "L'Armée 2 possede : " << a2->getSoldiers() << " Soldats après !" << std::endl;
    }
    else if(i == 22){
        std::cout << "Fin des Tests !"  << std::endl;
    }
           
    
}




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
        if(c.canBuild(4)) cout << "OK jolie ville !" << endl;
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

void menu(){
    cout << "Usage:  ./bin/client <mode>" << endl;
    cout << "Modes disponibles: " << endl;
    cout << "   hello: affiche un simple message dans la console" << endl;
    cout << "   state: effectue des opérations élémentaires sur l'état" << endl;
    cout << "   render: affiche un état" << endl;
    cout << "   engine: teste le moteur de jeu" << endl;
    cout << "   random_ai: teste le jeu avec une IA aléatoire" << endl;
    cout << "   heuristic_ai: teste le jeu avec une IA heuristique" << endl;
    cout << "   rollback: teste le rollback" << endl;
    cout << "   deep_ai: teste le jeu avec une IA avancé" << endl;
} 

