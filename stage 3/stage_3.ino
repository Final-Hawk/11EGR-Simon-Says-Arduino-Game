// Reads a potentiometer setting to switch the illumination of zero, one, two, three or four lights and/or tonal frequencies

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
int potGreen, potRed, potBlue, potWhite, potVibrate;
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
    potGreen = analogRead(potentiometerPin);
    potRed = analogRead(potentiometerPin) - 255;
    potBlue = analogRead(potentiometerPin) - 510;
    potWhite = analogRead(potentiometerPin) - 765;

    if (potGreen > 255) {
        potGreen = 255;
    } else if (potGreen < 0) {
        potGreen = 0;
    }
    if (potRed > 255) {
        potRed = 255;
    } else if (potRed < 0) {
        potRed = 0;
    }
    if (potBlue > 255) {
        potBlue = 255;
    } else if (potBlue < 0) {
        potBlue = 0;
    }
    if (potWhite > 255) {
        potWhite = 255;
    } else if (potWhite < 0) {
        potWhite = 0;
    }
    analogWrite(greenLEDPin, potGreen);
    analogWrite(redLEDPin, potRed);
    analogWrite(blueLEDPin, potBlue);
    analogWrite(whiteLEDPin, potWhite);    
    analogWrite(hapticMoterPin, potWhite);  
}

void sleep() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(redLEDPin,    LOW);
  digitalWrite(whiteLEDPin, LOW);
  digitalWrite(hapticMoterPin, LOW);
  while (digitalRead(OffSwitch) == HIGH) {
    delay(1);
  }
  loop();
}


