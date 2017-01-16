const int led = 13;

const int vSyncPin = 16;
const int hSyncPin = 17;

const int red = 9;
const int green = 2;
const int blue = 3;

byte graphicsBuffer[128] = {B00110011, B00001010, B10101101, B10111010, B10101111, B00010100, B00001011, B11101001, B10100100, B10000101, B11111000, B10110000, B00001111, B10101011, B10011101, B11000100, B01100110, B01101011, B11000010, B00100110, B11000000, B10110001, B10001010, B00010010, B10000110, B10100110, B00110101, B10001000, B01010010, B00000010, B00011011, B11000111, B00010000, B00111110, B10110010, B00011000, B01011010, B11110110, B01000111, B10010011, B00011100, B10110010, B01101011, B01000010, B10001101, B00001001, B00100110, B00111100, B11010000, B11101010, B01000111, B00111111, B01010001, B10100110, B11110010, B10010100, B10011000, B00110001, B11100010, B11110000, B00111000, B11110101, B11000101, B10100101, B11100111, B10010110, B10011111, B10101101, B11010110, B01001110, B00111101, B10011001, B10001101, B10000010, B01000110, B00110110, B01011111, B00010101, B10110110, B11010110, B10011000, B01111100, B01001110, B01011000, B00101011, B00011100, B10000001, B11101110, B01111010, B00101000, B01111101, B11001111, B00000001, B00110001, B01111110, B11101000, B01011101, B00011101, B01101000, B01110110, B00001011, B10101111, B10011001, B01101110, B01000001, B01101100, B00010011, B01000001, B11100110, B01010100, B10011111, B11001011, B00101110, B00011011, B11011000, B01010010, B00100110, B01100111, B10010110, B00000111, B01101011, B01000110, B00100110, B10101110, B01001011, B11001111, B00001111, B01010101};

IntervalTimer vgaLineTimer;

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

byte outputPinMask = B1000;

// bit 5 is the LED
byte blankColorMask = B100000;

void drawVGALine() {
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
  GPIOC_PDOR = blankColorMask;

  // back porch
  for (int i = 0; i < 26; i++) {
    __asm("nop\n");
  }

  // red, green and blue are all in register C
  for (int i = 0; i < 16; i++) {
    
    byte val = *(graphicsBuffer + i * (1 + vgaLineCount / 100));

    drawPixel(val >> 7);
    drawPixel(val >> 6);
    drawPixel(val >> 5);
    drawPixel(val >> 4);
    drawPixel(val >> 3);
    drawPixel(val >> 2);
    drawPixel(val >> 1);
    drawPixel(val);
  }

  GPIOC_PDOR = blankColorMask;

  // front porch
  for (int i = 0; i < 11; i++) {
    __asm("nop\n\n");
  }

  interrupts();
}

void drawPixel(int value) {
  GPIOC_PDOR = value & outputPinMask;
  GPIOC_PDOR = value & outputPinMask;
}

void loop() {
//  delay(1000);
  
//  Serial.println(boffset);

//  noInterrupts();
//  boffset += 1;
//  interrupts();
}

