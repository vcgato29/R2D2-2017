/**
 * \file
 * \brief     Main of the NAVSYS feature branch
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"

int main() {
    Client(sf::IpAddress::LocalHost, 5000).run();
    return 0;
}