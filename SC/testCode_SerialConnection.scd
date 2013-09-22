(// on-off loop for Test Button
fork{
	100.do{| i |
		{~testBut.valueAction_(1);
		~testBut.value.postln;
			}.defer;
		0.001.wait;

		{~testBut.valueAction_(0);
		~testBut.value.postln;
			}.defer;
		0.001.wait;

		i.postln;
	}
}
)


(// on-off loop for onOff Button
fork{
	50000.do{| i |
		{~buts[0, 0].valueAction_(1);
		~buts[0, 0].value.postln;
			}.defer;
		0.001.wait;

		{~buts[0, 0].valueAction_(0);
		~buts[0, 0].value.postln;
			}.defer;
		0.001.wait;

		i.postln;
	}
}
)
AppClock
~testBut.valueAction_(1);
~testBut.value;
~buts[0, 0].valueAction_(1)