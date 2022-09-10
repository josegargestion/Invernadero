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

#define NANO // Activa compilación para nano usando pines sin expansores.
//#define ESP826    // Activa compatibilidad con esp8266
//#define ESP32WROOM // Activa compatibilidad con ESP32
//#define LCD // Activa opciones de pantalla LCD
//#define S74HCXX // Activa la compilacion usando expansores 74hc595 y 74hc165.
//#define MC23008 // Activa la compilacion usando expansores MC23008.
//#define NODEPOSITO // Desactiva el deposito.
//#define RTC // Activa opciones de reloj de tiempo real.
//#define RELOJI2C // Activa el reloj I2C
//#define DS1307RTC // Configuracion para Reloj DS1307RTC por I2C
#include "hal\hal.h"
#endif
