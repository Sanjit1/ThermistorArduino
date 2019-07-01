#include <LiquidCrystal.h>
LiquidCrystal screen(12, 11, 5, 4, 3, 2);
int ThermistorPin = A0;
double measuredResistance,temperature;
float baseResistance = 10000;
double A =0.0021085081731127137;
double B =0.00007979204726779823;
double C =6.535076314649466e-7;
double e = 2.7182818284590452353602874713527;

void setup() {
  screen.begin(16,2);
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(b,OUTPUT);
  while (1 == 1) {

    measuredResistance = getR(A0);
    temperature = (1.0 / (A + B * ln(measuredResistance) + C * cb(ln(measuredResistance)))) - 273.15;
    screen.clear();
    screen.print(": ");
    screen.print(temperature);
    screen.println(" C");

    delay(100);
  }
}


float getR(int pin) {
  // A function to get the resistance of any thermistor
  int raw = 0;
  int VoltIn = 5;
  float VoltOut = 0;
  float R1 = 10000;
  float R2 = 0;
  float buff = 0;
  raw = analogRead(pin); // get raw data of the sensor
  buff = raw * VoltIn; // Multiply it by 5 volts(default for arduino
  VoltOut = (buff) / 1024.0;  //Figure out the voltage input to the Analog pin
  buff = (VoltIn / VoltOut) - 1; // Use ohm's law to figure out the resistance 
  R2 = R1 * buff;
  return R2; // return the resistance



}


double ln(double val) {
  return (log(val) / log (e));
}

double cb(double val){
  return val*val*val;
  }
