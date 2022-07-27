/*
#include "deposito.h"
#include "configurations.hpp"
#include "DHT.h"
#include "ambiente.h"
#include <Wire.h>
#include <RTCx.h>

DHT sensorInterior(DHTPIN, DHTTYPE);
Ambiente interior(DHTPIN, DHTTYPE);

boolean ESTADOBOMBA = false;
Deposito Deposito1(BOMBA,SONDAMAXIMO,SONDAMINIMO);

void setup(){
  Serial.begin(9600);
  Wire.begin();
	Serial.println("Autoprobing for a RTC...");
	if (rtc.autoprobe()) {
		// Found something, hopefully a clock.
		Serial.print("Autoprobe found ");
		Serial.print(rtc.getDeviceName());
		Serial.print(" at 0x");
		Serial.println(rtc.getAddress(), HEX);
	rtc.enableBatteryBackup();

	// rtc.clearPowerFailFlag();

	// Ensure the oscillator is running.
	rtc.startClock();
 }

void loop(){

Deposito1.ControlDeposito(BOMBA,SONDAMAXIMO,SONDAMINIMO);

  delay(2000);

  float h = interior.GetHR(sensorInterior);

  float t = interior.GetTemp(sensorInterior);

float h;
h = Ambiente1.sondaInterior.readTemperature();
Serial.print("Temperatura Interior : ");
Serial.println(h);
h = Ambiente1.sondaInterior.readHumidity();
Serial.print("Humedad Interior : ");
Serial.println(h);
h = Ambiente1.sondaExterior.readTemperature();
Serial.print("Temperatura Exterior : ");
Serial.println(h);
h = Ambiente1.sondaExterior.readHumidity();
Serial.print("Humedad Exterior : ");
Serial.println(h);
}
*/