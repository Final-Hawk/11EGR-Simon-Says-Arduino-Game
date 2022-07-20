// Creates outputs of light and sound.
const int greenLEDPin = 9;
const int whiteLEDPin = 10;
const int redLEDPin = 11;
const int blueLEDPin = 6;

const int greenBtnPin = 8;
const int whiteBtnPin = 7;
const int redBtnPin = 5;
const int blueBtnPin = 12;

const int hapticMoterPin = 3;
const int piezoBuzzerPin = 4;
const int OffSwitch = 2;
const int potentiometerPin = A5;

void setup() {
  // LED Outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(whiteLEDPin, OUTPUT);
  // button inputs
  pinMode(greenBtnPin, INPUT);
  pinMode(whiteBtnPin, INPUT);
  pinMode(redBtnPin, INPUT);
  pinMode(blueBtnPin, INPUT);

  // Haptic Motor
  pinMode(hapticMoterPin, OUTPUT);
  // Piezo Buzzer
  pinMode(piezoBuzzerPin, OUTPUT);
  // On/Off Switch
  pinMode(OffSwitch, INPUT_PULLUP);
  pinMode(potentiometerPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(OffSwitch) == HIGH) {
    sleep();
  }
  sequence();
}

void sequence() {
 
   // light greenLEDPin, redLEDPin, blueLEDPin, whiteLEDPin in sequence every second using millis
    if (digitalRead(OffSwitch) == HIGH) {
      sleep();
    }
    if (millis() % 2000 >= 0 && millis() % 2000 < 500) {
      // set minimum brightness of greenLEDPin to 5
      if (analogRead(potentiometerPin) /4 < 5) {
        analogWrite(greenLEDPin, 5);
      } else {
        analogWrite(greenLEDPin, analogRead(potentiometerPin) /4);
      }
      digitalWrite(redLEDPin, LOW);
      digitalWrite(blueLEDPin, LOW);
      digitalWrite(whiteLEDPin, LOW);
    } else if (millis() % 2000 >= 500 && millis() % 2000 < 1000) {
      digitalWrite(greenLEDPin, LOW);
      // set minimum brightness of redLEDPin to 5
      if (analogRead(potentiometerPin) < 5) {
        analogWrite(redLEDPin, 5);
      } else {
        analogWrite(redLEDPin, analogRead(potentiometerPin) /4);
      }
      digitalWrite(blueLEDPin, LOW);
      digitalWrite(whiteLEDPin, LOW);
    } else if (millis() % 2000 >= 1000 && millis() % 2000 < 1500) {
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(redLEDPin, LOW);
      // set minimum brightness of blueLEDPin to 5
      if (analogRead(potentiometerPin) /4 < 5) {
        analogWrite(blueLEDPin, 5);
      } else {
        analogWrite(blueLEDPin, analogRead(potentiometerPin) /4);
      }
      digitalWrite(whiteLEDPin, LOW);
    } else if (millis() % 2000 >= 1500 && millis() % 2000 < 2000) {
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(redLEDPin, LOW);
      digitalWrite(blueLEDPin, LOW);
      // set minimum brightness of whiteLEDPin to 5
      if (analogRead(potentiometerPin) /4 < 5) {
        analogWrite(whiteLEDPin, 5);
      } else {
        analogWrite(whiteLEDPin, analogRead(potentiometerPin) /4);
      }
    }
}


void sleep() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(whiteLEDPin, LOW);
  digitalWrite(hapticMoterPin, LOW);
  digitalWrite(piezoBuzzerPin, LOW);

  while (digitalRead(OffSwitch) == HIGH) {
    delay(1);
  }
  loop();
}


