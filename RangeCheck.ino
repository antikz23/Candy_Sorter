#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

#define HOPPER  40
#define CHECK   82
#define DROP    100
/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

Servo myservo_top;
Servo myservo_base;

int pos = 0;


void setup(void) {
  Serial.begin(9600);
  myservo_top.attach(10, 500, 2700);
  // ././ myservo.setMaximumPulse(2500);
  // myservo.setMinimumPulse(500);
  myservo_base.attach(9, 500, 2700);
  // ././ myservo.setMaximumPulse(2500);
  // myservo.setMinimumPulse(500);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;


  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  // lux = tcs.calculateLux(r, g, b);

  myservo_top.write(HOPPER);
  delay(3000);

  //Goes to sensor
  myservo_top.write(CHECK);
  delay(1000);
  //Reads sensor
  tcs.getRawData(&r, &g, &b, &c);

  //Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  if ((r < 4500) && (r > 2700) && (g < 2450) && (g > 2100) && (b < 1650) && (b > 1400))
  {
    Serial.println("Orange");
    myservo_base.write(0);
    delay(1000);
    myservo_top.write(DROP);
    delay(1000);
  }
  if ((r < 2550) && (r > 2350) && (g < 3000) && (g > 2250) && (b < 1600) && (b > 1420))
  {
    Serial.println("Green");
    myservo_base.write(35);
    delay(1000);
    myservo_top.write(DROP);
    delay(1000);
  }
  if ((r < 4200) && (r > 2800) && (g < 3600) && (g > 2450) && (b < 2000) && (b > 1500))
  {
    Serial.println("Yellow");
    myservo_base.write(70);
    delay(1000);
    myservo_top.write(DROP);
    delay(1000);
  }
  if ((r < 2300) && (r > 1900) && (g < 2200) && (g > 1600) && (b < 1600) && (b > 1100))
  {
    Serial.println("Purple");
    myservo_base.write(115);
    delay(1000);
    myservo_top.write(DROP);
    delay(1000);
  }
  if ((r < 2900) && (r > 2300) && (g < 2200) && (g > 1800) && (b < 1550) && (b > 1300))
  {
    Serial.println("Red");
    myservo_base.write(150);
    delay(1000);
    myservo_top.write(DROP);
    delay(1000);
  }


}
