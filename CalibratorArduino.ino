double opVolt = 5;
double basRes = 10000;

double A = 0.0021085081731127137;
double B = 0.00007979204726779823;
double C = 6.535076314649466e-7;
double e = 2.7182818284590452353602874713527;


void setup() {
  // put your setup code here, to run once:
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
  double volt = ((double)(analogRead(pin) + (double)1) / (double)1024) * opVolt;
  return volt;
}

double ln(double val) {
  return (log(val) / log (e));
}

double cb(double val) {
  return val * val * val;
}
