/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utils.hpp"
#include <iostream>

std::vector<int> loadCSV(const std::string fileName){
    
    std::vector<int> vcarte;
	std::ifstream fichier;
        fichier.open(fileName, std::ios::in);
        std::string ligne,valeur;
       		
        while(!fichier.eof()){
            std::getline(fichier,ligne);
            std::stringstream stream(ligne);

		
            while(getline(stream, valeur,',')){
			
                vcarte.push_back(atoi(valeur.c_str()));
			
            }
        }
        
        return vcarte;
}