#include <Arduino.h>
#define Rpin 1 // Pin must be with PWM
#define Gpin 2 // Pin must be with PWM
#define Bpin 3 // Pin must be with PWM
#define feedback_pin_with_interrupt_5 4
int fulfilmentR, fulfilmentG, fulfilmentB = 0;
uint8_t savedBrightness;
int counter;
void RGB(uint8_t, uint8_t, uint8_t, uint8_t);
void thunderFunction();
void setup()
{
  pinMode(feedback_pin_with_interrupt_5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(feedback_pin_with_interrupt_5), thunderFunction, FALLING);
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
}

void loop()
{
  if (counter > 0)
  {
    fulfilmentR = 255;
    fulfilmentG = 255;
    fulfilmentB = 255;
    RGB(255, 255, 255, 255);
    delay(100);
    for (size_t f = 255; f >= 0; f--)
    {
      RGB(f, 255, 255, f);
      delay(10);
      if (f == 0)
      {
        return;
      }
    }
  }
  counter--;
}

void thunderFunction()
{
  counter++;
}
// void thunderFunction()
// {
//   fulfilmentR = 255;
//   fulfilmentG = 255;
//   fulfilmentB = 255;
//   RGB(255, 255, 255, 255);
//   delay(100);
//   for (size_t f = 255; f >= 0; f--)
//   {
//     RGB(f, 255, 255, f);
//     delay(10);
//     if (f == 0)
//     {
//       return;
//     }
//   }
// }

void RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  if (r > 0 && g > 0 && b > 0)
  {
    int cetera = 255 - brightness;
    fulfilmentR = fulfilmentR - cetera;
    fulfilmentG = fulfilmentG - cetera;
    fulfilmentB = fulfilmentB - cetera;
    if (fulfilmentR <= 0)
    {
      fulfilmentR = 0;
    }
    if (fulfilmentG <= 0)
    {
      fulfilmentG = 0;
    }
    if (fulfilmentB <= 0)
    {
      fulfilmentB = 0;
    }
  }

  analogWrite(Rpin, fulfilmentR);
  analogWrite(Gpin, fulfilmentG);
  analogWrite(Bpin, fulfilmentB);
}