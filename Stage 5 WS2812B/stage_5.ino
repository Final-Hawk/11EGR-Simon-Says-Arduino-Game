// Displays a sequence of lights and tones, then checks whether the user repeats the sequence correctly, with
// Correct and Incorrect responses respectively acknowledged by the two animations developed in Stage 4.
//  Responds to user input by illuminating a pressed button and sounding a corresponding tone for a specified duration
// Creates outputs of light and sound.
#include <FastLED.h>

#define NUM_LEDS 13      /* The amount of pixels/leds you have */
#define DATA_PIN 13     /* The pin your data line is connected to */
#define LED_TYPE WS2812B /* I assume you have WS2812B leds, if not just change it to whatever you have */
#define BRIGHTNESS 255   /* Control the brightness of your leds */
#define SATURATION 255   /* Control the saturation of your leds */

CRGB leds[NUM_LEDS];

const int ledBtnCount = 4;

const int greenLEDPin = 9;
const int whiteLEDPin = 10;
const int redLEDPin = 11;
const int blueLEDPin = 6;
const int ledVars[ledBtnCount] = {greenLEDPin, whiteLEDPin, redLEDPin, blueLEDPin};

const int greenBtnPin = 8;
const int whiteBtnPin = 7;
const int redBtnPin = 5;
const int blueBtnPin = 12;
const int btnVars[ledBtnCount] = {greenBtnPin, whiteBtnPin, redBtnPin, blueBtnPin};

const int hapticMoterPin = 3;
const int piezoBuzzerPin = 4;
const int OffSwitch = 2;
const int potentiometerPin = A5;

// Game variables
int sequenceSize = 3;
const int maxSequenceSize = 8;
int correctSequence[maxSequenceSize];
bool gameFailed = false;
bool waitForInput = true; // game is in a state waiting for the user to click a button
int fadeLEDBright;

void setup() {
  // LED Outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(whiteLEDPin, OUTPUT);
  // button inputs
  pinMode(greenBtnPin, INPUT_PULLUP);
  pinMode(whiteBtnPin, INPUT_PULLUP);
  pinMode(redBtnPin, INPUT_PULLUP);
  pinMode(blueBtnPin, INPUT_PULLUP);
  // Haptic Motor
  pinMode(hapticMoterPin, OUTPUT);
  // Piezo Buzzer
  pinMode(piezoBuzzerPin, OUTPUT);
  // On/Off Switch
  pinMode(OffSwitch, INPUT_PULLUP);
  pinMode(potentiometerPin, INPUT);

  randomSeed(millis());
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    if (digitalRead(OffSwitch) == HIGH) {
        sleep();
    }
    for (int j = 0; j < 500; j++) {
        for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i - (j * 0.5), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */ 
        }
        FastLED.show();
        
      
        for (int i = 0; i < ledBtnCount; i++) {
        if (digitalRead(btnVars[i]) == LOW) {
            FastLED.clear();
            FastLED.show();
            digitalWrite(ledVars[i], HIGH);
            while (digitalRead(btnVars[i]) == LOW){
                delay(100);
            }
            for (int i = 0; i < ledBtnCount; i++) {
                digitalWrite(ledVars[i], LOW);
            }
            generate_sequence();
        }
        }  /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
    }
    fadeLEDBright = 128+127*cos(2*PI/2000*millis());
    analogWrite(greenLEDPin, fadeLEDBright);

    
}
 
void generate_sequence() {
    sequenceSize += 1;
    for (int i = 0; i < sequenceSize; i++) {
        correctSequence[i] = random(0, ledBtnCount);
    }
    display_sequence();
}
void display_sequence() {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(blueLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(whiteLEDPin, LOW);
    tone(piezoBuzzerPin, 500, 100);
    delay(200);
    tone(piezoBuzzerPin, 500, 100);
    delay(1000);
    for (int i = 0; i < sequenceSize; i++) {
        digitalWrite(ledVars[correctSequence[i]], HIGH);
        delay(analogRead(potentiometerPin));
        for (int bright = 255; bright >= 0; bright--) {
            analogWrite(ledVars[correctSequence[i]], bright);
            delay(1);
        }
        delay(500);
    }
    tone(piezoBuzzerPin, 500, 200);
    input_sequence();
}

void input_sequence() {
    Serial.println("input mode");
    gameFailed = false;
    for (int level = 0; level < sequenceSize && gameFailed == false; level++) {
        waitForInput = true;
        while (waitForInput == true && gameFailed == false) {
            for (int i = 0; i < ledBtnCount; i++) {
                if (digitalRead(btnVars[i]) == LOW) {
                    digitalWrite(ledVars[i], HIGH);
                    if (correctSequence[level] == i){
                        waitForInput = false;
                        tone(piezoBuzzerPin, 100, 50);
                        while (digitalRead(btnVars[i]) == LOW){
                            delay(50);
                        }
                        digitalWrite(ledVars[i], LOW);
                    } else {
                        digitalWrite(ledVars[correctSequence[level]], HIGH);
                        while (digitalRead(btnVars[i]) == LOW){
                            delay(100);
                        }
                        gameFailed = true;
                        digitalWrite(ledVars[i], LOW);
                    }
                } 
            }
        }
    }
    if (gameFailed == false) {
        success();
    } else {
      failure();
    }
}

void success() {
    digitalWrite (hapticMoterPin, LOW);   
    if (sequenceSize < maxSequenceSize) {
        digitalWrite (hapticMoterPin, HIGH);
        tone(piezoBuzzerPin, 400, 200);
        delay(200);
        digitalWrite (hapticMoterPin, LOW);
        generate_sequence();
    } else {
        digitalWrite(greenLEDPin, HIGH);
        digitalWrite(whiteLEDPin, HIGH);
        digitalWrite(blueLEDPin, HIGH);
        digitalWrite (hapticMoterPin, HIGH);
        tone(piezoBuzzerPin, 400, 200);
        delay(200);
        analogWrite(hapticMoterPin, 50);
        analogWrite(greenLEDPin, 50);
        delay(100);
        tone(piezoBuzzerPin, 500, 100);
        digitalWrite (hapticMoterPin, HIGH);
        delay(150);
        tone(piezoBuzzerPin, 650, 100);
        delay(150);
        tone(piezoBuzzerPin, 650, 200);
        delay(150);
        tone(piezoBuzzerPin, 650, 200);
        digitalWrite(redLEDPin, LOW);
        digitalWrite (hapticMoterPin, LOW);   
        sequenceSize = 3;
    }
}
void failure() {

    for (int i = 4; i >= 0; i--)  {
        digitalWrite(redLEDPin, HIGH);
        digitalWrite (hapticMoterPin, HIGH);
        tone(piezoBuzzerPin, 200, 200);
        delay(200);
        analogWrite(hapticMoterPin, 50);
        analogWrite(redLEDPin, 50);
        delay(100);
        digitalWrite (hapticMoterPin, HIGH);
    }
    sequenceSize = 3;
    sleep();
}

void sleep() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(redLEDPin,    LOW);
  digitalWrite(whiteLEDPin, LOW);
  digitalWrite(hapticMoterPin, LOW);
  digitalWrite(piezoBuzzerPin, LOW);
  randomSeed(millis());
  while (digitalRead(OffSwitch) == HIGH) {
    delay(1);
  }
  loop();
}
