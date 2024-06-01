/*****************************************************
 * FileName:        gpio.c
 * Dependencies:
 * Processor:       ESP32
 * Board:           ESP32-PANTHER48
 * Program version: Espressif-IDE
 * Company:         TecNM /IT Chihuahua
 * Description:     PROTOTIPOS DE FUNCIONES DEL DRIVER
 * Authors:         JORGE GABRIEL LOZANO RODRIGUEZ
 *                  PEDRO MANCINAS HERNANDEZ
 *  Created on: 15 de mayo del 2024
 **************************************************/
/************************************************************************************************
 * * Copyright (C) 2024 by JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 *  JORGE GABRIEL LOZANO RODRIGUEZ,PEDRO MANCINAS HERNANDEZ, RAÚL MONTES MONTES  y el TecNM /IT Chihuahua no son responsables del mal uso de este material.*/
#include "addresses.h"
#include "gpio.h"
#include "bsp.h"
/************************************************
            IO_MUX_x_REG  ADDRESSES MAP
************************************************/

volatile uint32_t GPIO_PINX_REG[] = {
		IO_0_REG,
		IO_1_REG,
		IO_2_REG,
		IO_3_REG,
		IO_4_REG,
		IO_5_REG,
		IO_6_REG,
		IO_7_REG,
		IO_8_REG,
		IO_9_REG,
		IO_10_REG,
		IO_11_REG,
		IO_12_REG,
		IO_13_REG,
		IO_14_REG,
		IO_15_REG,
		IO_16_REG,
		IO_17_REG,
		IO_18_REG,
		IO_19_REG,
		IO_20_REG,
		IO_21_REG,
		IO_22_REG,
		IO_23_REG,
		0x00,
		IO_25_REG,
		IO_26_REG,
		IO_27_REG,
		0x00,
		0x00,
		0x00,
		0x00,
		IO_32_REG,
		IO_33_REG,
		I_34_REG,
		I_35_REG,
		I_36_REG,
		I_37_REG,
		I_38_REG,
		I_39_REG,
};


/******************************************************************************
 * Function: GPIO_Out
 * Preconditions:
 * Overview: sets the pin as out
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
extern void GPIO_OUT(uint_fast16_t selectedPins)
{
    uint_fast16_t inputPinValue_withoffsett;

    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0 || selectedPins > MAX_OUTPUT_PIN){
    printf("Error el pin %d no disponible.",selectedPins);
    exit(1);
    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE +  GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

     HWREG32( inputPinValue_withoffsett) &= ~(1<<9);     /*Disable fun_IE*/

    //                                            | SEL0 || SEL1|| SEL2 |
    // FUNCION 2 GPIO                                 0      1       0
    HWREG32( inputPinValue_withoffsett) &= ~(1<<12); //2'12
    HWREG32( inputPinValue_withoffsett) |= (1<<13); //2'13
    HWREG32( inputPinValue_withoffsett) &= ~(1<<14);// 2'14

    switch (selectedPins) {
        case 32:
        case 33:
        	GPIO_ENABLE1_REG |= (1 << (selectedPins - 32));// se restan 32 poeque estamos usando un registro diferente y empieza donde termina  GPIO_ENABLE_REG
            break;
        default:
        	 GPIO_ENABLE_REG  |= 1 << selectedPins;
            break;
    }

}

/******************************************************************************
 * Function: GPIO_WRITE
 * Preconditions:   GPIO_Out_pin
 * Overview: sets the pin 1 or 0
 * Input: Pin(x).
 * Output: GND
 *
 *****************************************************************************/
extern void  GPIO_WRITTE(uint_fast16_t selectedPins, uint_fast8_t state){


	if(state==HIGH)
	{
		switch (selectedPins) {
		        case 32:
		        case 33:
		        	GPIO_OUT1_W1TS_REG  |= (1 << (selectedPins- 32));
		            break;
		        default:
		        	GPIO_OUT_W1TS_REG |= 1<<selectedPins;
		            break;
		    }
	}

    if(state==LOW)
	{
		switch (selectedPins) {
				        case 32:
				        case 33:
				        	GPIO_OUT1_W1TC_REG  |= (1 << (selectedPins- 32));// se restan 32 poeque estamos usando un registro diferente y empieza donde termina  GPIO_ENABLE_REG
				            break;
				        default:
				        	GPIO_OUT_W1TC_REG |= 1<<selectedPins;
				            break;
				    }
	}
}

/******************************************************************************
 * Function: GPIO_INPUT
 * Preconditions:
 * Overview: sets the pin as input
 * Input: Pin(x) and set pull-up or pull-down.
 * Output: GND
 *
 *****************************************************************************/
extern void GPIO_INPUT(uint_fast16_t selectedPins, uint_fast16_t MODE_PULL)
{

	uint_fast16_t inputPinValue_withoffsett;


    if( selectedPins > MAX_VALID_PIN || GPIO_PINX_REG[selectedPins] == 0){   // Las IO arriba de 34 son solo para entadas
    printf("Error el pin %d no disponible.",selectedPins);
    exit(1);
    }

    inputPinValue_withoffsett = DIR_GPIO2_BASE + GPIO_PINX_REG[selectedPins]; //Obtenemos el alias de el reg

    /*DESACTIVAMOS EL PIN COMO SALIDA*/
    if(selectedPins>=32 && selectedPins<=39){
    GPIO_ENABLE1_REG &= ~(1<<(selectedPins-32));
    }
    else
    GPIO_ENABLE_REG &= ~(1<<selectedPins);

     HWREG32(inputPinValue_withoffsett) |= (1<<9);     /*Activamos fun_IE*/
    //                                            | SEL0 || SEL1|| SEL2 |
      // FUNCION 2 GPIO                                 0      1       0
      HWREG32( inputPinValue_withoffsett) &= ~(1<<12); //2'12
      HWREG32( inputPinValue_withoffsett) |= (1<<13); //2'13
      HWREG32( inputPinValue_withoffsett) &= ~(1<<14);// 2'14

    if(MODE_PULL == PULL_UP)
    {
    	HWREG32( inputPinValue_withoffsett) |= (1<<PULL_UP);
    	HWREG32( inputPinValue_withoffsett) &= ~(1<<PULL_DOWN);
    }

    if(MODE_PULL == PULL_DOWN)
	{
    	HWREG32(inputPinValue_withoffsett) |=(1<<PULL_DOWN);
    	HWREG32(inputPinValue_withoffsett) &= ~(1<<PULL_UP);

	}
}

/******************************************************************************
 * Function: GPIO_READ
 * Preconditions: GPIO_Out_pin
 * Overview: read the pin as input
 * Input: Pin(x) and set pull-up or pull-down.
 * Output: GND
 *
 *****************************************************************************/
extern int GPIO_READ(uint_fast16_t selectedPins)
{
    // Check if the selected pin is in the range of 32 to 39
    if (selectedPins >= 32 && selectedPins <= 39)
    {
        // Read the state of the corresponding pin in the GPIO_IN1_REG register
        // Subtract 32 because GPIO_IN1_REG handles pins 32 to 39
        if (GPIO_IN1_REG & (1 << (selectedPins - 32)))
        {
            // If the corresponding bit is 1, return 1
            return 1;
        }
        else
        {
            // If the corresponding bit is 0, return 0
            return 0;
        }
    }
    else
    {
        // For pins outside the range 32 to 39, read the state of the pin in the GPIO_IN_REG register
        if (GPIO_IN_REG & (1 << selectedPins))
        {
            // If the corresponding bit is 1, return 1
            return 1;
        }
        else
        {
            // If the corresponding bit is 0, return 0
            return 0;
        }
    }
}


/******************************************************************************
 * Function:  ini_board_GPIO
 * Preconditions: NONE
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void ini_board_GPIO()
{
	 GPIO_INPUT(BTN1,PULL_UP); //BTN1 AND BTN2 HAVE ONLY PULL-UP
	 GPIO_INPUT(BTN2,PULL_UP);
	 GPIO_INPUT(25,PULL_UP);

	 GPIO_OUT(RGB_RED);
	 GPIO_OUT(RGB_BLUE);
	 GPIO_OUT(RGB_GREEN);

	 GPIO_OUT(LED_B);

}
/******************************************************************************
 * Function: start_CAR
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void start_CAR()
{

	 GPIO_OUT(GPIO_UP);
	 GPIO_OUT(GPIO_DOWN);
	 GPIO_OUT(GPIO_DOWN2);
	 GPIO_OUT(GPIO_UP2);
	 GPIO_OUT(LED_CAR);

}

/******************************************************************************
 * Function:  MOTOR_UP
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void MOTOR_UP()
{

	GPIO_WRITTE(GPIO_UP2,HIGH);
   	GPIO_WRITTE(GPIO_DOWN2,LOW);
 	GPIO_WRITTE(GPIO_UP,HIGH);
	GPIO_WRITTE(GPIO_DOWN,LOW);

}

/******************************************************************************
 * Function: MOTOR_DOWN
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_DOWN()
{

	GPIO_WRITTE(GPIO_UP2,LOW);
   	GPIO_WRITTE(GPIO_DOWN2,HIGH);
    GPIO_WRITTE(GPIO_UP,LOW);
    GPIO_WRITTE(GPIO_DOWN,HIGH);

}

/******************************************************************************
 * Function:  MOTOR_LEFT
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_LEFT()
{

	GPIO_WRITTE(GPIO_UP2,LOW);
   	GPIO_WRITTE(GPIO_DOWN2,LOW);
    GPIO_WRITTE(GPIO_UP,HIGH);
    GPIO_WRITTE(GPIO_DOWN,LOW);

}

/******************************************************************************
 * Function:  MOTOR_RIGHT
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_RIGHT()
{

	GPIO_WRITTE(GPIO_UP2,HIGH);
 	GPIO_WRITTE(GPIO_DOWN2,LOW);
    GPIO_WRITTE(GPIO_UP,LOW);
    GPIO_WRITTE(GPIO_DOWN,LOW);

}

/******************************************************************************
 * Function:  MOTOR_STOP
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_STOP()
{

	GPIO_WRITTE(GPIO_UP2,LOW);
 	GPIO_WRITTE(GPIO_DOWN2,LOW);
    GPIO_WRITTE(GPIO_UP,LOW);
    GPIO_WRITTE(GPIO_DOWN,LOW);

}
/******************************************************************************
 * Function:  MOTOR_LED_ON
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_LED_ON()
{

	GPIO_WRITTE(LED_CAR,HIGH);

}


/******************************************************************************
 * Function:  MOTOR_LED_OFF
 * Preconditions: SET: GPIO_UP2,GPIO_UP,GPIO_DOWN,GPIO_DOWN2.
 * Overview: start peripherals
 * Input: NONE
 * Output: start peripherals board
 *
 *****************************************************************************/
extern void  MOTOR_LED_OFF()
{

	GPIO_WRITTE(LED_CAR,LOW);

}


