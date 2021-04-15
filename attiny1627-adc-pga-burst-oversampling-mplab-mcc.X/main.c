/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
#include "mcc_generated_files/system/system.h"
#include <avr/io.h>

/* Defines to configure ADC accumulation */
#define DISCARDED_LSBS       5 /* 5 bits extra */
#define OVERSAMPLING_MAX_VALUE  ((uint32_t) ((1 << 12) - 1) << DISCARDED_LSBS) /* 12 + 5 bits = 17 bits */

/* Volatile variables to improve debug experience */
static volatile uint32_t adc_reading;
static volatile float voltage;

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    while(1)
    {
		/* Oversampling compensation as explained in the tech brief */
		adc_reading = ADC0_GetDiffConversion(false, ADC_MUXPOS_AIN6_gc, ADC_MUXNEG_GND_gc) >> DISCARDED_LSBS; /* Scale accumulated result by right shifting the number of extra bits */
		voltage = (float)((adc_reading * 3.3) / OVERSAMPLING_MAX_VALUE); /* Calculate voltage using 17-bit resolution, VDD = 3.3V */
    }    
}