// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "IoTTimer.h"
#include "wemo.h"
#include "Encoder.h"
#include "Button.h"

SYSTEM_MODE(MANUAL); //control logging into classroom router
//SYSTEM_THREAD(ENABLED); Caution - will allow code to execute before fully connected

// hue and wemo arrays
int myBulbs[] = {1,2,3,4,5}; 
int myWemos[] = {0,1,2,3,4};
int color;

const int SIZE = 12;
const int RANDSEED = A0;
int numbers[SIZE];  // Array to hold numbers 1-12
int myIndex;  // Tracks the current number in the shuffled list

// Encoder setttings
const int PINA=D8;
const int PINB=D9;
const int ONOFF=D4;
const int LEDRED=D11;
const int LEDGRN=D12;
const int LEDBLU=D13;
const int LEDSW=D14;

int ledSet=0;
int position=0;
int lastPosition=0;

int prevButtonState=0;
int buttonState;
int redLedState;
int grnLedState;
int bulbSet=0;
int wemoSet=0;

int numWemos=5;
bool bulbon;

int theRandNum;
int theWemo;
int theHue;

Encoder myEnc(PINA,PINB);
IoTTimer timer;
Button encButton(LEDSW);
Button yelPushButton(ONOFF);

void shuffleNumbers();

void setup() {
  // wait forr Serial Monitor
  Serial.begin(9600);
  waitFor(Serial.isConnected, 10000); 

  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  delay(1000);
  for(int i = 0; i < numWemos; i++){
    delay(1000);
    wemoWrite(myWemos[i],LOW);
    Serial.printf("Turning off wemo: %i\nwemoSet = %i\n", i, wemoSet);
  }

  // can't use because all anaolg as being used
  pinMode(A0, INPUT);
  randomSeed(analogRead(RANDSEED));  // Seed the random function using an analog pin
  shuffleNumbers();  // Initialize the shuffled numbers sequence
  if (myIndex < SIZE) {
    Serial.printf("Random Number: %d\n", numbers[myIndex]);
    myIndex++;

    // Simulate an interval (e.g., every 2 seconds)
    delay(2000);
  } 
  else {
      Serial.printf("All numbers used. Reshuffling...\n");
      shuffleNumbers();
  }

}

void loop() {
    //  Using the encoder button to turn on/off wemos
    if(encButton.isClicked()) {
      Serial.printf("\n\nmyIndex = %i\n", myIndex);
      theRandNum = numbers[myIndex];  // setting the random number to an easy to use variable
      Serial.printf("Button pressed\n");
      Serial.printf("theRandNum: %d\n", theRandNum);
      myIndex++;

      // Condition statements to determine which wemo and hue to light up

      // Stephanie & Sterling
      if(theRandNum > 0 && theRandNum < 3)
      {
        theWemo = 0;
        theHue = 1;

        Serial.printf("Stephanine & Sterling\n");
        wemoWrite(theWemo,HIGH);
        Serial.printf("Wemo %i on\n",theWemo);
        setHue(theHue,true,HueRed,random(32,255),255);
        Serial.printf("Hue %i on\n",theHue);
        delay(3000);
        wemoWrite(theWemo,LOW);
        Serial.printf("Wemo %i off\n",theWemo);
        setHue(theHue,false,HueRed,random(32,255),255);
        Serial.printf("Hue %i off\n",theHue);
      }
      
      // Will & Adrian
      if(theRandNum >= 3 && theRandNum <= 4)
      {
        theWemo = 1;
        theHue = 2;

        Serial.printf("Will & Adrian\n");
        wemoWrite(theWemo,HIGH);
        Serial.printf("Wemo %i on\n",theWemo);
        setHue(theHue,true,HueRed,random(32,255),255);
        Serial.printf("Hue %i on\n",theHue);
        delay(3000);
        wemoWrite(theWemo,LOW);
        Serial.printf("Wemo %i off\n",theWemo);
        setHue(theHue,false,HueRed,random(32,255),255);
        Serial.printf("Hue %i off\n",theHue);
      }

      // Dillon, Victor, Efrain
      if(theRandNum > 4 && theRandNum <= 7)
      {
        theWemo = 3;
        theHue = 4;

        Serial.printf("Dillon, Victor, Efrain\n");
        wemoWrite(theWemo,HIGH);
        Serial.printf("Wemo %i on\n",theWemo);
        setHue(theHue,true,HueRed,random(32,255),255);
        Serial.printf("Hue %i on\n",theHue);
        delay(3000);
        wemoWrite(theWemo,LOW);
        Serial.printf("Wemo %i off\n",theWemo);
        setHue(theHue,false,HueRed,random(32,255),255);
        Serial.printf("Hue %i off\n",theHue);
      }

      // Jason & Marlon
      if(theRandNum > 7 && theRandNum <=9)
      {
        theWemo = 4;
        theHue = 5;

        Serial.printf("Jason & Marlon\n");
        wemoWrite(theWemo,HIGH);
        Serial.printf("Wemo %i on\n",theWemo);
        setHue(theHue,true,HueRed,random(32,255),255);
        Serial.printf("Hue %i on\n",theHue);
        delay(3000);
        wemoWrite(theWemo,LOW);
        Serial.printf("Wemo %i off\n",theWemo);
        setHue(theHue,false,HueRed,random(32,255),255);
        Serial.printf("Hue %i off\n",theHue);
      }

      // Ben, Ahmad, Sofia
      if(theRandNum > 9 && theRandNum <= 12)
      {
        theWemo = 4;
        theHue = 5;

        Serial.printf("Ben, Ahmad, Sofia\n");
        wemoWrite(theWemo,HIGH);
        Serial.printf("Wemo %i on\n",theWemo);
        setHue(theHue,true,HueRed,random(32,255),255);
        Serial.printf("Hue %i on\n",theHue);
        delay(3000);
        wemoWrite(theWemo,LOW);
        Serial.printf("Wemo %i off\n",theWemo);
        setHue(theHue,false,HueRed,random(32,255),255);
        Serial.printf("Hue %i off\n",theHue);
      }
    }
}

void shuffleNumbers() {
    // Fill the array with numbers from 1 to 12
    for (int i = 0; i < SIZE; i++) {
        numbers[i] = i + 1;
        // Serial.printf("Numbers: %i\n", numbers[i]);
    }

    // Shuffle the array using Fisher-Yates algorithm
    for (int i = SIZE - 1; i > 0; i--) {
        int j = random(i + 1);  // Generate random index
        // Swap numbers[i] and numbers[j]
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
        Serial.printf("Numbers: %i\n", numbers[i]);
    }
    
    myIndex = 0;  // Reset index after shuffling
}