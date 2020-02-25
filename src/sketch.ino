// Pins
const int led1 = 3; 
const int led2 = 5; 
const int led3 = 6; 
const int led4 = 9; 
const int led5 = 10;
const int button = 2;

// Timer
const int timerMin = 25;
const int shortBreakMin = 5;
const int longBreakMin = 10;
const int longBreakEvery = 4;

// Variables
int buttonState = 0;
int fadeAmount = 5;
int brightness = 0;
int nDone = 0;

void setup() {
  pinMode(led1, OUTPUT);
  Serial.begin(9600);
}

void breathe(int led, int secs, long interval) {
  long msec = 0;
  long previousMillis = 0;
  while (msec < secs*1000L) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      analogWrite(led, brightness);
      brightness = brightness + fadeAmount;

      // reverse the direction of the fading at the ends of the fade:
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
      msec = msec + interval;  // track cumulative time
    }
  }
  analogWrite(led, 255);
}

void allOn() {
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  analogWrite(led3, 255);
  analogWrite(led4, 255);
  analogWrite(led5, 255);
}

void allOff() {
  analogWrite(led1, 0);
  analogWrite(led2, 0);
  analogWrite(led3, 0);
  analogWrite(led4, 0);
  analogWrite(led5, 0);
}

void takeBreak(int bsecs) {
  allOff();
  int secs = bsecs / 5;
  breathe(led5, secs, 15);
  breathe(led4, secs, 15);
  breathe(led3, secs, 15);
  breathe(led2, secs, 15);
  breathe(led1, secs, 15);
  allOff();
}

void waitBreak(int interval) {
  // blink until button press
  long previousMillis = 0;
  int ledState = LOW;
  while (digitalRead(button) == LOW) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      if (ledState == LOW) {
        allOn();
        ledState = HIGH;
      } else {
        allOff();
        ledState = LOW;
      }
    }
  }
}

void breakDone() {
  nDone = nDone + 1;

  // long break every n work sessions
  if (nDone % longBreakEvery == 0) {
    waitBreak(500);
    takeBreak(shortBreakMin * 60);
  } else {
    waitBreak(1500);
    takeBreak(longBreakMin * 60);
  }

  // indicator for how many have been completed
  switch (nDone) {
  case 1:
    analogWrite(led1, 255);
    break;
  case 2:
    analogWrite(led1, 255);
    analogWrite(led2, 255);
    break;
  case 3:
    analogWrite(led1, 255);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
    break;
  case 4:
    analogWrite(led1, 255);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
    analogWrite(led4, 255);
    break;
  case 5:
    analogWrite(led1, 255);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
    analogWrite(led4, 255);
    analogWrite(led5, 255);
    break;
  case 6:
    analogWrite(led1, 255);
    analogWrite(led5, 255);
    break;
  case 7:
    analogWrite(led2, 255);
    break;
  case 8:
    analogWrite(led3, 255);
    break;
  case 9:
    analogWrite(led4, 255);
    break;
  case 10:
    analogWrite(led5, 255);
    break;
  }
}

void work() {
  allOff();
  int sec = (timerMin * 60) / 5;
  breathe(led1, sec, 30);
  breathe(led2, sec, 30);
  breathe(led3, sec, 30);
  breathe(led4, sec, 30);
  breathe(led5, sec, 30);
  allOff();
}

void loop() {
  buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    work();
    breakDone();
  }
}
