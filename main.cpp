#include <Arduino.h>
#include <SoftwareSerial.h>

int leftListen = 6;
int rightListen = 10;
int leftAttention = 7;
int rightAttention = 11;
SoftwareSerial left (4, 5);
SoftwareSerial right (8, 9);
String RI;
String LI;
String userIn;


void setup() {
	pinMode(leftListen, INPUT);
	pinMode(rightListen, INPUT);
	pinMode(leftAttention, OUTPUT);
	pinMode(rightAttention, OUTPUT);
	Serial.begin(9600);
	while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  	}
	left.begin(9600);
	right.begin(9600);
}

void sendLeft(String message) {
	digitalWrite(leftAttention, HIGH);
	delay(10);
	left.print(message);
	digitalWrite(leftAttention, LOW);
}

void sendRight(String message) {
	digitalWrite(rightAttention, HIGH);
	delay(10);
	right.print(message);
	digitalWrite(rightAttention, LOW);
}

void loop() {
	if (Serial.available() > 0) {
		userIn = Serial.readString();
		Serial.print("Serial ");
		Serial.println(userIn);
		sendLeft(userIn);
		sendRight(userIn);
	}
	if(digitalRead(leftListen)) {
		left.listen();
		if (left.available() > 0) {
			LI = left.readString();
			Serial.print("LI ");
			Serial.println(LI);
			sendRight(LI);
		}
	}
	if(digitalRead(rightListen)) {
		right.listen();
		if (right.available() > 0) {
			RI = right.readString();
			Serial.print("RI ");
			Serial.println(RI);
			sendLeft(RI);
		}
	}
}