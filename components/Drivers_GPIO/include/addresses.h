/*****************************************************
 * FileName:        addresses.h
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 *                  PEDRO MANCINAS HERNANDEZ
 *                  RAÚL MONTES MONTES
 * Nota: La interfaz definida de este DRIVER hace uso de las estructuras
 *       declarados en gpio_config_2021.h
 *  Created on: 15 de mayo del 2024
 *  updated: 20/11/2021
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2024 by JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/

/************************************************
               GENERAL ADDRESSES
 ************************************************/
#define GPIO_HIGH      (0x01)
#define GPIO_LOW       (0x00)
#define FUN_IE         (0x200)
#define noexist        LOW

#define SEL0           (0x1000)
#define SEL1           (0x2000)
#define SEL2           (0x4000)


#define VCC 1
#define GND 0

#define R_PULL_UP   8
#define R_PULL_DOWN 7

#define MAX_VALID_PIN  39
#define MAX_OUTPUT_PIN 34

/************************************************
             DEFINITION OF VOLATILE
 ************************************************/

#define HWREG32(x)     (*((volatile uint32_t *)(x)))

/************************************************
             OUTPUT ADDRESSES
 ************************************************/

#define GPIO_OUT_REG       (HWREG32(0x3FF44004))

#define GPIO_ENABLE_REG    (HWREG32(0x3FF44020)) //GPIO 0-31 output enable register
#define GPIO_ENABLE1_REG   (HWREG32(0x3FF4402C)) //GPIO 32-39 output enable register

#define GPIO_OUT_W1TS_REG  (HWREG32(0x3FF44008))
#define GPIO_OUT_W1TC_REG  (HWREG32(0x3FF4400C))

#define GPIO_OUT1_W1TS_REG (HWREG32(0x3FF44014))
#define GPIO_OUT1_W1TC_REG (HWREG32(0x3FF44018))

#define DIR_GPIO2_BASE     0x3FF49000

/************************************************
             INPUT ADDRESSES
 ************************************************/

#define GPIO_IN_REG          HWREG32(0x3FF4403C)        //GPIO 0-31

#define GPIO_IN1_REG          HWREG32(0x3FF44040)       //GPIO 32-39


/************************************************
             INTERRUPTION ADDRESSES
 ************************************************/
              //REGISTERS OF INTERRUPTIONS 0-31

           //GPIO 0-31 input register 0x3FF4403C RO

#define GPIO_STATUS_REG      HWREG32(0x3FF44044)       //    GPIO 0-31 interrupt status register 0x3FF44044
#define GPIO_STATUS_W1TS_REG HWREG32(0x3FF44048)
#define GPIO_STATUS_W1TC_REG HWREG32(0x3FF4404C)

             //REGISTERS OF INTERRUPTIONS 31-39

#define GPIO_STATUS1_REG      HWREG32(0x3FF44050)
#define GPIO_STATUS1_W1TS_REG HWREG32(0x3FF44054)
#define GPIO_STATUS1_W1TC_REG HWREG32(0x3FF44058)


/************************************************
  IO_MUX_x_REG  ADDRESSES MAP  PINES ADDRESSES (MAP)
 ************************************************/
#define IO_0_REG  0x44
#define IO_1_REG  0x88
#define IO_2_REG  0x40
#define IO_3_REG  0x84
#define IO_4_REG  0x48
#define IO_5_REG  0x6C
#define IO_6_REG  0x60
#define IO_7_REG  0x64
#define IO_8_REG  0x68
#define IO_9_REG  0x54
#define IO_10_REG 0x58
#define IO_11_REG 0x5C
#define IO_12_REG 0x34
#define IO_13_REG 0x38
#define IO_14_REG 0x30
#define IO_15_REG 0x3C
#define IO_16_REG 0x4C
#define IO_17_REG 0x50
#define IO_18_REG 0x70
#define IO_19_REG 0x74
#define IO_20_REG 0x78
#define IO_21_REG 0x7C
#define IO_22_REG 0x80
#define IO_23_REG 0x8C
#define IO_24_REG 0x00              // DISABLED
#define IO_25_REG 0x24
#define IO_26_REG 0x28
#define IO_27_REG 0x2C
#define IO_28_REG 0x00 				// DISABLED
#define IO_29_REG 0x00              // DISABLED
#define IO_30_REG 0x00				// DISABLED
#define IO_31_REG 0x00			    // DISABLED
#define IO_32_REG 0x1C
#define IO_33_REG 0x20
 //ONLY READ
#define I_34_REG 0x14
#define I_35_REG 0x18
#define I_36_REG 0x04
#define I_37_REG 0x08
#define I_38_REG 0x0C
#define I_39_REG 0x01



/************************************************
            RTC ADDRESSES
 ************************************************/

#define RTC_0  0x01       //I_36_REG
#define RTC_1  0x01       //I_37_REG
#define RTC_2  0x01       //I_38_REG
#define RTC_3  0x01       //I_39_REG
#define RTC_4  0x01       //I_34_REG
#define RTC_5  0x01       //I_35_REG
#define RTC_6  0x01       //IO_25_REG
#define RTC_7  0x01       //IO_26_REG
#define RTC_8  0x3FF484B4 //IO_33_REG
#define RTC_9  0x3FF484B8 //IO_32_REG
#define RTC_10 0x3FF48494 //IO_4_REG
#define RTC_11 0x3FF48498 //IO_0_REG
#define RTC_12 0x3FF4849C //IO_2_REG
#define RTC_13 0x3FF484A0 //IO_15_REG
#define RTC_14 0x3FF484A4 //IO_13_REG
#define RTC_15 0x3FF484A8 //IO_12_REG
#define RTC_16 0x3FF484AC //IO_14_REG
#define RTC_17 0x3FF484B0 //IO_27_REG

#define TOUCH_RTC_0   RTC_10
#define TOUCH_RTC_1   RTC_11
#define TOUCH_RTC_2   RTC_12
#define TOUCH_RTC_3   RTC_13
#define TOUCH_RTC_4   RTC_14
#define TOUCH_RTC_5   RTC_15
#define TOUCH_RTC_6   RTC_16
#define TOUCH_RTC_7   RTC_17
#define TOUCH_RTC_8   RTC_8
#define TOUCH_RTC_9   RTC_9
