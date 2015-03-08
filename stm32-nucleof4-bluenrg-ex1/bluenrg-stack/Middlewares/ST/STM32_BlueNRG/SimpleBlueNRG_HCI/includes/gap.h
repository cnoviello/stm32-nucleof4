/******************** (C) COPYRIGHT 2012 STMicroelectronics ********************
* File Name          : gap.h
* Author             : AMS - HEA&RF BU
* Version            : V1.0.0
* Date               : 19-July-2012
* Description        : Header file for BlueNRG's GAP layer. 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
#ifndef __GAP_H__
#define __GAP_H__

#include <link_layer.h>

/*----------------GAP UUIDs--------------------------*/
#define GAP_SERVICE_UUID                        (0x1800)
#define DEVICE_NAME_UUID						(0x2A00)
#define APPEARANCE_UUID							(0x2A01)
#define PERIPHERAL_PRIVACY_FLAG_UUID			(0x2A02)
#define RECONNECTION_ADDR_UUID					(0x2A03)
#define PERIPHERAL_PREFERRED_CONN_PARAMS_UUID	(0x2A04)

/*----------------Characteristic value lengths--------------*/
#define DEVICE_NAME_CHARACTERISTIC_LEN			        (8)
#define APPEARANCE_CHARACTERISTIC_LEN			        (2)
#define PERIPHERAL_PRIVACY_CHARACTERISTIC_LEN	        (1)
#define RECONNECTION_ADDR_CHARACTERISTIC_LEN			(6)
#define PERIPHERAL_PREF_CONN_PARAMS_CHARACTERISTIC_LEN	(8)

/*------------- AD types for adv data and scan response data ----------------*/

/* FLAGS AD type */
#define AD_TYPE_FLAGS							(0x01)
/* flag bits */
#define FLAG_BIT_LE_LIMITED_DISCOVERABLE_MODE	(0x01)
#define FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE	(0x02)
#define FLAG_BIT_BR_EDR_NOT_SUPPORTED			(0x04)
#define FLAG_BIT_LE_BR_EDR_CONTROLLER			(0x08)/* single device supports BR/EDR and LE controller */
#define FLAG_BIT_LE_BR_EDR_HOST					(0x10)/* single device supports BR/EDR and LE host */

/* SERVICE UUID AD types */
#define AD_TYPE_16_BIT_SERV_UUID				(0x02)
#define AD_TYPE_16_BIT_SERV_UUID_CMPLT_LIST		(0x03)
#define AD_TYPE_32_BIT_SERV_UUID				(0x04)
#define AD_TYPE_32_BIT_SERV_UUID_CMPLT_LIST		(0x05)
#define AD_TYPE_128_BIT_SERV_UUID				(0x06)
#define AD_TYPE_128_BIT_SERV_UUID_CMPLT_LIST	(0x07)

/* LOCAL NAME AD types */
#define AD_TYPE_SHORTENED_LOCAL_NAME			(0x08)
#define AD_TYPE_COMPLETE_LOCAL_NAME			    (0x09)

/* TX power level AD type*/
#define AD_TYPE_TX_POWER_LEVEL					(0x0A)

/* security manager TK value AD type */
#define AD_TYPE_SEC_MGR_TK_VALUE				(0x10)

/* security manager OOB flags */
#define AD_TYPE_SEC_MGR_OOB_FLAGS				(0x11)

/* slave connection interval AD type */
#define AD_TYPE_SLAVE_CONN_INTERVAL				(0x12)

/* service solicitation UUID list Ad types*/
#define AD_TYPE_SERV_SOLICIT_16_BIT_UUID_LIST	(0x14)
#define AD_TYPE_SERV_SOLICIT_32_BIT_UUID_LIST	(0x15)

/* service data AD type */
#define AD_TYPE_SERVICE_DATA					(0x16)	

/* manufaturer specific data AD type */
#define AD_TYPE_MANUFACTURER_SPECIFIC_DATA		(0xFF)

#define MAX_ADV_DATA_LEN						(31)

#define DEVICE_NAME_LEN			  				(7)
#define BD_ADDR_SIZE							(6)

/* privacy flag values */
#define PRIVACY_ENABLED							(0x01)
#define PRIVACY_DISABLED						(0x00)

/* conection intervals in terms of 625 micro sec */
#define DIR_CONN_ADV_INT_MIN					(0x190)/*250ms*/
#define DIR_CONN_ADV_INT_MAX					(0x320)/*500ms*/
#define UNDIR_CONN_ADV_INT_MIN					(0x800)/*1.28s*/
#define UNDIR_CONN_ADV_INT_MAX					(0x1000)/*2.56s*/
#define LIM_DISC_ADV_INT_MIN					(0x190)/*250ms*/
#define LIM_DISC_ADV_INT_MAX					(0x320)/*500ms*/
#define GEN_DISC_ADV_INT_MIN					(0x800)/*1.28s*/
#define GEN_DISC_ADV_INT_MAX					(0x1000)/*2.56s*/

/* time out values */
#define LIM_DISC_MODE_TIMEOUT					(180000)/* 180 seconds. according to the errata published */
#define PRIVATE_ADDR_INT_TIMEOUT				(900000)/* 15 minutes */


#define GAP_PERIPHERAL_ROLE						(0x01)
#define GAP_BROADCASTER_ROLE					(0x02)
#define GAP_CENTRAL_ROLE						(0x03)
#define GAP_OBSERVER_ROLE						(0x04)


#define GAP_NON_DISC_MODE						(0x01)
#define GAP_LIM_DISC_MODE						(0x02)
#define GAP_GEN_DISC_MODE						(0x04)
#define GAP_NON_CONN_MODE						(0x08)
#define GAP_DIRECT_CONN_MODE					(0x10)
#define GAP_UNDIRECTED_CONN_MODE				(0x20)

/* SECURITY MANAGER OOB FLAGS */
#define SM_OOB_FLAGS_FIELD                      (0x01)
#define SM_OOB_LE_SUPPORTED                     (0x02)
#define SM_OOB_SIMULTANEOUS_LE_BREDR            (0x04)
#define SM_OOB_ADDR_TYPE                        (0x08)

/**
 * @defgroup gap_procedure_codes GAP procedure codes
 * @brief Procedure codes for EVT_BLUE_GAP_PROCEDURE_COMPLETE event
 * and aci_gap_terminate_gap_procedure() command.
 * @{
 */
#define GAP_LIMITED_DISCOVERY_PROC                  (0x01)
#define GAP_GENERAL_DISCOVERY_PROC                  (0x02)
#define GAP_NAME_DISCOVERY_PROC                     (0x04)
#define GAP_AUTO_CONNECTION_ESTABLISHMENT_PROC      (0x08)
#define GAP_GENERAL_CONNECTION_ESTABLISHMENT_PROC   (0x10)
#define GAP_SELECTIVE_CONNECTION_ESTABLISHMENT_PROC (0x20)
#define GAP_DIRECT_CONNECTION_ESTABLISHMENT_PROC    (0x40)
/**
 * @}
 */

#endif /* __GAP_H__ */
