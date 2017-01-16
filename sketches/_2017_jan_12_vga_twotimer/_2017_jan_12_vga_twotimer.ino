const int led = 13;

const int vSyncPin = 16;
const int hSyncPin = 17;

const int red = 9;
const int green = 2;
const int blue = 3;

IntervalTimer vgaSyncTimer;
IntervalTimer vgaDrawTimer;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  pinMode(vSyncPin, OUTPUT);
  pinMode(hSyncPin, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  vgaSyncTimer.begin(syncVGA, 31);
  vgaSyncTimer.priority(8);

  vgaDrawTimer.begin(drawVGA, 31);
  vgaDrawTimer.priority(12);
}

volatile unsigned long vgaLineCount = 0;

// LED is bit 5 of C register
byte outputMask = B100000;
byte greenMask = B1000;

void syncVGA() {
  noInterrupts();
  vgaLineCount += 1;
  vgaLineCount = vgaLineCount % 525;
  
  if (vgaLineCount < 2) {
    // vsync pulse start
    // vsync (bit 0) go low
    GPIOB_PDOR = B00;
  } else {
    // vsync pulse end
    // vsync (bit 0) go high
    GPIOB_PDOR = B01;
  }

  for (int i = 0; i < 87; i++) {
    __asm("nop\n");
  }

  // hsync pulse end
  // hsync (bit 1) go high
  GPIOB_PDOR |= B10;
  
  interrupts();
}

void drawVGA() {
  for (int i = 0; i < 296; i++) {
    __asm("nop\n");
  }

  GPIOC_PDOR = outputMask | greenMask;
  
  for (int i = 0; i < 100; i++) {
    __asm("nop\n");
  }
  
  GPIOC_PDOR = outputMask;

  for (int i = 0; i < 3; i++) {
    __asm("nop\n");
  }

  GPIOC_PDOR = outputMask | greenMask;
  
  for (int i = 0; i < 20; i++) {
    __asm("nop\n");
  }
  
  GPIOC_PDOR = outputMask;
}

void loop() {
  // put your main code here, to run repeatedly:

}
