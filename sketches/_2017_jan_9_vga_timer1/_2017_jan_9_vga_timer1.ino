const int vSyncPin = 15;
const int hSyncPin = 17;

const int red = 1;
const int green = 2;
const int blue = 3;

IntervalTimer vgaTimer;

void setup() {  
  pinMode(vSyncPin, OUTPUT);
  pinMode(hSyncPin, OUTPUT);

  pinMode(red, OUTPUT);

  vgaTimer.begin(drawVGA, 31);
  vgaTimer.priority(0);
}

volatile unsigned long vSyncCount = 0;
void drawVGA() {
  
  if (vSyncCount < 2) {
    digitalWrite(vSyncPin, LOW);
  } else {
    digitalWrite(vSyncPin, HIGH);
  }

  digitalWrite(hSyncPin, LOW);
  digitalWrite(hSyncPin, HIGH);

  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(red, LOW);
  
  vSyncCount += 1;

  if (vSyncCount > 538) {
    vSyncCount = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
