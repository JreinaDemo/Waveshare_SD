/**************************************************************************************************/
/** @file     main.c
 *  @brief    03_SD_Test example
 *  @details  x
 *
 *  @author   Justin Reina, Firmware Engineer
 *  @created  3/21/25
 *  @last rev 3/21/25
 *
 *  @section    Opens
 *      none current
 *
 *  @section    Legal Disclaimer
 *      ©2025 Justin Reina. All rights reserved. All contents of this source file and/or any other
 *      related source files are the explicit property of Justin Reina. Do not distribute.
 *      Do not copy.
 */
/**************************************************************************************************/

//************************************************************************************************//
//                                            INCLUDES                                            //
//************************************************************************************************//

//Project Includes
#include "sd_card.h"

//************************************************************************************************//
//                                          PUBLIC FUNCTIONS                                      //
//************************************************************************************************//

/**************************************************************************************************/
/** @fcn        void app_main(void)
 *  @brief      SD card and FAT filesystem example
 *  @details    This example uses SPI peripheral to communicate with SD card
 *
 *  @section    Purpose
 *		This example code is in the Public Domain (or CC0 licensed, at your option)
 *
 *		Unless required by applicable law or agreed to in writing, this software is distributed on 
 *		an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied
 */
/**************************************************************************************************/
void app_main(void) {
	
	//Locals
	esp_err_t stat;									/* sdk status response 						  */
	
	
    //------------------------------------ Initialize SD card ------------------------------------// 
    stat = waveshare_sd_card_init();
    
    //Safety
    if(stat!= ESP_OK) {
		return;
	}
    
    //-------------------------------- Test SD card functionality --------------------------------// 
    stat = waveshare_sd_card_test();

    
	return;
}

