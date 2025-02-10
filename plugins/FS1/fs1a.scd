



(
SynthDef(\fs1a_shifter, {
	| gain=1.0, freq1=300.0, freq2=350.0, lfoFreq1=0.4, lfoFreq2=100.9, lfoAmt1=40.0, lfoAmt2=50.0, fb1=0.5, fb2=0.5,sidebandMix=0.5, outMix=0.5|

	var fs =FS1.ar( Saw.ar(40) , K2A.ar(gain), K2A.ar(freq1), K2A.ar(freq2), K2A.ar(lfoFreq1), K2A.ar(lfoFreq2), K2A.ar(lfoAmt1), K2A.ar(lfoAmt2), K2A.ar(fb1), K2A.ar(fb2),K2A.ar(sidebandMix), K2A.ar(outMix)).poll;
	Out.ar(0,fs.dup)
}

).add
)
a=Synth.new(\fs1a_shifter)


a.set(\gain, 0.6,\freq1,18.0, \freq2,1.1, \lfoFreq1,100.3, \lfoFreq2,1000, \lfoAmt1,0.10, \lfoAmt2,0.5, \fb1,0.999, \fb2,0.999,\sidebandMix,0.001, \outMix,0 )


a.set(\gain, 1.6,\freq1,30.0, \freq2,270.0, \lfoFreq1,1.3, \lfoFreq2,1, \lfoAmt1,200.10, \lfoAmt2,90.5, \fb1,0.9, \fb2,0.95,\sidebandMix,0.5, \outMix,0 )






