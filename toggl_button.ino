/*
  Toggl Button

You can control Toggl timetracker.

1. Set toggl api key on file api_key.txt
2. Start Toggl timer, with description and project.
3. Hold down learn button so long if both leds are on
4. If project is learned and running then red led is on
5. Push touch button stop timer and green led going on
6. Push again toutch button and red led going on

If you start/stop timer on website then leds switches less than 10 seconds to right state
Device switched only last learned project. So if you want start switching new project just start it on web and press learn button.
If no internet connection, then both leds are off


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
long interval = 10000;         // interval at which to check toggl status (milliseconds)
long learnButtonHold = 1000;
long capaciveSensity = 100;

HttpClient client;
CapacitiveSensor cs = CapacitiveSensor(capaciveSendPin,capaciveRecPin);

void setup() {
  Serial.begin(9600);   // Initialize the Serial for debugging
  Bridge.begin();	// Initialize the Bridge
  // initialize the LED pin as an output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(learnButtonPin, INPUT);
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
	//Serial.println("CAP:" + cap);
	if (buttonState == HIGH ){
	  // make REST calls to toggl API
	  if (currentLedState == 1){
		togglStop();
	  }else if (currentLedState == 2){
		togglStart();
	  }
	  
	  delay(10);
	  } else {
		//Serial.println("BUTTON RELEASE");
	  }
  }
  lastButtonState = buttonState;
  // make toggl chech request
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    //Serial.println(currentLedState);
    togglCheck();
  } 
}

void togglCheck() {
  String command = "python /root/toggl_button/check.py";
  int result = getResult(command);
  switchLed(result);
  if (result == 5){
    togglLearn();
  }
}

void togglStart() {
  switchLed(1);
  String command = "python /root/toggl_button/start.py";
  int result = getResult(command);
  switchLed(result);
}

void togglStop() {
  switchLed(2)
  String command = "python /root/toggl_button/stop.py";
  int result = getResult(command);
  switchLed(result);
}

void togglLearn() {
  switchLed(5);
  String command = "python /root/toggl_button/learn.py";
  int result = getResult(command);
  switchLed(result);
}

int getResult(String command){
  int result = 0;	
  Process p;
	Serial.println(command);
	p.runShellCommand(command);
        while (p.running());
	  while (p.available() > 0) {
		char c = p.read();
                if (isDigit(c)){
                  result = (result * 10) + (c - '0');
                }
	  }
 return result;
}

void switchLed(int ledState) {
  Serial.println(ledState);
  if (ledState == 1) {
	// time running
	digitalWrite(redPin, HIGH);
	digitalWrite(greenPin, LOW);
  } else if (ledState == 2) {
	// time stopping
	digitalWrite(redPin, LOW);
	digitalWrite(greenPin, HIGH);
  } else if (ledState == 5) {
	// learn
	digitalWrite(redPin, HIGH);
	digitalWrite(greenPin, HIGH);
  } else if (ledState == 0) {
	// no connection
	digitalWrite(redPin, LOW);
	digitalWrite(greenPin, LOW);
  }
  currentLedState = ledState;
}
