// PluginFS1.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "FS1.hpp"

static InterfaceTable* ft;

namespace FS1 {

    Phasor::Phasor(double sr): m_out(0.f), m_val(0UL),m_increment(0LL),m_sampleRate(sr), m_invSampleRate(1.0f/sr)
    {
    }
    float Phasor::next(float freq) 
    {

        m_increment = static_cast<int64_t>((static_cast<double>(freq) * m_invSampleRate) * max32);
        //m_iphase = static_cast<uint32_t>((phase) * static_cast<double>(0xffffffff));

        m_val = static_cast<uint32_t>( static_cast<int64_t>(m_val) +m_increment);
        m_out = static_cast<float>( static_cast<double>(m_val) * max32inv );
        return m_out;
    }

    // /////////////////////////////////////////////////////////////////////


    FS1::FS1(): 
        m_hilbert(std::make_unique<signalsmith::hilbert::HilbertIIR<float>>(static_cast<float>(mWorld->mSampleRate), 1, 2.0f)),
        m_upperSideband(0.f),
        m_lowerSideband(0.f),
        m_cosOsc(Phasor(mWorld->mSampleRate)),
        m_sinOsc(Phasor(mWorld->mSampleRate)),
        m_lfo1(Phasor(mWorld->mSampleRate)),
        m_lfo2(Phasor(mWorld->mSampleRate)),
        m_fb1(0.f),
        m_fb2(0.f),
        m_out(0.f)
    {
    mCalcFunc = make_calc_function<FS1, &FS1::next>();
    
    

    next(1);

}



void FS1::next(int nSamples) {

    // Audio rate input
    const float* input = in(0);

    // Control rate parameter: gain.
    const float* gain = in(1);


    const float* freq1 = in(2);
    const float* freq2 = in(3);

    const float* lfoFreq1 = in(4);
    const float* lfoFreq2 = in(5);

    const float* lfoAmt1 = in(6);
    const float* lfoAmt2 = in(7);

    const float* fb1 = in(8);
    const float* fb2 = in(9);

    const float* sidebandMix = in(10);
    const float* outMix = in(11);
    

    // Output buffer
    float* outbuf = out(0);
    
    // simple gain function
    for (auto i = 0; i < nSamples; ++i) {

        auto transform = (*m_hilbert)(std::tanh( input[i] + fb1[i]*m_fb1 + fb2[i]*m_fb2 ));

        m_upperSideband = (transform.first * std::cos(m_cosOsc.next(freq1[i] + lfoAmt1[i]*(m_lfo1.next(lfoFreq1[i])) * twopi_f))) -
            (transform.second * std::sin(m_sinOsc.next(freq2[i] + (lfoAmt2[i] * std::cos(twopi_f*m_lfo2.next(lfoFreq2[i]))) * twopi_f) )); // Upper sideband

        m_lowerSideband = ( transform.first * std::cos( m_cosOsc.getVal() * twopi_f))
            + (transform.second * std::sin(m_sinOsc.getVal() * twopi_f)); // Lower sideband

        //mix sidebands
        m_out = sidebandMix[i] * m_upperSideband + (1.f - sidebandMix[i]) * m_lowerSideband;

        m_fb1 = std::tanh( m_out );

        outbuf[i] = std::tanh( input[i]* outMix[i] + ((1.f-outMix[i])* m_out) * gain[i] );

        m_fb2 = outbuf[i];

    }
}

} // namespace FS1

PluginLoad(FS1UGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<FS1::FS1>(ft, "FS1", false);
}
