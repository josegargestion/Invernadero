/**
 * @file hal.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Archivo de Abstraccion de hardware
 * @version 0.0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h> // STD de arduino.
#include "..\DHT.h"     // STD de arduino.
#include "..\configurations.h"
#ifndef HAL_H
#define HAL_H

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
#include "Relojes.h"
#endif

#ifdef LCD
#include "Pantallas.h"
#endif

#ifdef NANO
#include "nano.h"
#endif

#ifdef MC23008
#include "MC23008.h"
#endif

#endif