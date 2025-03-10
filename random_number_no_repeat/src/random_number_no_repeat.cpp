// Include Particle Device OS APIs
#include "Particle.h"

const int SIZE = 12;
const int RANDSEED = A0;
int numbers[SIZE];  // Array to hold numbers 1-12
int myIndex=0;  // Tracks the current number in the shuffled list

// Encoder setttings
const int PINA=D8;
const int PINB=D9;
const int ONOFF=D4;
const int LEDRED=D11;
const int LEDGRN=D12;
const int LEDBLU=D13;
const int LEDSW=D14;

void shuffleNumbers();

void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected, 10000); // wait forr Serial Monitor

    // can't use because all anaolg as being used
    pinMode(A0, INPUT);
    randomSeed(analogRead(RANDSEED));  // Seed the random function using an analog pin
    shuffleNumbers();  // Initialize the shuffled numbers sequence
}

void loop() {
    if (myIndex < SIZE) {
        Serial.printf("Random Number: %d\n", numbers[myIndex]);
        myIndex++;

        // Simulate an interval (e.g., every 2 seconds)
        delay(2000);
    } else {
        Serial.printf("All numbers used. Reshuffling...\n");
        shuffleNumbers();
    }
    // Serial.printf("Numbers: %i\n", numbers[myIndex]);
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