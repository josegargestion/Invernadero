/**
 * @file configurations.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Archivo de definiciones para la configuracion inicial del sistema.
 * @version 0.0.3
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <Arduino.h>		// STD de arduino.
#include "DHT.h"		// STD de arduino.
#ifndef CONFIGURACION_H
#define CONFIGURACION_H
//#define DEBUG
#define NANO        // Activa compilación para nano usando pines sin expansores.
//#define S74HCXX // Activa la comìlacion usando expansores 74hc595 y 74hc165.
//#define MC23008 // Activa la comìlacion usando expansores MC23008.

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
const uint16_t SELECT_DELAY_DEFAULT = 1000;; // milliseconds
const uint16_t LAST_SLOT_DEFAULT = 99; ;      // number
const uint16_t EEPROM_ADDR = 0;;
const uint8_t EEPROM_SIG[2] = {0xee, 0x11};;
const uint8_t CONFIG_VERSION = 0;;
#define _RTC_ADD 0x68
#define _LCD_ADD 0x3f

// Configuracion de pines
const int _pinControlSondaMaximo = 12; // 22
const int _pinControlSondaMinimo = 11; // 21
const int _pinControlBomba = 10;
const uint8_t _HTINTPIN = 10;
const uint8_t _HTEXTPIN = 8;
const int _pinControlValvula = 7;
const int _DHTPIN = 8;
const int _pinControlDeshumidificador = 1;
const int _pinControlHumidificador = 2;
const int _pinControlExtractor = 3;
const int _pinControlCalefaccion = 4;
const int _pinControlImpulsor = 6;
const int _pinControlLampara = 7;
const int _SDA = 23;
const int _SCL = 24;
#ifdef NANO

#endif

#ifdef MC23008
const int _pinEstadoLampara = 0;
const int _pinEstadoSensorMaximo = 0;
const int _pinEstadoSensorMinimo = 0;
const int _pinEstadoBomba = 0;
const int _pinEstadoValvula = 0;
#define _IO1_ADD 0x20
#define _IO2_ADD 0x21
#endif

#endif
