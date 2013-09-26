// Make list manually. [value, holdTime] pairs.
(
f.stop;
f = fork{
	100.do{
//		[[1, 1], [2, 1], [3, 1], [4, 1]]
//		[[10, 1], [20, 1], [30, 1], [40, 1]]
//		[[80, 1], [90, 1], [100, 1], [110, 1], [120, 1], [130, 1], [140, 1], [150, 1]]
//		[[70, 1], [60, 1], [55, 1], [50, 1], [45, 1], [40, 1], [30, 1], [20, 1],[5, 1]]

//		[[40, 1], [30, 0.5], [40, 0.5], [60, 1], [70, 1]] //라솔파미레
		[[70, 1], [60, 1], [40, 1], [60, 1], [70, 1],[5, 1],
		[60, 0.5], [255, 0.5], [40, 0.25], [60, 0.5], [80, 1.5]]

		.do{| i , j |
			{
				~slids[0, 0].valueAction_(i[0].linlin(1, 255, 0.0, 1.0));
			}.defer;
			// ("i[0]: " + i[0]).postln;
			// ("i[1]: " + i[1]).postln;
			i[1].wait;
		}
	}
}
)

(
g.stop;
g = fork{
	100.do{
		[[118, 0.1], [20, 0.2], [3, 0.3], [60, 0.4], [100, 0.1], [200, 0.5]]


		.do{| i , j |
			{
				~slids[0, 0].valueAction_(i[0].linlin(1, 255, 0.0, 1.0));
			}.defer;
			// ("i[0]: " + i[0]).postln;
			// ("i[1]: " + i[1]).postln;
			i[1].wait;
		}
	}
}
)

(
h.stop;
h = fork{
	10.do{
		[[118, 1.6], [20, 1.6], [30, 1.6], [60, 3.2]]


		.do{| i , j |
			{
				~slids[0, 6].valueAction_(i[0].linlin(1, 255, 0.0, 1.0));
			}.defer;
			// ("i[0]: " + i[0]).postln;
			// ("i[1]: " + i[1]).postln;
			i[1].wait;
		}
	}
}
)

(
f.stop;
f = fork{
	100.do{
		~final
		.do{| i , j |
			{
				~slids[0, 1].valueAction_(i[0]);
			}.defer;
			("i[0]: " + i[0]).postln;
			("i[1]: " + i[1]).postln;
			i[1].wait;
		}
	}
}
)



(
f.stop;
r = Routine({
	10.do{
		[[1, 2], [2, 0.1], [3, 2], [6, 0.4]]

		.do{| i , j |
			{
				~slids[0, 1].valueAction_(i[0]);
			};
			("i[0]: " + i[0]).postln;
			("i[1]: " + i[1]).postln;
			i[1].wait;
		}
	}
});
AppClock.play(r);
)
AppClock.clear;
SystemClock.clear;
f.stop;
List
~sum = List.new;
~ss = List.with(0, 1);
~dd = List.with(10,20);
~dd.class;
~sum.add(~ss);

// mearge value and holdTime
~holdTimeList[].removeAt(0);

~sum.add(~valueList);
~sum.add(~holdTimeList);

// lace to one list
~laced = ~sum.lace(~valueList.size + ~holdTimeList.size);


(
~final = List.newClear;

~laced.pairsDo({| a, b |
	~tList = List.with(a, b);
	~final.add(~tList);
})

)
~final.postln;




~holdTimeList
~valueList;

~holdTimeList.size;
~valueList.size;



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