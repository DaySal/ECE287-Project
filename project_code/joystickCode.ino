const int VRxPin = A0;
const int VRyPin = A1;
const int SWPin  = 5;

const int Xplus = 13;
const int Xminus = 12;
const int Yplus = 11;
const int Yminus = 10;

int VRx = 0;        // value read from the horizontal pot
int VRy = 0;        // value read from the vertical pot
int SW = 0;         // value read from the switch

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;
int lastButtonState = 500;

void setup() {
  Serial.begin(9600);
  pinMode(SWPin,INPUT_PULLUP);
  pinMode(VRxPin, INPUT);
  pinMode(VRyPin, INPUT);

  pinMode(Xplus, OUTPUT);
  pinMode(Xminus, OUTPUT);
  pinMode(Yplus, OUTPUT);
  pinMode(Yminus, OUTPUT);
}

void loop() {

  VRx = analogRead(VRxPin);
  VRy = analogRead(VRyPin);
  SW = digitalRead(SWPin);

  // If the switch changed, due to noise or pressing:
  if (VRx < lastButtonState -50 | VRx > lastButtonState + 50) {
    // reset the debouncing timer
    lastButtonState = VRx;
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (VRx > 650) {
      digitalWrite(Xplus, HIGH);
      digitalWrite(Xminus, LOW);
    } else if (VRx < 350) {
      digitalWrite(Xminus, HIGH);
      digitalWrite(Xplus, LOW);
    } else {
      digitalWrite(Xminus, LOW);
      digitalWrite(Xplus, LOW);
    }
  
    if (VRy > 650) {
      digitalWrite(Yplus, HIGH);
      digitalWrite(Yminus, LOW);
    } else if (VRy < 350) {
      digitalWrite(Yminus, HIGH);
      digitalWrite(Yplus, LOW);
    } else {
      digitalWrite(Yminus, LOW);
      digitalWrite(Yplus, LOW);
    }
  }
}
