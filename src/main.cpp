#include <Arduino.h>
#define Rpin 1 // Pin must be with PWM
#define Gpin 2 // Pin must be with PWM
#define Bpin 3 // Pin must be with PWM
#define feedback_pin_with_interrupt_5 4
int fulfilmentR, fulfilmentG, fulfilmentB = 0;
uint8_t savedBrightness;
uint64_t savedTime, savedTime1;
uint64_t actualTime;
uint8_t f, f1;
bool lock = 0;
bool lock1 = 1;
void RGB(uint8_t, uint8_t, uint8_t);
void thunderFunction();

void setup()
{
  pinMode(feedback_pin_with_interrupt_5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(feedback_pin_with_interrupt_5), thunderFunction, LOW);
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
}

void loop()
{
  actualTime = millis();
  if (actualTime - savedTime >= 100UL && lock == 0) //
  {
    savedTime = actualTime;
    RGB(255, 255, 255);
    lock = 1;
    lock1 = 0;
  }
  if (actualTime - savedTime1 >= 10UL && lock == 1 && lock1 == 0)
  {
    savedTime1 = actualTime;

    if (f > 0)
    {
      f--;
      RGB(f, 255, 255);
    }
    if (f == 0)
    {
      f1--;
      RGB(0, f1, f1);
    }
    if (f1 == 0)
    {
      RGB(0, 0, 0);
      lock1 = 1;
    }
  }
}

void thunderFunction()
{
  fulfilmentR = 255;
  fulfilmentG = 255;
  fulfilmentB = 255;
  f = 255;
  f1 = 255;
  lock = 0;
  lock1 = 1;
  // RGB(255, 255, 255, 255);
  // delay(100);

  // for (size_t f = 255; f >= 0; f--)
  // {
  //   if (f == 0)
  //   {
  //     RGB(0, 0, 0, 0);
  //     return;
  //   }
  //   RGB(f, 255, 255, f);
  //   delay(10);
  // }
}

void RGB(uint8_t r, uint8_t g, uint8_t b)
{
  // if (r > 0 && g > 0 && b > 0)
  // {
  //   int cetera = 255 - brightness;
  //   fulfilmentR = fulfilmentR - cetera;
  //   fulfilmentG = fulfilmentG - cetera;
  //   fulfilmentB = fulfilmentB - cetera;
  //   if (fulfilmentR <= 0)
  //   {
  //     fulfilmentR = 0;
  //   }
  //   if (fulfilmentG <= 0)
  //   {
  //     fulfilmentG = 0;
  //   }
  //   if (fulfilmentB <= 0)
  //   {
  //     fulfilmentB = 0;
  //   }
  // }
  analogWrite(Rpin, fulfilmentR);
  analogWrite(Gpin, fulfilmentG);
  analogWrite(Bpin, fulfilmentB);
}