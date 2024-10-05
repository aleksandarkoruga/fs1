// PluginFS1.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace FS1 {

class FS1 : public SCUnit {
public:
    FS1();

    // Destructor
    // ~FS1();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace FS1
