#include <Arduino.h>
#define Rpin 10 // Pin must be with PWM
#define Gpin 9  // Pin must be with PWM
#define Bpin 11 // Pin must be with PWM
#define feedback_pin_with_interrupt_5 3
int fulfilmentR, fulfilmentG, fulfilmentB = 0;
uint8_t savedBrightness;
uint64_t savedTime, savedTime1, savedTime2;
uint64_t actualTime;
uint8_t f, f1;
bool lock = 0;
bool lock1 = 1;
bool lock2 = 0;
uint8_t brightnessTest, fadeAmount;
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
  actualTime = micros();
  if (actualTime - savedTime2 >= 3000UL && lock2 == 0)
  {
    savedTime2 = actualTime;
    brightnessTest = brightnessTest + fadeAmount;
    if (brightnessTest <= 0 || brightnessTest >= 255)
    {
      fadeAmount = -fadeAmount;
    }

    RGB(brightnessTest, brightnessTest, brightnessTest);
  }

  if (actualTime - savedTime >= 100000UL && lock == 0)
  {
    savedTime = actualTime;
    RGB(255, 255, 255);
    lock = 1;
    lock1 = 0;
  }
  if (actualTime - savedTime1 >= 100UL && lock == 1 && lock1 == 0)
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
  lock2 = 1;
  fulfilmentR = 255;
  fulfilmentG = 255;
  fulfilmentB = 255;
  f = 255;
  f1 = 255;
  lock = 0;
  lock1 = 1;
}

void RGB(uint8_t r, uint8_t g, uint8_t b)
{
  fulfilmentR = r;
  fulfilmentG = g;
  fulfilmentB = b;
  analogWrite(Rpin, fulfilmentR);
  analogWrite(Gpin, fulfilmentG);
  analogWrite(Bpin, fulfilmentB);
}