/*
 * 
 * This code snippet uses arduinos onboard ADC(Analog to digital Convertor). 
 * Look at externalAdc for code using Ads1115
 * go to sanjit1.github.io/Calibrator for more info
   Reference Formulas:
   Voltage Divider
            _____
           |     |
           |     R1
          Vin    |
         _____   |___ Vout
          ---    |
           |    R2
           |     |
           |_____|

   Vout = Vin*R2/(R1+R2)
   Simplified to: R1 = R2(Vin-Vout)/Vout
   Steinhart-hart Equation:
   1/T = A + B(ln(R)) + C(ln^3(R))

*/

// Voltage Divider Variables
double opVolt = 5; // The voltage at which Arduino operates
double basRes = 10000; // resistance R1

// Steinhart-hart Variables To calibrate, go to sanjit1.github.io/Calibrator/webCalibrator.html
double A = 0.0021085081731127137;
double B = 0.00007979204726779823;
double C = 6.535076314649466e-7;
double e = 2.7182818284590452353602874713527;


void setup() {
  Serial.begin(9600); // initialize the Serial Object
}

void loop() {
  Serial.println(getTemp(A0, A, B, C)); // print the Temperature using the get temp Function
  delay(1000); // wait for a second before giving another reading

}

double getTemp(int pin, double Av , double Bv , double Cv) {
  double res = getR(pin);
  return (1.0 / (Av + Bv * (double)ln(res) + Cv * (double)cb((double)ln(res)))) - 273.15;
  //Use the steinhart-Hart equation with the resistance from analog input
}



double getR(int pin) {
  double v = getV(pin);
  return (basRes * (opVolt - v) / v); // use the simplified voltage divider equation to find resistance 
}

double getV(int pin) {
  double volt = ((double)(analogRead(pin)/ (double)1024) * opVolt;
  /* Theory time: 
   * Arduinos Onboard ADC reads from 0 to 1023(10 bit)  
   * Since there are 1024 values possible, giving a range of 5 volts, we need to divide by 1024 and multiply by 5 volts.
   */
  return volt;
}

double ln(double val) {
  return (log(val) / log (e));
  // Natural log function
}

double cb(double val) {
  return val * val * val;
  // cube function, cuz why not
}
