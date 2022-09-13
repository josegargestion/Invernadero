/**
 * @file inver.ino
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 **/
#include "Debug.h"       // Biblioteca de macros de errores.
#include "estructuras.h" // Personal de control de tiempos del procesador y horarios.
#include "invernadero.h" // Clase maestra de control del sistema.
#include <Arduino.h>     // STD de arduino.
Inver Inver1;
millis_set mainMillis;

void setup()
{
  mainMillis.currentmillis = millis();
  mainMillis.period = 1000;
  mainMillis.lastmillis = 0;
  Serial.begin(19200);
  Inver1.begin();
}

void loop()
{
  mainMillis.currentmillis = millis();
  if (mainMillis.currentmillis - mainMillis.lastmillis >= mainMillis.period)
  {
    DPRINTLN(F(" 000 - Loop principal. "));
    Inver1.Control();
    mainMillis.lastmillis = millis();
  }
}
