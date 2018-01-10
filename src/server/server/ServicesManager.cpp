/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ServicesManager.h"
#include "ServiceException.h"
#include <iostream>

using namespace std;

namespace server{

    void ServicesManager::registerService(AbstractService* service) {
        services.push_back(service);
    }

    
    AbstractService* ServicesManager::findService(const std::string& url) const {
        
        for(auto& service : services){
            //cout << service->getPattern() << endl;
            //cout << "Url " << url << endl;
            if(url.find(service->getPattern()) != string::npos ){
                return service;    
            }
        }   
        return NULL;
          
    }

    HttpStatus ServicesManager::queryService(std::string& out, const std::string& in, const std::string& url, const std::string& method) {
        /*
        if(url == "/version"){
            if(method == "GET"){
    		Json::Value tmp;;
    		findService(url)->get(tmp, -1);
    		out = tmp.toStyledString();
    		return HttpStatus::OK;   	
    	}
	}
         */
        cout << "Demande" << endl;
        AbstractService* service = findService(url);
        Json::Value tmp;
        if (!service)
            throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" non trouvé");
        
        if(method == "GET"){ 
            HttpStatus status = service->get(tmp, -1);
            out = tmp.toStyledString();
            return status;
        }
        throw ServiceException(HttpStatus::BAD_REQUEST,"Méthode "+method+" invalide");
    }
    
    
}