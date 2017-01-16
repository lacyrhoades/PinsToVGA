
// only one "page"
volatile byte graphicsBuffer[1024] = {};
volatile int byteCount = 0;

const int led = 13;

const int d0 = 2;
const int d1 = 14;
const int d2 = 7;
const int d3 = 8;
const int d4 = 6;
const int d5 = 20;
const int d6 = 21;
const int d7 = 5;

const int rs = 0;
const int rw = 1;
const int en = 19;

const int cs1 = 17;
const int cs2 = 18;

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);

  pinMode(rs, INPUT);
  pinMode(rw, INPUT);
  pinMode(en, INPUT);
  
  pinMode(cs1, INPUT);
  pinMode(cs2, INPUT);

  attachInterrupt(en, readPins, FALLING);
}

void loop() {
  delay(500);
  dumpBuffer();
}

void dumpBuffer() {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 64; i++) {
      Serial.print( (graphicsBuffer[i] >> j) & B01 );
    }
    Serial.println("");
  }
  Serial.println("");
  Serial.println("");
}

void readPins() {
  // rs = 1 and rw = 0 means someone is writing display data
  if ((GPIOB_PDIR & 0x10000) && (GPIOB_PDIR & 0x20000) == 0) {
    // write data pins to buffer
    graphicsBuffer[byteCount] = GPIOD_PDIR & B11111111;

    // next time write to the next byte in the buffer
    byteCount += 1;
    byteCount = byteCount % 1024;
  }
}

