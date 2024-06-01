/*****************************************************
 * FileName:        gpio.h
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 *                  PEDRO MANCINAS HERNANDEZ
 *                  RAÚL MONTES MONTES
 * Nota:
 *  Created on: 15 de mayo del 2024
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2024 by JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include "bsp.h"
/************************************************
             FUCTION PROTOTYPE OF GPIO
************************************************/
extern void ini_board_GPIO();
extern void GPIO_OUT(uint_fast16_t selectedPins);
extern void GPIO_WRITTE(uint_fast16_t selectedPins, uint_fast8_t state);
extern void GPIO_INPUT(uint_fast16_t selectedPins, uint_fast16_t MODE_PULL);
extern int  GPIO_READ(uint_fast16_t selectedPins);

/************************************************
             FUCTION PROTOTYPE OF CAR
************************************************/
extern void start_CAR();

extern void MOTOR_UP();
extern void MOTOR_DOWN();
extern void MOTOR_RIGHT();
extern void MOTOR_LEFT();
extern void MOTOR_STOP();
extern void MOTOR_LED_ON();
extern void MOTOR_LED_OFF();
#endif // GPIO_H
