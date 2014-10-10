/*
  Toggl tButton

Creates Toggl timetracker event if putton pressed.

 The circuit:
 * LEDs anode attached to ground
 * LEDs cahtode attached läbi 200 ohm resistor to arduino pin 11 and 6 
 * Learn pushbutton attached to pin 12 from +5V
 * 10K resistor attached to pin 12 from ground
 * Capacive sensor wire is attached to pin 5
 * Capacive sensor resistor 1M is attached to pin 5 and 9

 created 2014
 by Arvi Võime <http://>

*/

#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>

// get library from http://playground.arduino.cc/Main/CapacitiveSensor
#include <CapacitiveSensor.h>


// constants won't change. They're used here to
// set pin numbers:
const int learnButtonPin = 12;     // the number of the pushbutton pin
const int capaciveSendPin = 9;
const int capaciveRecPin = 5;

const int redPin =  11;       // the number of the RED LED pin
const int greenPin = 6;       // the number of the GREEN LED pin


// variables will change:
int currentLedState = 0;      // variable to led status
int lastButtonState = 0;      // vairable for button last status
long previousMillis = 0;      // will store last time LED was updated
long interval = 5000;         // interval at which to check toggl status (milliseconds)
long learnButtonHold = 1000;
long capaciveSensity = 100;
int debuging = 1;

HttpClient client;                                                      // define http client connection
CapacitiveSensor cs = CapacitiveSensor(capaciveSendPin,capaciveRecPin);

void setup() {
  Serial.begin(9600);   // Initialize the Serial for debugging
  Bridge.begin();	// Initialize the Bridge
  // initialize the LED pin as an output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(learnButtonPin, INPUT);
//  togglCurrent(); // get current values
//getParameters();
}

void loop() {
  unsigned long currentMillis = millis();
  // read the state of the pushbutton value:
  //int buttonState = digitalRead(buttonPin);

  int learnButtonState = digitalRead(learnButtonPin);
  if (learnButtonState == HIGH){
    delay(learnButtonHold);
      int learnButtonStateRepeat = digitalRead(learnButtonPin);
      if (learnButtonStateRepeat == HIGH){
        togglLearn();
      }
  } 


  int buttonState;
  long cap =  cs.capacitiveSensor(30);

  if (cap > capaciveSensity){
	buttonState = 1;
  }else{
	buttonState = 0;
  }
  if (buttonState != lastButtonState){
	Serial.println("CAP:" + cap);
	if (buttonState == HIGH ){
	  Serial.println("BUTTON PRESS");
	  // muuda praegune staatus vastupidiseks
	  //currentLedState = !currentLedState;
	  // muuda ära led
  //    switchLed ( currentLedState );
	  
	  // make REST calls to toggl API
	  if (currentLedState == 0){
		togglStart();
	  }else{
		togglStop();
	  }
	  
	  delay(10);
	  } else {
		Serial.println("BUTTON RELEASE");
	  }
  }
  lastButtonState = buttonState;
  // make toggl chech request
  if(currentMillis - previousMillis > interval) {
	// save the last time
	previousMillis = currentMillis;
	//togglCurrent();
  } 
}

void togglCurrent() {
  Process p;
  String command = "python /root/toggl_button/check.py";
  Serial.println(command);
  p.runShellCommand(command);
   
	String json = "";    
	while (p.available()>0) {
	  char c = p.read();
	  json += String(c);
	  //Serial.print(c);
	}

	//Serial.flush();
	json.trim();
	Serial.println(json);    
	
	String togglState = json;

	long cap =  cs.capacitiveSensor(30);

	Serial.println("TOGGL:"+String(togglState));
	Serial.println("LED:"+String(currentLedState));
	Serial.println("CAP:"+String(cap));
  
  // if (togglState != currentLedState){
	 //  Serial.println("TOGGL STATE CHANGED");
	 //  // muuda praegune staatus toggleks
	 //  currentLedState = togglState;
	 //  // muuda ära led
	 //  switchLed(currentLedState);
	 //  delay(10);
  // }
}

void togglStart() {
  Process p;

  String command = "python /root/toggl_button/start.py";

  Serial.println(command);
  p.runShellCommand(command);
  
  // empty old tid value
  String json="";
	while (p.available()>0) {
	  char c = p.read();
	  json += c;
	//  Serial.print(c);
	}

	Serial.flush();
	json.trim(); // remove spaces and newlines
	Serial.println(json);

}

void togglStop() {
	Process p;
	String command = "python /root/toggl_button/stop.py";
	Serial.println(command);
	p.runShellCommand(command);
	  while (p.available()>0) {
		char c = p.read();
		Serial.print(c);
	  }
	  Serial.flush();
  }

void togglLearn() {
	Process p;
	String command = "python /root/toggl_button/learn.py";
	Serial.println(command);
	p.runShellCommand(command);
	  while (p.available()>0) {
		char c = p.read();
		Serial.print(c);
	  }
	  Serial.flush();
}

void httpTest(){
  // Make a HTTP request:
  client.get("http://arduino.cc/asciilogo.txt");
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
	char c = client.read();
	Serial.print(c);
  }
  Serial.flush();
  delay(5000);
}

void switchLed(int ledState) {
  if (ledState == HIGH) {
	// turn LED on:
	digitalWrite(redPin, HIGH);
	digitalWrite(greenPin, LOW);
  } else {
	// turn LED off:
	digitalWrite(redPin, LOW);
	digitalWrite(greenPin, HIGH);
  }
  currentLedState = ledState;
}
