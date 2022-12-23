#pragma once
#ifndef OKPROJECT_INTOJSONFILE_H
#define OKPROJECT_INTOJSONFILE_H
#include <iostream>
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

void graphIntoJson(int n, int** arr, json j){
    for(int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            j["graph"][i][k] = arr[i][k];
            
        }
    }
}


#endif //OKPROJECT_INTOJSONFILE_H