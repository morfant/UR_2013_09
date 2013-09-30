(
SystemClock.sched(0.0,{ arg time, i, j, k;
    time.postln;
	("i: " +i).postln;
	    ("j: " +j).postln;
	    ("k: " +k).postln;
	1.0;
});
)

SystemClock.clear;

~holdTimeList[0, 7].add(~valueList[0, 7]);
~valueList[0, 7];


(// get list size
for(0, 2 - 1, {| i |
	for(0, 8 - 1, {| j |
		("ht" + i ++ "-" ++ j + ":" + ~holdTimeList[i, j].size).postln;
		("vl" + i ++ "-" ++ j + ":" + ~valueList[i, j].size).postln;
	});
});
)

[[1, 1], [2, 1], [3, 1], [4, 1]] + [10, 0]