// PluginFS1.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "FS1.hpp"

static InterfaceTable* ft;

namespace FS1 {

FS1::FS1() {
    mCalcFunc = make_calc_function<FS1, &FS1::next>();
    next(1);
}

void FS1::next(int nSamples) {

    // Audio rate input
    const float* input = in(0);

    // Control rate parameter: gain.
    const float gain = in0(1);

    // Output buffer
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain;
    }
}

} // namespace FS1

PluginLoad(FS1UGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<FS1::FS1>(ft, "FS1", false);
}
