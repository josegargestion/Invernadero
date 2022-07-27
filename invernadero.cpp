/**
 * @file invernadero.cpp
 * @brief Codigo de la biblioteca deposito.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @version 0.5.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2021
 */
#include "configurations.h" // Guarda los datos por defecto del equipo.
#include "debug.h"          // Necesario para las llamadas de depuración.
#include "cAPPconfig.h"     // Guardado de datos a EEPROM.
#include "debug.h"          // Necesario para las llamadas de depuración.
#include "Time.h"           // Control de horas y tiempos, ademas del rtc.
#include "estructuras.h"    // Estructuras de datos.
#include "deposito.h"       // Control sistema de deposito de liquidos
#include "ambiente.h"       // Control del ambiente.
#include "Iluminacion.h"    // Control iluminación.
#include "invernadero.h"    // Clase maestra de control del sistema.
#include "hardware.h"       // Clase de control del hardware.
#include "ControlTiempos.h" // Clase de control de horarios.
#include <Arduino.h>        // STD de arduino.
cAppConfig configApp1;
Control_Tiempos Horario1;
Hardware Sistema1;
Deposito Deposito1;
Ambiente Ambiente1;
Iluminacion Iluminacion1;
millis_set inverMillis;
Inver::Inver()
{
}
void Inver::begin()
{
  DTIME;
  DPRINTLN(F(" Inicializando modulos. "));
  DTIME;
  DPRINTLN(F(" Begin Sistema1"));
  Sistema1.begin();
  DTIME;
  DPRINTLN(F(" Begin configApp1."));
  configApp1.begin();
  DTIME;
  DPRINTLN(F(" Begin Iluminacion1."));
  Iluminacion1.begin();
  DTIME;
  DPRINTLN(F(" Begin Ambiente1"));
  Ambiente1.begin();
  DTIME;
  DPRINTLN(F(" Begin Deposito1"));
  Deposito1.begin();
  DTIME;
  DPRINTLN(F(" Carga de variables desde memoria. "));
  Horario1.SetTimeOn(configApp1._D.OnHora, configApp1._D.OnMinuto);
  Horario1.SetTimeOff(configApp1._D.OffHora, configApp1._D.OffMinuto);
  // Ambiente1.SetTimeOn(configApp1._D.OnHora, configApp1._D.OnMinuto, configApp1._D.OnTemp, configApp1._D.OnHr);
  // Ambiente1.SetTimeOff(configApp1._D.OffHora, configApp1._D.OffMinuto, configApp1._D.OffTemp, configApp1._D.OffHr);
#ifdef DEBUG
  configApp1._D.CalBomba = true;
  configApp1._D.CalValvula = true;
#endif
  if (configApp1._D.CalBomba && configApp1._D.CalValvula)
  {
    DTIME;
    DPRINTLN(F(" Cargando calibracion desde EEPROM."));
    Sistema1.estadoHardware.CalBomba = configApp1._D.CalBomba;
    Sistema1.estadoHardware.CalValvula = configApp1._D.CalValvula;
    Sistema1.estadoHardware.TCalibracionBomba = configApp1._D.TCalibracionBomba;
    Sistema1.estadoHardware.TCalibracionValvula = configApp1._D.TCalibracionValvula;
  }
  else
  {
    DTIME;
    DPRINTLN(F(" Generando nueva calibracion."));
    configData_t tempconfig;
    tempconfig = Sistema1.SetCalibracion(configApp1._D);
    configApp1._D = tempconfig;
    DTIME;
    DPRINTLN(F(" Guardando calibracion en EEPROM."));
    configApp1.configSave();
  }
}
void Inver::Control()
{
  Sistema1.Control();
  Iluminacion1.Control();
  Ambiente1.Control();
  Deposito1.Control();
}
