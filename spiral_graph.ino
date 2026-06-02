/*
Draw Spiral Graph 

***
 Mathematical Equation
r=a+bθ
r=a+bθ
📌 Explanation:
    rr is the distance from the origin to a point on the spiral.
    θθ is the angle in radians (starting from the Y-axis in your code).
    aa is the starting radius (in your code, a = 1.0).
    bb is the rate at which the spiral expands (in your code, b = 0.2).
This is known as an Archimedean Spiral, where the radius increases linearly with the angle.
***

1. Wiring: ST7735S TFT + Arduino Uno
TFT Pin	Arduino Uno	Function
VCC	5V	Power
GND	GND	Ground
CS	D10	Chip Select
RESET	D8	Reset
DC or A0	D9	Data/Command select
SDA	D11	SPI Data (MOSI)
SCL	D13	SPI Clock (SCK)
LED or BLK	3.3V or 100Ω to 5V	Backlight
2. Analog Joystick to Arduino Uno (unchanged)
Joystick Pin	Arduino Uno
GND	GND
VCC	5V
VRx	A0
VRy	A1
SW	D2

*/

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// TFT Pins
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define SCREEN_W 128
#define SCREEN_H 160

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  drawLabels();   // Label text and equation
  drawSpiral();   // Draw spiral with axes
}

void loop() {
  // Nothing here
}

void drawLabels() {
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.println("Spiral: Polar Form");

  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(5, 18);
  tft.println("r = a + bθ");

  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(5, 32);
  tft.println("a = 1.0, b = 0.2");
}

void drawCoordinateAxes(int centerX, int centerY) {
  // Draw Y-axis
  tft.drawLine(centerX, 0, centerX, SCREEN_H, ST77XX_RED);

  // Draw X-axis
  tft.drawLine(0, centerY, SCREEN_W, centerY, ST77XX_RED);

  // Draw ticks on X-axis
  for (int x = centerX - 60; x <= centerX + 60; x += 10) {
    tft.drawPixel(x, centerY - 1, ST77XX_WHITE);
    tft.drawPixel(x, centerY + 1, ST77XX_WHITE);
  }

  // Draw ticks on Y-axis
  for (int y = centerY - 60; y <= centerY + 60; y += 10) {
    tft.drawPixel(centerX - 1, y, ST77XX_WHITE);
    tft.drawPixel(centerX + 1, y, ST77XX_WHITE);
  }
}

void drawSpiral() {
  float angle = PI / 2;      // Start from Y-axis
  float radius = 1.0;        // Smaller initial radius
  float angleStep = 0.1;     // Tighter spiral
  float radiusStep = 0.2;    // Slower growth

  int centerX = SCREEN_W / 2;
  int centerY = SCREEN_H / 2 + 20;  // Move spiral down to fit labels

  drawCoordinateAxes(centerX, centerY);  // Draw axes first

  int prevX = centerX + cos(angle) * radius;
  int prevY = centerY + sin(angle) * radius;

  for (int i = 0; i < 180; i++) {
    angle += angleStep;
    radius += radiusStep;

    int x = centerX + cos(angle) * radius;
    int y = centerY + sin(angle) * radius;

    tft.drawLine(prevX, prevY, x, y, ST77XX_YELLOW);

    prevX = x;
    prevY = y;

    delay(5);
  }
}

