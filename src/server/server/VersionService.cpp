/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "VersionService.h"

namespace server{

    VersionService::VersionService() : AbstractService("/version") {

    }

    HttpStatus VersionService::get(Json::Value& out, int id) const {
        out["major"] = 4;
        out["minor"] = 2;
    //out = tmp.toStyledString();
        return HttpStatus::OK;
    }
    
}