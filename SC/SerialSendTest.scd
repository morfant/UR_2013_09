/*

Arduino의 SerialMonitor와 함께 사용할 수 없다.


*/

(

p = SerialPort(
    "/dev/tty.usbmodem12341",    //edit to match your port. SerialPort.listDevices
    baudrate: 9600
    );

//send serial data - slow pulsating

r= Routine({
    inf.do{|i|
		p.put(i%100);
		(i%100).postln;
		0.05.wait;
    };
}).play;


CmdPeriod.doOnce{r.stop; p.close;};
)


SerialPort.closeAll;