/**
  ******************************************************************************
  * @file    stm32xx_lpm.h
  * @author  MCD Application Team
  * @version V1.0
  * @date    14-April-2014
  * @cond DOXYGEN_EXCLUDE
  * @brief   Header for stm32l1xx_lpm.c module
  * @endcond
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#ifndef __STM32xx_LPM_H
#define __STM32xx_LPM_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
#include "stm32xx_lpm_conf.h"

 /* Exported types ------------------------------------------------------------*/

 /**
  * MCU Low Power Mode supported
  */
typedef enum
{
	eLPM_Mode_Sleep		= 0x00,	/**< DEEPSLEEP=0, LPSDR=0, PDDS=0	*/
	eLPM_Mode_Stop		= 0x04,	/**< DEEPSLEEP=1, LPSDR=0, PDDS=0	*/
	eLPM_Mode_LP_Stop	= 0x06,	/**< DEEPSLEEP=1, LPSDR=1, PDDS=0	*/
	eLPM_Mode_StandBy	= 0x07,	/**< DEEPSLEEP=1, LPSDR=1, PDDS=1	*/
	eLPM_Mode_RUN		= 0x08
} eLPM_Mode;

/*
 * Supported requester to the MCU Low Power Manager - can be increased up  to 32
 */
typedef enum
{
    eLPM_MAIN_LOOP_PROCESSES,
	eLPM_Id_UART_Tx,
	eLPM_Id_UART_Rx,
	eLPM_Application,
	eLPM_ADC_Temp_Measurement,
	eLPM_NVM
} eLPM_Id;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int LPM_Mode_isRunning(eLPM_Id eId);
void LPM_Mode_Request_mask(uint32_t eMask, eLPM_Mode eMode);
void LPM_Mode_Request(eLPM_Id eId, eLPM_Mode eMode);
void LPM_Enter_Mode(void);
void LPM_EnterStopMode(void);
void LPM_ExitStopMode(void);
void LPM_EnterStandbyMode(void);
void LPM_ExitStandbyMode(void);

/* Compiler specific definition ------------------------------------------------------- */

 /*
  * Define the No OPeration intrinsinc
  */
#if defined ( __CC_ARM )
#define NOP __nop()
#define WEAK __weak
#elif defined ( __ICCARM__ )
#define NOP __NOP()
#define WEAK __weak
#elif defined ( __GNUC__ )
#define NOP __NOP()
#define WEAK __attribute__((weak))
#endif


#ifdef __cplusplus
}
#endif

#endif /* __STM32xx_LPM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
