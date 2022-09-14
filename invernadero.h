/**
 * @file invernadero.h
 * @brief Control principal del sistema.
 *
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @version 0.5.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2021
 */
#pragma once
#ifndef INVERNADERO_H
#define INVERNADERO_H
#include "ihal.h"
/// @brief clase invernadero, crear con Inver <objname>; .
class Inver
{
public:
    IHAL &_hal;
    Inver();
    Inver(IHAL &_hal); /// Constructor.
    void begin();          /// Inicializacion.
    void Control();        /// LLamada de ejecucion.
};
#endif