/**
 * @file hal\Pantallas.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Archivo configuracion placa Arduino Nano
 * @version 0.5.0
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PANTALLAS_H
#define PANTALLAS_H

//#define DISPLAYI2C // Activa la pantalla I2C
#ifdef DISPLAYI2C
#define _LCD_ADD 0x3f
#endif

#endif