/*
Arduino의 SerialMonitor와 함께 사용할 수 없다.

녹음중인 채널을 끝내지 않고 다른 채널의 슬라이더를 움직이면 에러가 발생한다.
*/
~buts.class;
~buts.add
(
var row = 2;
var column = 8;
var windowWidth = 800;
var windowHeight = 250;
var serialPortWhereToGet = "/dev/tty.usbmodem12341";

// Rec
var recFlag = false;

// Quit
var qBut;

// Test Button
var ptVal = 0;
var tVal = 0;

// Buttons
var butSize = 40;
var butIntervalX = 80;
var butIntervalY = 80;
var pbVal = 0; // store previous button val
var bVal = 0;

// Sliders
var slidSizeX = 80;
var slidSizeY = 20;
var slidIntervalX = 60;
var slidIntervalY = 10;
var psiVal = 0; // store previous (int)slider val
var siVal = 0;

// Local variable
var bLeft = 0;
var bTop = 0;

// Index holder
var idxRow = 0;
var idxColumn = 0;

// Routine
var routine = Array2D.new(row, column);

// Sliders array2D
~slids = Array2D.new(row, column);

// Buttons array2D
~buts = Array2D.new(row, column);

// Rec Buttons array2D
~recButs = Array2D.new(row, column);

// List for record
~holdTimeList = Array2D.new(row, column);
~valueList = Array2D.new(row, column);

for(0, row - 1, {| i |
	for(0, column - 1, {| j |
		~holdTimeList[i, j] = List.newClear();
		~valueList[i, j] = List.newClear();
	});
});


// Main Window
w = Window.new("GUI Introduction", Rect(0, 500, windowWidth, windowHeight));

// Array2D init with nil
for(0, row - 1, {| i |
	for(0, column - 1, {| j |
		~slids[i, j] = nil;
		~buts[i, j] = nil;
		~recButs[i, j] = nil;
	});
});

// Serial setup
//SerialPort.listDevices;
p = SerialPort(
	serialPortWhereToGet,    //edit to match your port. SerialPort.listDevices
	baudrate: 9600    //check that baudrate is the same as in arduino sketch
);
p.doneAction = {("Serial port" + serialPortWhereToGet + "got closed").postln;};


// make button row
for(0, row - 1, {| i |
	for(0, column - 1, {| j |
		~buts[i, j] = Button.new(w, Rect(butIntervalX * (j + 1),
			butIntervalY * (i + 1), butSize, butSize))
		.states_([["Off"],["On", Color.white, Color.black]]);

		~recButs[i, j] = Button.new(w, Rect(butIntervalX * (j + 1) + butSize,
			butIntervalY * (i + 1), butSize, butSize))
		.states_([["Auto", Color.white, Color.blue],["ing..", Color.white, Color.green]]);

		~recButs[i, j].action = {| but |
			bVal = but.value;
			if(bVal == 1,
				{
					var sum = List.newClear;
					var laced = List.newClear;
					var vhPairs = List.newClear; //value - holdTime pairs

					// mearge value and holdTime
					~holdTimeList[i, j].removeAt(0);

					sum.add(~valueList[i, j]);
					sum.add(~holdTimeList[i, j]);

					// lace to one list
					laced = sum.lace(~valueList.size + ~holdTimeList.size);
					laced.pairsDo({| a, b | vhPairs.add(List.with(a, b)) });

					routine[i, j] = Routine({
						2.do{
						vhPairs.do{| list, idx |
							{
								~slids[i, j].valueAction_(list[0]);
							}.defer;
							("list[0]: " + list[0]).postln;
							("list[1]: " + list[1]).postln;
							list[1].wait;
						}
						}
					});
					SystemClock.play(routine[i, j]);
					// SystemClock.sched(0.0, {|time|
					// 	f.play;
//					});
				},
				{
			});
		};


		bLeft = ~buts[i, j].bounds.left;
		bTop = ~buts[i, j].bounds.top;

		~slids[i, j] = Slider.new(w, Rect(bLeft, bTop - (butSize/2), slidSizeX, slidSizeY));

		~slids[i, j].action = {arg sld;
			idxRow = i; idxColumn = j;
			if(recFlag == true,{
				// Save time interval
				AppClock.sched(0.0,{ arg time;
					~time = ((time*1000).round) / 1000;
					~holdTimeList[i, j].add(~time - ~pTime);
					("holdTime: " + ~holdTimeList[i, j]).postln;
					~pTime = ~time;
					nil; //just do once
				});

				// Save slider value
				~value = sld.value;
				~valueList[i, j].add(~value);
				("value: " + ~valueList[i, j]).postln;
				~pValue = ~value;

				},{
				siVal = sld.value.linlin(0.0, 1.0, 1, 255).asInteger;
				if(siVal != psiVal,{
					p.putAll(Int8Array[i, j, bVal, siVal]);
					(i + "/" + j + "=" + bVal + "/" + siVal).postln; // Print value
					psiVal = siVal;
				});
			});
		};

		~buts[i, j].action = {arg but;
			bVal = but.value;
			if(bVal != pbVal, {
				p.putAll(Int8Array[i, j, bVal, siVal]); // Send serial
				(i + "/" + j + "=" + bVal + "/" + siVal).postln; // Print value
				pbVal = bVal;
			});
		};
    });
});


w.front;

// Record Button
~recBut = Button.new(w, Rect(windowWidth - 100, 0, 50, 50)).states_([["Rec", Color.white, Color.red], ["ing.."]]).action_({| but |
	tVal = but.value;
	if(tVal == 0,{
		// Save last values hold time.
		AppClock.sched(0.0,{ arg time;
			~time = ((time*1000).round) / 1000;
			~holdTimeList[idxRow, idxColumn].add(~time - ~pTime);
//			("holdTime: " + ~holdTimeList[idxRow, idxColumn]).postln;
			nil; //just do once
		});

		recFlag = false;
		("Rec stop.").postln;
	},{
		recFlag = true;
		("Rec start!").postln;
	});
});


// Quit Button
qBut = Button.new(w, Rect(0, 0, 50, 50)).states_([["Quit"], ["Bye"]]).action_({w.close;
	p.close;
});

// Serial Connectioin Test Button
~testBut = Button.new(w, Rect(windowWidth - 50, 0, 50, 50)).states_([["Test", Color.white, Color.black], ["LED?", Color.white, Color.blue]]).action_({| but |
	tVal = but.value;
	if(tVal == 1, {
		if(ptVal != tVal, {
			p.putAll(Int8Array[100, 101, 102, 103]);
			"Test ON code send".postln; // Print value
			ptVal = tVal;
			});
		},{
		if(ptVal != tVal, {
			p.putAll(Int8Array[0, 0, 0, 0]);
			"Test OFF code send".postln; // Print value
			ptVal = tVal;
			});
		}
	);
});

// Serial Receive routine
// r= Routine({
// 	var byte, str, res;
// 	99999.do{|i|
// 		if(p.read == 10, {
// 			str = "";
// 			while({byte = p.read; byte != 13 }, {
// 				str= str++byte.asAscii;
// 			});
// 			res = str.asInteger;
// 			("Teensy said :" + str + "asInteger: " + res).postln;
// 		});
// 	};
// }).play;

//Ending
CmdPeriod.doOnce{

	r.stop;
	w.close;
	p.close;
	SystemClock.clear;
};
)

(//Function
~time = 0;
~getCurrentTime = {SystemClock.sched(0.0,{ arg time;
    time.postln;
	~time = ((time*1000).round) / 1000;
	~time.postln;
	nil; //just do once
});
};
)

~getCurTime.value;

postln(100);
SerialPort.closeAll;
SerialPort.listDevices;

p.isOpen;
p.close;
SerialPort