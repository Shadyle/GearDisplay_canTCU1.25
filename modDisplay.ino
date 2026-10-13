#include <Adafruit_GFX.h>

//#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Wire.h>
#define SSD1306_NO_SPLASH 0
#define SH1106_NO_SPLASH 0
#define SH1106 1

#ifdef SSD1306
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 tft(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//#define OLED_DC     6 
//#define OLED_CS     7
#define OLED_RESET  -1
#endif

#ifdef SH1106
  #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
  #include <Adafruit_SH1106.h>
  #define OLED_RESET 4
  Adafruit_SH1106 tft(OLED_RESET);
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


char cTemperature[20];
// Initialize Adafruit ST7789 TFT library
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
//Adafruit_SSD1306 tft(SCREEN_WIDTH, SCREEN_HEIGHT,
//  &SPI, OLED_DC, OLED_RESET, OLED_CS);



unsigned long tmrRefreshDisplay;
int tmrRefreshDisplayInterval = 500;

void InitDisplay(){
#ifdef SSD1306
  if(!tft.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }else{
    Serial.println(F("SSD1306 allocation success"));
  }
  tft.clearDisplay();
#endif
#ifdef SH1106
  tft.begin(SH1106_SWITCHCAPVCC , SCREEN_ADDRESS);

  tft.clearDisplay();
#endif

  tft.fillScreen(BLACK);
 gear = '-';
 gmode = '-';
 temp = 0;
 bRefresh = 1;



  tft.display();
 // tft.setRotation(3);
}

void LoopDisplay(){
 if ((unsigned long)(millis() - tmrRefreshDisplay) >= tmrRefreshDisplayInterval) {
  if(bRefresh == 1){
    ClearDisplay();
    itoa(temp,cTemperature,10);
    SetWrap(false);                       // turn off text wrap option
    tft.setFont(&FreeSerif9pt7b);
    ShowNum(iTemperatureLeft,iTemperatureTop,temp,1);
    tft.setFont(&FreeSerif12pt7b);
    ShowText(iGearPosLeft,iGearPosTop,gear,3);
    ShowText(iGearModeLeft,iGearModeTop,gmode,1);
    //ShowText(iTemperatureLeft,iTemperatureTop,temp,3);
  
    tmrRefreshDisplay = millis();
    bRefresh = 0;
  }
} 
}




void ClearDisplay(){
tft.clearDisplay();
}
void SetWrap(bool bWrap){
tft.setTextWrap(bWrap);
}
void InvertDisplay(bool bInvert){
    tft.invertDisplay(bInvert);
}
void ShowText(int iLeft,int iTop,char cText,int iSize){
 // tft.cp437(true);
    tft.setTextColor(WHITE);  // set text color to YELLOW and black background
  tft.setTextSize(iSize);           // text size = 3
  tft.setCursor(iLeft, iTop);        // move cursor to position (15, 27) pixel
  tft.print(cText);
   tft.display();
}
void ShowNum(int iLeft,int iTop,int iNumber,int iSize){
 // tft.cp437(true);
    tft.setTextColor(WHITE);  // set text color to YELLOW and black background
  tft.setTextSize(iSize);           // text size = 3
  tft.setCursor(iLeft, iTop);        // move cursor to position (15, 27) pixel
  tft.print(iNumber);
   tft.display();
}

