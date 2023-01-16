//
// Created by loona on 15/01/23.
//

#include "globvars.h"

namespace glob {

    std::ifstream f("globvars/globvars.json");
    const json g = json::parse(f);

    const int RENDER_DIST = g["RENDER_DISTANCE"];
}