const int led1 = 3; 
const int led2 = 5; 
const int led3 = 6; 
const int led4 = 9; 
const int led5 = 10;
const int button = 2;
const int timerMin = 25;  // How long should the timer run for
const int timerSec = (timerMin * 60) / 5;

int buttonState = 0;
int fadeAmount = 5;
int brightness = 0;
int nDone = 0;

void setup() {
  pinMode(led1, OUTPUT);
  Serial.begin(9600);
}

void breathe(int led) {
  long msec = 0;
  while (msec < timerSec*1000L) {
    analogWrite(led, brightness);
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    msec = msec + 30;
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

void done() {
  nDone = nDone + 1;
  for (int i = 0; i <= 5; i++) {
    allOn();
    delay(200);
    allOff();
    delay(200);
  }
  switch (nDone) {
  case 1:
    analogWrite(led1, 0);
  case 2:
    analogWrite(led1, 0);
    analogWrite(led2, 0);
  case 3:
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
  case 4:
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
  case 5:
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
    analogWrite(led5, 0);
  }
}

void loop() {
  buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    breathe(led1);
    breathe(led2);
    breathe(led3);
    breathe(led4);
    breathe(led5);
    done();
  }
}
