/*!
 * \class Tube
 * \brief Specialization of the train type. Describes the object Tube and all its associated methods.
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef MOD_TUBE_H
#define MOD_TUBE_H

#include "Train.h"

class Tube: public Train {

public:
    Tube();
    Tube(uint, uint, tm, tm, uint, bool, uint, vector<Coach>&, vector< Camera >&);
    ~Tube();

    std::string getVehicleName(void) const override;
};

#endif //MOD_TUBE_H
