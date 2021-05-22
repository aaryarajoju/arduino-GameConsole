#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       
#include <TouchScreen.h>

const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9341
const int TS_LEFT=165,TS_RT=940,TS_TOP=949,TS_BOT=183;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

uint16_t ID;
uint8_t Orientation = 1;   

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void showTFT() {

    tft.setCursor(0, 0);
    
    tft.fillRect(105, 25, 110, 60, RED);
    tft.fillRect(25, 90, 110, 60, RED);
    tft.fillRect(105, 155, 110, 60, RED);
    tft.fillRect(185, 90, 110, 60, RED);

    tft.setTextSize(3);
    
    tft.setCursor(140, 45);
    tft.print("UP");
    tft.setCursor(125, 175);
    tft.print("DOWN");
    tft.setCursor(45, 110);
    tft.print("LEFT");
    tft.setCursor(195, 110);
    tft.print("RIGHT");
  
}

void setup() {

    Serial.begin(9600);
    
    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);
    showTFT();

}

void loop() {

    uint16_t xpos, ypos;  
    tp = ts.getPoint(); 

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        
        xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
        ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());

        if (xpos > 105 && xpos < 215 && ypos > 25 && ypos < 85) {
            Serial.println("1");
            delay(200);
        } else if (xpos > 105 && xpos < 215 && ypos > 155 && ypos < 215) {
            Serial.println("2");
            delay(200);
        } else if (xpos > 25 && xpos < 135 && ypos > 90 && ypos < 150) {
            Serial.println("4");
            delay(200);
        } else if (xpos > 185 && xpos < 295 && ypos > 90 && ypos < 150) {
            Serial.println("3"); 
            delay(200);
        }
    }
}
