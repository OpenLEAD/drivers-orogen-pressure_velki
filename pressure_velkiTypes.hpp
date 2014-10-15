#ifndef pressure_velki_TYPES_HPP
#define pressure_velki_TYPES_HPP

#include <string>
#include <vector>

namespace pressure_velki {
    /* One device on the Velki bus */
    struct Device
    {
        std::string name;
        int id;
    };
    typedef std::vector<Device> Devices;
}

#endif

