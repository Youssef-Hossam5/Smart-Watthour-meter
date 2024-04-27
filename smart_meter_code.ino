#include <EmonLib.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

EnergyMonitor emon;
 
#define vCalibration 146.55
#define currCalibration 19.55

float kWh = 0;
unsigned long lastmillis = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  emon.voltage(14, vCalibration, 0); // Voltage: input pin, calibration, phase_shift
  emon.current(16, currCalibration); // Current: input pin, calibration.
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Digital Electricity");
  lcd.setCursor(7, 1);
  lcd.print("Meter");
  delay(3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  emon.calcVI(20, 2000);
  kWh = kWh + emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  yield();
  Serial.print("Vrms: ");
  Serial.print(emon.Vrms, 2);
  Serial.print("V");
 
  Serial.print("\tIrms: ");
  Serial.print(emon.Irms, 4);
  Serial.print("A");
 
  Serial.print("\tPower: ");
  Serial.print(emon.apparentPower, 4);
  Serial.print("W");
 
  Serial.print("\tkWh: ");
  Serial.print(kWh, 5);
  Serial.println("kWh");
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vrms:");
  lcd.print(emon.Vrms, 2);
  lcd.print("V");
  lcd.setCursor(0, 1);
  lcd.print("Irms:");
  lcd.print(emon.Irms, 4);
  lcd.print("A");
  lcd.setCursor(0, 2);
  lcd.print("Power:");
  lcd.print(emon.apparentPower, 4);
  lcd.print("W");
  lcd.setCursor(0, 3);
  lcd.print("kWh:");
  lcd.print(kWh, 4);
  lcd.print("W");
  delay(1000);
 
  lastmillis = millis();
}