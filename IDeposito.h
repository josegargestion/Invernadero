/**
 * @file IDeposito.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Interfaz minima de un deposito de liquidos.
 * @version 0.1
 * @date 2022-09-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef IDEPOSITO_H
#define IDEPOSITO_H
#include "estructuras.h"
class IDeposito
{
public:
    /**
     * @brief Variable que contendra los datos de configuracion.
     *
     */
    Estado_HAL_Deposito _estadoDeposito;
    /**
     * @brief Enciende o apaga el sistema de vaciado del deposito.
     *
     * @param estado ON = encendio , OFF = apagado.
     */
    virtual void Vaciado(bool estado) = 0;
    /**
     * @brief Enciende o apaga el sistema de llenado del deposito.
     *
     * @param estado ON = encendido , OFF = apagado.
     */
    virtual void LLenado(bool estado) = 0;
    virtual Estado_HAL_Deposito UpdateEstado() = 0;
    /**
     * @brief Construct a new Deposito:: Deposito object
     *
     */
    virtual void Deposito() = 0;
    /**
     * @brief Inicializador del hardware.
     *
     */
    virtual void begin() = 0;
    /**
     * @brief Control automatico del deposito.
     *
     */
    virtual void Control() = 0;
};
#endif