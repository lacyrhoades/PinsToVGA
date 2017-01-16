const int led = 13;

const int vSyncPin = 16;
const int hSyncPin = 17;

const int red = 9;
const int green = 2;
const int blue = 3;

IntervalTimer vgaLineTimer;

int buffer[480][640] = {};

void setup() {  
  pinMode(led, OUTPUT);
  
  pinMode(vSyncPin, OUTPUT);
  pinMode(hSyncPin, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  vgaLineTimer.begin(drawVGALine, 31);
  vgaLineTimer.priority(0);
}

volatile unsigned long vgaLineCount = 0;
void drawVGALine() {
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

  // hsync pulse start
  // hsync (bit 1) go low
  // GPIOB_PDOR &= B01;
  // already is low

  for (int i = 0; i < 86; i++) {
    __asm("nop\n");
  }

  // hsync pulse end
  // hsync (bit 1) go high
  GPIOB_PDOR |= B10;

  // blank color info
  GPIOC_PDOR = B100000;

  // back porch
  for (int i = 0; i < 40; i++) {
    __asm("nop\n");
  }

  // red, green and blue are all in register C
  for (int i = 0; i < 301; i++) {
    GPIOC_PDOR = B101000;
  }

  for (int i = 0; i < 12; i++) {
    GPIOC_PDOR = B100000;
  }

  for (int i = 0; i < 301; i++) {
    GPIOC_PDOR = B101000;
  }
  
  GPIOC_PDOR = B100000;

  // front porch
  for (int i = 0; i < 11; i++) {
    __asm("nop\n\n");
  }
}

void loop() {
//  delay(1000);
//  
//  Serial.println(cVal, BIN);

  // noInterrupts();
//  if (val & B1000) {
//    val = B100000;
//  } else {
//    val = B101000;
//  }
  // interrupts();
}

