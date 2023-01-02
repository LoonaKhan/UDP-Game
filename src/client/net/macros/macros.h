//
// Created by loona on 02/01/23.
//

#pragma once

#include <requests.h>

namespace macrs{
    void verifyOnline(net::UDPConn &c, int id);

    void readRes(net::UDPConn &c, int &cred);

    void UpdateCred(int id, int *cred);

}