#include <Arduino.h>
#include <SoftwareSerial.h>

int leftListen = 7;
int rightListen = 10;
SoftwareSerial left (5, 6);
SoftwareSerial right (8, 9);
String RI;
String LI;
String userIn;


void setup() {
	pinMode(leftListen, INPUT);
	pinMode(rightListen, INPUT);
	Serial.begin(9600);
	while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  	}
	left.begin(9600);
	right.begin(9600);
}


void loop() {
	if (Serial.available() > 0) {
		userIn = Serial.readString();
		Serial.print("Serial ");
		Serial.println(userIn);
		left.print(userIn);
		right.print(userIn);
	}
	if(digitalRead(leftListen)) {
		left.listen();
		if (left.available() > 0) {
			LI = left.readString();
			Serial.print("LI ");
			Serial.println(LI);
		}
	}
	if(digitalRead(rightListen)) {
		right.listen();
		if (right.available() > 0) {
			RI = right.readString();
			Serial.print("RI ");
			Serial.println(RI);
		}
	}
}