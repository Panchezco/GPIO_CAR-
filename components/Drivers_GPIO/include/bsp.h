/*****************************************************
 * FileName:        bsp.h
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 *                  PEDRO MANCINAS HERNANDEZ
 *                  RAÚL MONTES MONTES
 *  Created on: 15 de mayo del 2024
////////////////////////////////////////////////////////////////////////////////////////////////////
 * * Copyright (C) 2024 by  JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES- TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 *  JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTESy el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/

#include "addresses.h"
/************************************************
       SOURCE DEFINITIONS
************************************************/

#define HIGH  VCC
#define LOW   GND

#define RGB_HIGH  GND // REVERSE LOGIC FOR RGB
#define RGB_LOW   VCC

/************************************************
        RESISTENCES DEINITIONS
************************************************/
#define PULL_UP   R_PULL_UP
#define PULL_DOWN R_PULL_DOWN

/************************************************
      MAP OF BOARD  ESP32-PANTHER48
************************************************/

#define BTN1    18     //   0x40000 IO 18
#define BTN2    19     //   0x80000 IO 19

#define LED_1     17   // IO 17
#define LED_2     16   // IO 16
#define LED_3     4    // IO 4
#define LED_4     2    // IO 2
#define LED_B     5    // IO 5


#define RGB_RED     14 // IO 14
#define RGB_GREEN   13 // IO 12
#define RGB_BLUE    12  // IO 13


/************************************************
      MAP OF BOARD MOTORS  ESP32-PANTHER48
************************************************/ // PINES DE EJEMPLO
#define GPIO_UP 2
#define GPIO_DOWN 4
#define GPIO_UP2 16
#define GPIO_DOWN2 17
#define LED_CAR 5

/************************************************
      MAP OF BOARD IO
************************************************/

#define IO0 (0)
#define IO1 (1)
#define IO2 (2)
#define IO3 (3)
#define IO4 (4)
#define IO5 (5)
#define IO6 (6)
#define IO7 (7)
#define IO8 (8)
#define IO9 (9)
#define IO10 (10)
#define IO11 (11)
#define IO12 (12)
#define IO13 (13)
#define IO14 (14)
#define IO15 (15)
#define IO16 (16)
#define IO17 (17)
#define IO18 (18)
#define IO19 (19)
#define IO20 (20)
#define IO21 (21)
#define IO22 (22)
#define IO23 (23)
#define IO24 (24)
#define IO25 (25)
#define IO26 (26)
#define IO27 (27)
#define IO28 (28)
#define IO29 (29)
#define IO30 (30)
#define IO31 (31)
#define IO32 (32)
#define IO33 (33)
#define IO34 (34)
#define IO35 (35)
#define IO36 (36)
#define IO37 (37)
#define IO38 (38)
#define IO39 (39)

