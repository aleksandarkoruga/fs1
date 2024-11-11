// PluginFS1.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include "hilbert-iir/hilbert.h"

namespace FS1 {

class Phasor
{
    
public:
    Phasor(double sr);

    float next(float freq);
    inline float& getVal() { return m_out; }
private:
    float m_out;


    uint32_t m_val;
    int64_t m_increment;
    double m_sampleRate;
    double m_invSampleRate;
    const double max32 = static_cast<double>(0xffffffff);
    const double max32inv = 1.0/static_cast<double>(0xffffffff);
    //float m_freq;
    //float m_phase;
    //uint32_t m_iphase;

};


class FS1 : public SCUnit {
public:
    FS1();

    // Destructor
    // ~FS1();
    
private:


    // Calc function
    void next(int nSamples);

    std::unique_ptr< signalsmith::hilbert::HilbertIIR<float>> m_hilbert;
    float m_upperSideband;
    float m_lowerSideband;
    
    Phasor m_cosOsc;
    Phasor m_sinOsc;
    Phasor m_lfo1;
    Phasor m_lfo2;

    float m_fb1;
    float m_fb2;


    float m_out;
    // Member variables
};

} // namespace FS1
