// Make list manually. [value, holdTime] pairs.
(
f.stop;
f = fork{
	100.do{
		[[1, 2], [2, 0.1], [3, 2], [6, 0.4], [], [], [], []]


		.do{| i , j |
			{
				~slids[0, 1].valueAction_(i[0].linlin(1, 255, 0.0, 1.0));
			}.defer;
			("i[0]: " + i[0]).postln;
			("i[1]: " + i[1]).postln;
			i[1].wait;
		}
	}
}
)

f.stop;
List

// Auto list maker
(
~holdTimeList = List.newClear;
~valueList = List.newClear;


~value = 0;
~pValue = 0;

~time = 0;
~pTime = 0;


var rec = 0;

~value = ~slids[0, 0].value;

~recList = {
	// Save time interval
	~getCurrentTime.value; //get current time
	~holdTimeList.add = ~pTime - ~time;
	~pTime = ~time;

	// Save value
	~value = ~slids[0, 0].value;
	~valueList.add = ~value;
	~pValue = ~value; //routine으로 만들어야 할지도.
}

});

)

(
~getCurTime = {SystemClock.sched(0.0,{ arg time;
    time.postln;
	~currentTime = ((time*1000).round) / 1000;
	~currentTime.postln;
	nil; //just do once
});
};
)

~getCurTime.value;

SystemClock.clear;