FS1 : UGen {
	*ar { |input, gain, freq1, freq2, lfoFreq1, lfoFreq2, lfoAmt1, lfoAmt2, fb1, fb2,sidebandMix, outMix|
		^this.multiNew('audio', input, gain, freq1, freq2, lfoFreq1, lfoFreq2, lfoAmt1, lfoAmt2, fb1, fb2,sidebandMix, outMix);
	}
	 	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
