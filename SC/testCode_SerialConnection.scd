(// on-off loop for Test Button
fork{
	100.do{| i |
		{~testBut.valueAction_(1);
		~testBut.value.postln;
			}.defer;
		0.1.wait;

		{~testBut.valueAction_(0);
		~testBut.value.postln;
			}.defer;
		0.1.wait;

		i.postln;
	}
}
)


(// on-off loop for onOff Button
f = fork{
	40.do{| i |
		{~buts[0, 0].valueAction_(1);
		~buts[0, 0].value.postln;
			}.defer;
		0.1.wait;

		{~buts[0, 0].valueAction_(0);
		~buts[0, 0].value.postln;
			}.defer;
		0.3.wait;

		i.postln;
	}
}
)

(// on-off loop for onOff Button
g = fork{
	20.do{| i |
		{~buts[0, 5].valueAction_(1);
		~buts[0, 5].value.postln;
			}.defer;
		1.5.wait;

		{~buts[0, 5].valueAction_(0);
		~buts[0, 5].value.postln;
			}.defer;
		1.5.wait;

		i.postln;
	}
}
)


(// test loop for slider
f = fork{
	40.do{| i |
		{~slids[0, 0].valueAction_(1);
		~slids[0, 0].value.postln;
			}.defer;
		0.3.wait;

		{~slids[0, 0].valueAction_(0);
		~slids[0, 0].value.postln;
			}.defer;
		0.3.wait;

		i.postln;
	}
}
)
AppClock
~testBut.valueAction_(1);
~testBut.value;
~buts[0, 0].valueAction_(1)