#line 1 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\invernadero.h"
/**
 * @file invernadero.h
 * @brief Control principal del sistema.
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @version 0.5.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2022
 */
#ifndef INVERNADERO_H
#define INVERNADERO_H
/// @brief clase invernadero, crear con Inver <objname>
class Inver
{
public:
    Inver();        /// Constructor.
    void begin();   /// Inicializacion.
    void Control(); /// LLamada de ejecuci�n.
};
#endif