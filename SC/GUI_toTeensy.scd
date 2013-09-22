/*
Arduino의 SerialMonitor와 함께 사용할 수 없다.
*/

(
var raw = 4;
var column = 8;
var windowWidth = 600;
var windowHeight = 350;
var serialPortWhereToGet = "/dev/tty.usbmodem12341";

// Quit, Test Button
var qBut;
var testBut;

// Buttons
var buts = Array2D.new(raw, column); // 4 raw, 8 column
var butSize = 40;
var butIntervalX = 60;
var butIntervalY = 60;
var bVal = 0;

// Sliders
var slids = Array2D.new(raw, column); // 4 raw, 8 column
var slidSize = 40;
var slidIntervalX = 60;
var slidIntervalY = 10;
var siVal = 0;

~buts = Array2D.new(raw, column); // 4 raw, 8 column
~slids = Array2D.new(raw, column); // 4 raw, 8 column

w = Window.new("GUI Introduction", Rect(0, 500, windowWidth, windowHeight));

// Array2D init with nil
for(0, raw - 1, {| i |
	for(0, column - 1, {| j |
		buts[i, j] = nil;
		slids[i, j] = nil;
	});
});

// Serial setup
//SerialPort.listDevices;
p = SerialPort(
	serialPortWhereToGet,    //edit to match your port. SerialPort.listDevices
	baudrate: 9600    //check that baudrate is the same as in arduino sketch
);
p.doneAction = {("Serial port" + serialPortWhereToGet + "got closed").postln;};


// make button raw
for(0, raw - 1, {| i |
	for(0, column - 1, {| j |
		~buts[i, j] = Button.new(w, Rect(butIntervalX * (j + 1), butIntervalY * (i + 1), butSize, butSize + (slidSize/2))).states_([["Off"],["On", Color.white, Color.black]]);
		~slids[i, j] = Slider.new(~buts[i, j], Rect(0, 0, butSize, butSize/2));

		~slids[i, j].action = {arg sld;
			siVal = sld.value.linlin(0.0, 1.0, 1, 255).asInteger;
			p.putAll(Int8Array[i, j, bVal, siVal]);
			(i + "/" + j + "=" + bVal + "/" + siVal).postln; // Print value
		};

		~buts[i, j].action = {arg but;
			bVal = but.value;
			p.putAll(Int8Array[i, j, bVal, siVal]); // Send serial
			(i + "/" + j + "=" + bVal + "/" + siVal).postln; // Print value
		};
    });
});


w.front;

// Quit Button
qBut = Button.new(w, Rect(0, 0, 50, 50)).states_([["Quit"], ["Bye"]]).action_({w.close; p.close});

// Serial Connectioin Test Button
// testBut = Button.new(w, Rect(windowWidth - 100, 0, 50, 50)).states_([["Test"], ["LED?"]]).action_({| but |
// 	if(but.value == 1,
// 		{p.putAll(Int8Array[100, 101, 102, 103]);
// 			"Test ON code send".postln; // Print value
//
// 		}, // Send specify value to test.
// 		{p.putAll(Int8Array[0, 0, 0, 0]);
// 			"Test OFF code send".postln; // Print value
// 		}
// 	)
// });

// Serial Connectioin Test Button
~testBut = Button.new(w, Rect(windowWidth - 100, 0, 50, 50)).states_([["Test", Color.white, Color.black], ["LED?", Color.white, Color.blue]]).action_({| but |
	if(but.value == 1,
		{p.putAll(Int8Array[100, 101, 102, 103]);
		"Test ON code send".postln; // Print value

		}, // Send specify value to test.
		{p.putAll(Int8Array[0, 0, 0, 0]);
		"Test OFF code send".postln; // Print value
		}
	)
});


r= Routine({
    var byte, str, res;
    99999.do{|i|
        if(p.read == 10, {
            str = "";
            while({byte = p.read; byte != 13 }, {
                str= str++byte.asAscii;
            });
            res = str.asInteger;
            ("Teensy said :" + str + "asInteger: " + res).postln;
        });
    };
}).play;

//Ending
CmdPeriod.doOnce{
	r.stop;
	w.close;
	p.close;
};
)

postln(100);
SerialPort.closeAll;
SerialPort.listDevices;

p.isOpen;
p.close;
SerialPort