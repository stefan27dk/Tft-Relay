
// Libraries
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

// Pressure
#define MINPRESSURE 1
#define MAXPRESSURE 7000

//Output Pins Relay
#define RePin 13


 


// ALL Touch panels and wiring is DIFFERENT
// Get Results from TouchScreen_Calibr_native.ino in McuFriend Library examples



// Touch Calibration
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 158, TS_RT = 896, TS_TOP = 930, TS_BOT = 179; 


// Touchscreen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); // New Touchscreen 
int pixel_x, pixel_y;     //Touch_getXY() updates global vars

  


// COLORS
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF






 





// Is Pressed
bool IsPressed(void)
{
   TSPoint p = ts.getPoint(); // Get Point on Screen on touched 
   pinMode(YP, OUTPUT); // Restore Shared Pins
   pinMode(XM, OUTPUT);
   digitalWrite(YP, HIGH);   // Because TFT Control Pins
   digitalWrite(XM, HIGH);
   bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE); // Max Pressure
   
   if(pressed==true) // If pressed
   { 
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height()); 
   }

   return pressed;
}







// OnPressed
void OnPressed(bool pressed)
{ 
       if((pixel_x >= 40 && pixel_x <=100) && (pixel_y >= 200 && pixel_y <= 260))
       {
            tft.fillRect(40, 80, 160, 80, GREEN); 
            digitalWrite(RePin, HIGH); // Relay ON
       }  
    
    else if((pixel_x > 120 && pixel_x <=180) && (pixel_y >= 200 && pixel_y <= 260))
    {
      tft.fillRect(40, 80, 160, 80, RED); 
      digitalWrite(RePin, LOW); // Relay OFF

    } 
}





 



// Setup
void setup(void)
{
    Serial.begin(9600);
    tft.reset();
    uint16_t ID = tft.readID(); // Read ID 
    tft.begin(ID);
    tft.setRotation(0); //PORTRAIT / Landscape   
    tft.setCursor (15, 125);
    tft.fillScreen(BLACK); 
    tft.fillRect(40, 80, 160, 80, RED); // Big Rectangle

    tft.fillRect(40, 200, 60, 60, GREEN); // Left Button //ON
    tft.fillRect(120, 200, 60, 60, RED); // Right Button // OFF

    // Pins
     pinMode(RePin, OUTPUT);

}



// LOOP 
void loop(void)
{ 
  OnPressed(IsPressed());    
  
}




