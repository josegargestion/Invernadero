/**
 * @file IHAL_Depo.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#ifndef IHAL_DEPO_H
#define IHAL_DEPO_H
#include "estructuras.h"
#include "ihal.h"
#include "IDeposito.h"
class IHAL_DEPO : public IHAL , IDeposito
{
public:
	struct IHAL_DEPO_DATA
	{
        IHAL_DATA _estadoHAL;
		bool _estadoIluminacion;
		float _estadoTemperatura;
		float _estadoHumedadAire;
		float _estadoHumedadTierra;
		Estado_HAL_Deposito _estadoDeposito;
	};
    IHAL_DATA GetEstado(IHAL_DATA set){return set;};
	virtual IHAL_DEPO_DATA GetEstado(IHAL_DEPO_DATA set) = 0;
	virtual void LLenarDeposito() = 0;
	virtual void VaciarDeposito() = 0;
	virtual Estado_HAL_Deposito GetDeposito(IHAL_DATA *PestadoDeposito) = 0;
};
#endif