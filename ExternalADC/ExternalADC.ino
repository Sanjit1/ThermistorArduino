#include <Wire.h>
#include <Adafruit_ADS1015.h>
double opVolt = 5;
double basRes = 10000;

Adafruit_ADS1115 ads1115(0x49);

void setup() {
  // put your setup code here, to run once:
  ads1115.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(getTemp(A0,A,B,C));
  delay(1000);

}

double getTemp(int pin, double Av ,double Bv , double Cv) {
  double res = getR(pin);
  return (1.0 / (Av + Bv * (double)ln(res) + Cv * (double)cb((double)ln(res)))) - 273.15;
}



double getR(int pin) {
  double v = getV(pin);
  return (basRes * (opVolt - v) / v);
}

double getV(int pin) {
  double volt = ((double)(ads1115.readADC_SingleEnded(pin) + (double)1) / (double)32768) * 6.144;
  return volt;
}

