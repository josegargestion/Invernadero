/**
 * @brief
 *
 * @attention
 *
 * @author Josegar1908@gmail.com
 * @version 0.0.3
 *
 * @todo
 *
 * */
#include "utility\Debug.h"          // Biblioteca de macros de errores.
#include "src\ControlTiempos.h" // Personal de control de tiempos del procesador y horarios.
#include "src\invernadero.h"        // Clase maestra de control del sistema.
#include <Arduino.h>            // STD de arduino.
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
    Inver1.Control();
    mainMillis.lastmillis = millis();
  }
}
