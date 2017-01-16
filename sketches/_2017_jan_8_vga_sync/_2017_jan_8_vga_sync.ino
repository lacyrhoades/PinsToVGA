#include <IntervalTimer.h>

const int led = 13;

const int vSync = 23;
const int hSync = 22;

const int red = 1;
const int green = 2;
const int blue = 3;

IntervalTimer vTimer;

void setup() {
  pinMode(led, OUTPUT);

  pinMode(vSync, OUTPUT);
  pinMode(hSync, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  vTimer.begin(vCallback, 4);

  digitalWrite(blue, HIGH);
  digitalWrite(led, HIGH);
}

volatile unsigned short vLines = 0;
volatile unsigned short hLines = 0;

void vCallback() {
  if (vLines < 16) {
    digitalWrite(vSync, HIGH);
  } else {
    digitalWrite(vSync, LOW);
  }

  if (hLines == 1) {
    digitalWrite(hSync, HIGH);
  } else {
    digitalWrite(hSync, LOW);
  }

  vLines += 1;
  hLines += 1;

  if (vLines > 4199) {
    vLines = 0;
  }

  if (hLines > 7) {
    hLines = 0;
  }
}

void loop() {
}


