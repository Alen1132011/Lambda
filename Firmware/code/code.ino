
const int switch1Pin = 12;
const int switch2Pin = 44;
const int switch3Pin = 43;

const int encoderAPin = 10;
const int encoderBPin = 11;

const int buzzerPin = 13;

const int touchPins[] = {1, 2, 3, 6, 7, 8, 9};
const char* touchNames[] = {
  "TOUCH1", "TOUCH2", "TOUCH3", "TOUCH6",
  "TOUCH7", "TOUCH4", "TOUCH5"
};

int lastEncoderA = HIGH;
int lastSwitch1 = HIGH;
int lastSwitch2 = HIGH;
int lastSwitch3 = HIGH;

unsigned long lastTouchCheck = 0;
unsigned long lastPrintTime = 0;

int touchThreshold = 30;

void setup() {
  Serial.begin(115200);

  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);
  pinMode(switch3Pin, INPUT_PULLUP);

  pinMode(encoderAPin, INPUT_PULLUP);
  pinMode(encoderBPin, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

  lastEncoderA = digitalRead(encoderAPin);

  Serial.println();
  Serial.println("========================");
  Serial.println("    LAMBDA CONTROLLER");
  Serial.println("========================");
  Serial.println("System started!");
  Serial.println("Testing all components...");

  tone(buzzerPin, 1000, 200);
}

void loop() {
  testSwitches();
  testEncoder();
  testTouch();
}

void testSwitches() {
  int switch1State = digitalRead(switch1Pin);
  int switch2State = digitalRead(switch2Pin);
  int switch3State = digitalRead(switch3Pin);

  if (switch1State != lastSwitch1) {
    if (switch1State == LOW) {
      Serial.println("Switch 1 pressed");
      tone(buzzerPin, 1000, 100);
    }
    lastSwitch1 = switch1State;
  }

  if (switch2State != lastSwitch2) {
    if (switch2State == LOW) {
      Serial.println("Switch 2 pressed");
      tone(buzzerPin, 1200, 100);
    }
    lastSwitch2 = switch2State;
  }

  if (switch3State != lastSwitch3) {
    if (switch3State == LOW) {
      Serial.println("Switch 3 pressed");
      tone(buzzerPin, 1500, 100);
    }
    lastSwitch3 = switch3State;
  }
}

void testEncoder() {
  int encoderA = digitalRead(encoderAPin);
  int encoderB = digitalRead(encoderBPin);

  if (encoderA != lastEncoderA) {
    if (encoderA == LOW) {
      if (encoderB == HIGH) {
        Serial.println("Encoder: Clockwise");
      } else {
        Serial.println("Encoder: Counterclockwise");
      }
    }
    lastEncoderA = encoderA;
  }
}

void testTouch() {
  if (millis() - lastTouchCheck < 100) {
    return;
  }

  lastTouchCheck = millis();

  for (int i = 0; i < 7; i++) {
    int touchValue = touchRead(touchPins[i]);

    if (touchValue < touchThreshold) {
      Serial.print(touchNames[i]);
      Serial.print(" detected! Value: ");
      Serial.println(touchValue);
    }
  }
}
