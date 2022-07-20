//  Responds to user input by illuminating a pressed button and sounding a corresponding tone for a specified duration
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
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(OffSwitch) == HIGH) {
    sleep();
  }
  if (digitalRead(greenBtnPin) == LOW) {
    digitalWrite(greenLEDPin, analogRead(potentiometerPin) /4);
    tone(piezoBuzzerPin, 100);
  } else if (digitalRead(redBtnPin) == LOW) {
    digitalWrite(redLEDPin, analogRead(potentiometerPin) /4);
    tone(piezoBuzzerPin, 200);
  } else if (digitalRead(blueBtnPin) == LOW) {
    digitalWrite(blueBtnPin, analogRead(potentiometerPin) /4);
    tone(piezoBuzzerPin, 300);
  } else if (digitalRead(whiteBtnPin) == LOW) {
    digitalWrite(whiteBtnPin, analogRead(potentiometerPin) /4);
    tone(piezoBuzzerPin, 400);
  } else {
    digitalWrite(blueLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    digitalWrite(whiteLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
    noTone(piezoBuzzerPin);
  }
  
}

void sleep() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(redLEDPin,    LOW);
  digitalWrite(whiteLEDPin, LOW);
  digitalWrite(hapticMoterPin, LOW);
  digitalWrite(piezoBuzzerPin, LOW);
  
  while (digitalRead(OffSwitch) == HIGH) {
    delay(1);
  }
  loop();
}


