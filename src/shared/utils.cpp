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
        
        int sizeX = 0;
        int sizeY = 0;
       		
        while(!fichier.eof()){
            std::getline(fichier,ligne);
            std::stringstream stream(ligne);
            
            sizeX = 0;
            sizeY++;

            while(getline(stream, valeur,',')){
			
                vcarte.push_back(atoi(valeur.c_str()));
		sizeX++;	
            }
            
        }
                
        return vcarte;
}

std::vector<int> getDimentionsCSV(const std::string fileName){
    
        std::vector<int> vcarte, dimensions;
	std::ifstream fichier;
        fichier.open(fileName, std::ios::in);
        std::string ligne,valeur;
        
        int sizeY = 0;
        int sizeX = 0;
        int sizeTot = 0;
       		
        while(!fichier.eof()){
            std::getline(fichier,ligne);
            std::stringstream stream(ligne);
            
            sizeY++;

            while(getline(stream, valeur,',')){
			
                sizeTot++;	
            }
            
        }
        
        sizeY--;
        sizeX = sizeTot / sizeY;
        
        dimensions.push_back(sizeX);
        dimensions.push_back(sizeY);        
        return dimensions;
    
}

