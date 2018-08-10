/*!
 * \class Tramway
 * \brief Specialization of the train type. Describes the object Tranway and all its associated methods.
 * \author Marie Brunet Carteaux <marie.brunet@orange.com>
 * \date May 7, 2018
 */

#ifndef CRASH_TEST_TRAMWAY_H
#define CRASH_TEST_TRAMWAY_H

#include "Train.h"

class Tramway : public Train {
private:

public:
    Tramway();
    Tramway(uint, uint, tm, tm, uint, bool, uint, vector< Coach >&, vector< Camera >&);
    ~Tramway() override;

    std::string getVehicleName(void) const override;
};


#endif //CRASH_TEST_TRAMWAY_H
