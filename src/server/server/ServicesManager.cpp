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
        cout << url << endl;
        for(auto& service : services){
            if(url.find(service->getPattern()) != string::npos ){
                return service;    
            }
        }   
        return NULL;
          
    }

    HttpStatus ServicesManager::queryService(std::string& out, const std::string& in, const std::string& url, const std::string& method) {

        AbstractService* service = findService(url);
        
        Json::Value tmp;
        if (!service)
            throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" non trouvé");
        const string pattern = service->getPattern();
        int id = -1;
        
        if (url.size() > pattern.size()) {
            string end = url.substr(pattern.size());
            if (end[0] != '/')
                throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée (forme attendue: <service>/<nombre>)");
            end = end.substr(1);
            if (end.empty())
                throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée (forme attendue: <service>/<nombre>)");
            try {
                size_t pos = 0;
                id = stoi(end,&pos);
                if (pos != end.size())
                    throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée: '"+end+"' n'est pas un nombre");
            }
            catch(...) {
                throw ServiceException(HttpStatus::BAD_REQUEST,"Url malformée: '"+end+"' n'est pas un nombre");
            }
        }
        
        if(method == "GET"){ 
            HttpStatus status = service->get(tmp, id);
            out = tmp.toStyledString();
            return status;
        }
        else if(method == "PUT"){
            Json::Reader reader;
            Json::Value jsonIn;
            
            if (!reader.parse(in,jsonIn)){
                throw ServiceException(HttpStatus::BAD_REQUEST,"Données invalides: "+reader.getFormattedErrorMessages());
            }
            //cout << jsonIn.toStyledString() << endl;
            Json::Value jsonOut;
            //cout << service->getPattern() << endl;
            HttpStatus status = service->put(jsonOut,jsonIn);
            out = jsonOut.toStyledString();
            return status;
        }
        else if(method == "POST"){
            Json::Reader reader;
            Json::Value jsonIn;
            if(!reader.parse(in,jsonIn))
                throw ServiceException(HttpStatus::BAD_REQUEST,"Données invalides: "+reader.getFormattedErrorMessages());
            return service->post(jsonIn,id);
            }
        else if(method == "DELETE"){
            
            return service->remove(id);
            
        }
        throw ServiceException(HttpStatus::BAD_REQUEST,"Méthode "+method+" invalide");
    }
    
    
}