/**
 * @file configurations.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Archivo de definiciones para la configuracion inicial del sistema.
 * @version 0.5.0
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h> // STD de arduino.
#include "DHT.h"     // STD de arduino.
#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#define DEBUG   // Activa el modo depuracion.
#define NANO // Activa compilación para nano usando pines sin expansores.
//#define ESP826    // Activa compatibilidad con esp8266
//#define ESP32WROOM // Activa compatibilidad con ESP32
//#define LCD // Activa opciones de pantalla LCD
//#define S74HCXX // Activa la compilacion usando expansores 74hc595 y 74hc165.
//#define MC23008 // Activa la compilacion usando expansores MC23008.
#define NODEPOSITO // Desactiva el deposito.
//#define RTC // Activa opciones de reloj de tiempo real.
//#define RELOJI2C // Activa el reloj I2C
//#define DS1307RTC // Configuracion para Reloj DS1307RTC por I2C


// Configuracion de parametros por defecto.
const uint8_t _DEFECTO_HORA_ON = 23;
const uint8_t _DEFECTO_MINUTO_ON = 10;
const uint8_t _DEFECTO_HORA_OFF = 16;
const uint8_t _DEFECTO_MINUTO_OFF = 5;
const float _DEFECTO_TEMP_ON = 21;
const float _DEFECTO_TEMP_OFF = 18;
const float _DEFECTO_HR_ON = 50;
const float _DEFECTO_HR_OFF = 60;
const unsigned long _DEFECTO_PERIODO = 5000;
const unsigned long _CalibracionBomba = 10000; // Tiempo de calibracion de la bomba.
const bool _CalBomba = false;
const bool _CalValvula = false;
const unsigned long _CalibracionValvula = 10000; // Tiempo de calibracion de la valvula.
const uint8_t _HTINTTYPE = DHT22;
const uint8_t _HTEXTTYPE = DHT22;
const uint8_t _DHTTYPE = DHT22;
const bool ON = true;
const bool OFF = false;
const uint16_t SELECT_DELAY_DEFAULT = 1000;
const uint16_t LAST_SLOT_DEFAULT = 99;
const uint16_t EEPROM_ADDR = 0;
const uint8_t EEPROM_SIG[2] = {0xee, 0x11};
const uint8_t CONFIG_VERSION = 0;

#ifdef RTC
#include "hal\Relojes.h"
#endif

#ifdef LCD
#include "hal\Pantallas.h"
#endif

#ifdef NANO
#include "hal\nano.h"
#endif

#ifdef MC23008
#include "hal\MC23008.h"
#endif

#endif
