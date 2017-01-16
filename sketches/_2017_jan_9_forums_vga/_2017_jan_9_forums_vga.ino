#define Width  120 //sreen pixels
#define Height  100  //screen pixels

uint8_t lcdBuffer[Height*Width]; 

// VGA PINS
#define RGB_OUT GPIOB_PDOR
#define PIN_VR1 16 
#define PIN_VR2 17
#define PIN_VG1 19
#define PIN_VG2 18
#define PIN_VB1 0
#define PIN_VB2 1
//#define PIN_VI1 32 //not used in this code - can delete
//#define PIN_VI2 25 //not used in this code - can delete
#define PIN_VBLANK 3
#define PIN_HBLANK 5

byte colours[6] = {0x01,0x02,0x04,0x08,0x10,0x20};

static volatile int VSYNC = 0;

#define NOP asm volatile("nop\n\t");

volatile uint32_t currentLine = 0;
volatile uint32_t currentFrame = 0;

IntervalTimer timer0;

#define UPPER_BORDER 40

void timerLine() {
  cli();

  if (currentLine>1) {
    digitalWrite(PIN_VBLANK, 1);
  } else {
    digitalWrite(PIN_VBLANK, 0);
  }

  digitalWrite(PIN_HBLANK, 0);
  RGB_OUT = 0x00;
  RGB_OUT = 0x00;
  RGB_OUT = 0x00;
  RGB_OUT = 0x00;
  
  digitalWrite(PIN_HBLANK, 1);

  currentLine++;
  currentLine = currentLine%525;

  NOP;

  uint32_t y = (currentLine - UPPER_BORDER)>>2;//how many rows to duplicate (to square up the image)

//display output section is within the timer >>
  if (y>=0 && y<Height){  //for each row do
  
    for (int i=0; i<40; i++) {//left edge buffer
      RGB_OUT = 0;
    }
    
    uint8_t* displayPointer = lcdBuffer + Width*y;
    
      for (int x=Width; x>0; x--) { //which way round?? 
    
    uint32_t color = *(displayPointer++);

      color = color | (color<<12); //shift bits
      RGB_OUT = color;
      RGB_OUT = color;
      RGB_OUT = color;
      RGB_OUT = color; //four calls wide to square up each pixel
    }//end of one row of pixels
  }//end of display output section

  VSYNC = 0;
   if (y==Height) {  
    VSYNC = 1;
  }
  RGB_OUT = 0;
  sei();
}


void setup()   {

  delay(500);
  pinMode(PIN_VR1, OUTPUT);
  pinMode(PIN_VG1, OUTPUT);
  pinMode(PIN_VB1, OUTPUT);
//  pinMode(PIN_VI1, OUTPUT);
  pinMode(PIN_VR2, OUTPUT);
  pinMode(PIN_VG2, OUTPUT);
  pinMode(PIN_VB2, OUTPUT);
//  pinMode(PIN_VI2, OUTPUT);
  pinMode(PIN_VBLANK, OUTPUT);
  pinMode(PIN_HBLANK, OUTPUT);
  
  timer0.begin(timerLine, 31.468);

}

unsigned int tick = 0;

int y =0;

void loop()          
{
    if (VSYNC==1) {
      tick++;   
      VSYNC=0;
//fill the buffer
      
//fill the screen with a colour
fillScreen(colours[5]);
  
//then draw a diagonal series of dots
//then draw a line 
  drawLine(10,10,100,100,0x1); 

//then draw a line 
  for(int x=0;x<100;x++){
   putPixel(x,10,0x1);
   }
   
    }
}
//------------drawing functions-------------------------//
void putPixel(int x0,int y0,uint8_t color) {
  lcdBuffer[y0*Width+x0] = color;
}
void drawLine(int x0, int y0, int x1, int y1, uint8_t color) {
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    putPixel(x0,y0,color);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}
void fillScreen(uint8_t c) {
  for (int y=0; y<Height; y++) {
    for (int x=0; x<Width; x++) {
      lcdBuffer[y*Width+x] = c;
    }
  }
}
