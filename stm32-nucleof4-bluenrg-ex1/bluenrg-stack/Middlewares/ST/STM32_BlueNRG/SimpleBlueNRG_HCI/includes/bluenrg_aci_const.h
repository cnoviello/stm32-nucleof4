/******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
* File Name          : bluenrg_aci_const.h
* Author             : AMS - AAS
* Version            : V1.0.0
* Date               : 26-Jun-2014
* Description        : Header file with ACI definitions for BlueNRG FW6.3.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifndef __BLUENRG_ACI_CONST_H_
#define __BLUENRG_ACI_CONST_H_

#include "compiler.h"
#include "link_layer.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define OCF_HAL_WRITE_CONFIG_DATA   0x000C

#define OCF_HAL_SET_TX_POWER_LEVEL          0x000F
typedef __packed struct _hal_set_tx_power_level_cp{
	uint8_t	en_high_power;
    uint8_t pa_level;
} PACKED hal_set_tx_power_level_cp;
#define HAL_SET_TX_POWER_LEVEL_CP_SIZE 2

#define OCF_HAL_DEVICE_STANDBY          0x0013

#define OCF_HAL_TONE_START                  0x0015
typedef __packed struct _hal_tone_start_cp{
	uint8_t	rf_channel;
} PACKED hal_tone_start_cp;
#define HAL_TONE_START_CP_SIZE 1

#define OCF_HAL_TONE_STOP                   0x0016

#define OCF_UPDATER_START                   0x0020
#define OCF_UPDATER_REBOOT                  0x0021

#define OCF_GET_UPDATER_VERSION                 0x0022
typedef __packed struct _get_updater_version_rp{
    uint8_t		    status;
	uint8_t		    version;
} PACKED get_updater_version_rp;
#define GET_UPDATER_VERSION_RP_SIZE 2

#define OCF_GET_UPDATER_BUFSIZE             0x0023
typedef __packed struct _get_updater_bufsize_rp{
    uint8_t		    status;
	uint8_t		    buffer_size;
} PACKED get_updater_bufsize_rp;
#define GET_UPDATER_BUFSIZE_RP_SIZE 2

#define OCF_UPDATER_ERASE_BLUE_FLAG         0x0024

#define OCF_UPDATER_RESET_BLUE_FLAG         0x0025

#define OCF_UPDATER_ERASE_SECTOR            0x0026
typedef __packed struct _updater_erase_sector_cp{
	uint32_t	address;
} PACKED updater_erase_sector_cp;
#define UPDATER_ERASE_SECTOR_CP_SIZE 4

#define OCF_UPDATER_PROG_DATA_BLOCK         0x0027
/* Variable length parameters */

#define OCF_UPDATER_READ_DATA_BLOCK         0x0028
typedef __packed struct _updater_read_data_block_cp{
	uint32_t	address;
    uint16_t    data_len;
} PACKED updater_read_data_block_cp;
#define UPDATER_READ_DATA_BLOCK_CP_SIZE 6
typedef __packed struct _updater_read_data_block_rp{
    uint8_t		    status;
	uint8_t		    data[0];
} PACKED updater_read_data_block_rp;
#define GET_UPDATER_BUFSIZE_RP_SIZE 2

#define OCF_UPDATER_CALC_CRC                0x0029
typedef __packed struct _updater_calc_crc_cp{
	uint32_t	address;
    uint8_t    num_sectors;
} PACKED updater_calc_crc_cp;
#define UPDATER_CALC_CRC_CP_SIZE 5
typedef __packed struct _updater_calc_crc_rp{
    uint8_t		    status;
	uint32_t		crc;
} PACKED updater_calc_crc_rp;
#define UPDATER_CALC_CRC_RP_SIZE 5

#define OCF_UPDATER_HW_VERSION              0x002A
typedef __packed struct _updater_hw_version_rp{
    uint8_t		    status;
	uint8_t		    version;
} PACKED updater_hw_version_rp;
#define UPDATER_HW_VERSION_RP_SIZE 2

#define OCF_GAP_SET_NON_DISCOVERABLE	    0x0081

#define OCF_GAP_SET_LIMITED_DISCOVERABLE	0x0082

#define OCF_GAP_SET_DISCOVERABLE	        0x0083

#define OCF_GAP_SET_DIRECT_CONNECTABLE      0x0084
typedef __packed struct _gap_set_direct_conectable_cp{
    uint8_t		own_bdaddr_type;
	uint8_t		direct_bdaddr_type;
    tBDAddr		direct_bdaddr;
} PACKED gap_set_direct_conectable_cp;
#define GAP_SET_DIRECT_CONNECTABLE_CP_SIZE 8

#define OCF_GAP_SET_IO_CAPABILITY      0x0085
typedef __packed struct _gap_set_io_capability_cp{
    uint8_t		io_capability;
} PACKED gap_set_io_capability_cp;
#define GAP_SET_IO_CAPABILITY_CP_SIZE 1

#define OCF_GAP_SET_AUTH_REQUIREMENT      0x0086
typedef __packed struct _gap_set_auth_requirement_cp{
    uint8_t	mitm_mode;
    uint8_t     oob_enable;
    uint8_t     oob_data[16];
    uint8_t     min_encryption_key_size;
    uint8_t     max_encryption_key_size;
    uint8_t     use_fixed_pin;
    uint32_t    fixed_pin;
    uint8_t     bonding_mode;
} PACKED gap_set_auth_requirement_cp;
#define GAP_SET_AUTH_REQUIREMENT_CP_SIZE 26

#define OCF_GAP_SET_AUTHOR_REQUIREMENT      0x0087
typedef __packed struct _gap_set_author_requirement_cp{
  uint16_t      conn_handle;
  uint8_t       authorization_enable;
} PACKED gap_set_author_requirement_cp;
#define GAP_SET_AUTHOR_REQUIREMENT_CP_SIZE 3

#define OCF_GAP_PASSKEY_RESPONSE      0x0088
typedef __packed struct _gap_passkey_response_cp{
  uint16_t conn_handle;
  uint32_t passkey;
} PACKED gap_passkey_response_cp;
#define GAP_PASSKEY_RESPONSE_CP_SIZE 6

#define OCF_GAP_AUTHORIZATION_RESPONSE      0x0089
typedef __packed struct _gap_authorization_response_cp{
  uint16_t conn_handle;
  uint8_t  authorize;
} PACKED gap_authorization_response_cp;
#define GAP_AUTHORIZATION_RESPONSE_CP_SIZE 3

#define OCF_GAP_INIT		        0x008A
typedef __packed struct _gap_init_cp{
	uint8_t	role;
} PACKED gap_init_cp;
#define GAP_INIT_CP_SIZE 1
typedef __packed struct _gap_init_rp{
    uint8_t		    status;
	uint16_t		service_handle;
    uint16_t		dev_name_char_handle;
    uint16_t		appearance_char_handle;
} PACKED gap_init_rp;
#define GAP_INIT_RP_SIZE 7

#define OCF_GAP_SET_NON_CONNECTABLE      0x008B
typedef __packed struct _gap_set_non_connectable_cp{
    uint8_t	advertising_event_type;
} PACKED gap_set_non_connectable_cp;
#define GAP_SET_NON_CONNECTABLE_CP_SIZE 1

#define OCF_GAP_SET_UNDIRECTED_CONNECTABLE      0x008C
typedef __packed struct _gap_set_undirected_connectable_cp{
    uint8_t	adv_filter_policy;
    uint8_t	own_addr_type;
} PACKED gap_set_undirected_connectable_cp;
#define GAP_SET_UNDIRECTED_CONNECTABLE_CP_SIZE 2

#define OCF_GAP_SLAVE_SECURITY_REQUEST      0x008D
typedef __packed struct _gap_slave_security_request_cp{
  uint16_t conn_handle;
  uint8_t  bonding;
  uint8_t  mitm_protection;
} PACKED gap_slave_security_request_cp;
#define GAP_SLAVE_SECURITY_REQUEST_CP_SIZE 4

#define OCF_GAP_UPDATE_ADV_DATA      0x008E

#define OCF_GAP_DELETE_AD_TYPE      0x008F
typedef __packed struct _gap_delete_ad_type_cp{
    uint8_t	ad_type;
} PACKED gap_delete_ad_type_cp;
#define GAP_DELETE_AD_TYPE_CP_SIZE 1

#define OCF_GAP_GET_SECURITY_LEVEL      0x0090
typedef __packed struct _gap_get_security_level_rp{
    uint8_t		    status;
	uint8_t		    mitm_protection;
    uint8_t		    bonding;
    uint8_t		    oob_data;
    uint8_t         passkey_required;
} PACKED gap_get_security_level_rp;
#define GAP_GET_SECURITY_LEVEL_RP_SIZE 5

#define OCF_GAP_SET_EVT_MASK      0x0091
typedef __packed struct _gap_set_evt_mask_cp{
    uint16_t	evt_mask;
} PACKED gap_set_evt_mask_cp;
#define GAP_SET_EVT_MASK_CP_SIZE 2

#define OCF_GAP_CONFIGURE_WHITELIST   0x0092

#define OCF_GAP_TERMINATE      0x0093
typedef __packed struct _gap_terminate_cp{
  uint16_t handle;
  uint8_t  reason;
} PACKED gap_terminate_cp;
#define GAP_TERMINATE_CP_SIZE 3

#define OCF_GAP_CLEAR_SECURITY_DB   0x0094

#define OCF_GAP_ALLOW_REBOND_DB     0x0095

#define OCF_GAP_START_LIMITED_DISCOVERY_PROC   0x0096
typedef __packed struct _gap_start_limited_discovery_proc_cp{
  uint16_t scanInterval;
  uint16_t scanWindow;
  uint8_t  own_address_type;
  uint8_t  filterDuplicates;
} PACKED gap_start_limited_discovery_proc_cp;
#define GAP_START_LIMITED_DISCOVERY_PROC_CP_SIZE 6

#define OCF_GAP_START_GENERAL_DISCOVERY_PROC   0x0097
typedef __packed struct _gap_start_general_discovery_proc_cp{
  uint16_t scanInterval;
  uint16_t scanWindow;
  uint8_t  own_address_type;
  uint8_t  filterDuplicates;
} PACKED gap_start_general_discovery_proc_cp;
#define GAP_START_GENERAL_DISCOVERY_PROC_CP_SIZE 6

#define OCF_GAP_START_AUTO_CONN_ESTABLISHMENT  0x0099

#define OCF_GAP_CREATE_CONNECTION      0x009C
typedef __packed struct _gap_create_connection_cp{
  uint16_t scanInterval;
  uint16_t scanWindow;
  uint8_t peer_bdaddr_type;
  tBDAddr peer_bdaddr;
  uint8_t own_bdaddr_type;
  uint16_t conn_min_interval;
  uint16_t conn_max_interval;
  uint16_t conn_latency;
  uint16_t supervision_timeout;
  uint16_t min_conn_length;
  uint16_t max_conn_length;
} PACKED gap_create_connection_cp;
#define GAP_CREATE_CONNECTION_CP_SIZE 24

#define OCF_GAP_TERMINATE_GAP_PROCEDURE      0x009D

#define OCF_GAP_SEND_PAIRING_REQUEST      0x009F
typedef __packed struct _gap_send_pairing_request_cp{
  uint16_t conn_handle;
  uint8_t force_rebond;
} PACKED gap_send_pairing_request_cp;
#define GAP_SEND_PAIRING_REQUEST_CP_SIZE 3

#define OCF_GATT_INIT		        0x0101

#define OCF_GATT_ADD_SERV		    0x0102
typedef __packed struct _gatt_add_serv_rp{
    uint8_t		    status;
	uint16_t		handle;
} PACKED gatt_add_serv_rp;
#define GATT_ADD_SERV_RP_SIZE 3

#define OCF_GATT_INCLUDE_SERV		0x0103
typedef __packed struct _gatt_include_serv_rp{
	uint8_t		    status;
    uint16_t		handle;    
} PACKED gatt_include_serv_rp;
#define GATT_INCLUDE_SERV_RP_SIZE 3

#define OCF_GATT_ADD_CHAR		    0x0104
typedef __packed struct _gatt_add_char_rp{
    uint8_t		    status;
	uint16_t		handle;
} PACKED gatt_add_char_rp;
#define GATT_ADD_CHAR_RP_SIZE 3

#define OCF_GATT_ADD_CHAR_DESC	    0x0105
typedef __packed struct _gatt_add_char_desc_rp{
    uint8_t		    status;
	uint16_t		handle;
} PACKED gatt_add_char_desc_rp;
#define GATT_ADD_CHAR_DESC_RP_SIZE 3

#define OCF_GATT_UPD_CHAR_VAL		0x0106

#define OCF_GATT_DEL_CHAR   		0x0107
typedef __packed struct _gatt_del_char_cp{
	uint16_t	service_handle;
	uint16_t	char_handle;
} PACKED gatt_del_char_cp;
#define GATT_DEL_CHAR_CP_SIZE 4

#define OCF_GATT_DEL_SERV   		0x0108
typedef __packed struct _gatt_del_serv_cp{
	uint16_t	service_handle;
} PACKED gatt_del_serv_cp;
#define GATT_DEL_SERV_CP_SIZE 2

#define OCF_GATT_DEL_INC_SERV   	0x0109
typedef __packed struct _gatt_del_inc_serv_cp{
	uint16_t	service_handle;
    uint16_t	inc_serv_handle;
} PACKED gatt_del_inc_serv_cp;
#define GATT_DEL_INC_SERV_CP_SIZE 4

#define OCF_GATT_SET_EVT_MASK      0x010A
typedef __packed struct _gatt_set_evt_mask_cp{
    uint32_t	evt_mask;
} PACKED gatt_set_evt_mask_cp;
#define GATT_SET_EVT_MASK_CP_SIZE 4

#define OCF_GATT_EXCHANGE_CONFIG      0x010B
typedef __packed struct _gatt_exchange_config_cp{
    uint16_t	conn_handle;
} PACKED gatt_exchange_config_cp;
#define GATT_EXCHANGE_CONFIG_CP_SIZE 2

#define OCF_GATT_FIND_INFO_REQ      0x010C
typedef __packed struct _gatt_find_info_req_cp{
    uint16_t	conn_handle;
    uint16_t	start_handle;
    uint16_t	end_handle;
} PACKED gatt_find_info_req_cp;
#define GATT_GATT_FIND_INFO_REQ_CP_SIZE 6

#define OCF_GATT_DISC_ALL_PRIM_SERVICES 0X0112
typedef __packed struct _gatt_disc_all_prim_serivces_cp{
  uint16_t conn_handle;
} PACKED gatt_disc_all_prim_services_cp;
#define GATT_DISC_ALL_PRIM_SERVICES_CP_SIZE 2

#define OCF_GATT_FIND_INCLUDED_SERVICES 0X0114
typedef __packed struct _gatt_disc_find_included_services_cp{
  uint16_t conn_handle;
  uint16_t start_handle;
  uint16_t end_handle;
} PACKED gatt_find_included_services_cp;
#define GATT_FIND_INCLUDED_SERVICES_CP_SIZE 6

#define OCF_GATT_DISC_ALL_CHARAC_OF_SERV 0X0115
typedef __packed struct _gatt_disc_all_charac_of_serv_cp{
  uint16_t conn_handle;
  uint16_t start_attr_handle;
  uint16_t end_attr_handle;
} PACKED gatt_disc_all_charac_of_serv_cp;
#define GATT_DISC_ALL_CHARAC_OF_SERV_CP_SIZE 6

#define OCF_GATT_DISC_CHARAC_BY_UUID 0X0116

#define OCF_GATT_DISC_ALL_CHARAC_DESCRIPTORS 0X0117
typedef __packed struct _gatt_disc_all_charac_descriptors_cp{
  uint16_t conn_handle;
  uint16_t char_val_handle;
  uint16_t char_end_handle;
} PACKED gatt_disc_all_charac_descriptors_cp;
#define GATT_DISC_ALL_CHARAC_DESCRIPTORS_CP_SIZE 6

#define OCF_GATT_READ_CHARAC_VAL   0x0118
typedef __packed struct _gatt_read_charac_val_cp{
  uint16_t conn_handle;
  uint16_t attr_handle;
} PACKED gatt_read_charac_val_cp;
#define GATT_READ_CHARAC_VAL_CP_SIZE 4

#define OCF_GATT_READ_LONG_CHARAC_VAL   0x011A
typedef __packed struct _gatt_read_long_charac_val_cp{
  uint16_t conn_handle;
  uint16_t attr_handle;
  uint16_t val_offset;
} PACKED gatt_read_long_charac_val_cp;
#define GATT_READ_LONG_CHARAC_VAL_CP_SIZE 6

#define OCF_GATT_WRITE_CHAR_VALUE   0x011C
#define OCF_GATT_WRITE_CHAR_DESCRIPTOR      0x0121

#define OCF_GATT_READ_CHAR_DESCRIPTOR       0x0122

#define OCF_GATT_WRITE_WITHOUT_RESPONSE     0x0123

#define OCF_GATT_SIGNED_WRITE_WITHOUT_RESPONSE     0x0124

#define OCF_GATT_CONFIRM_INDICATION                0x0125
typedef __packed struct _gatt_confirm_indication_cp{
	uint16_t	conn_handle;
} PACKED gatt_confirm_indication_cp;
#define GATT_CONFIRM_INDICATION_CP_SIZE 2

#define OCF_GATT_WRITE_RESPONSE                    0x0126

#define OCF_GATT_ALLOW_READ		    0x0127
typedef __packed struct _gatt_allow_read_cp{
	uint16_t	conn_handle;
} PACKED gatt_allow_read_cp;
#define GATT_ALLOW_READ_CP_SIZE 2

#define OCF_GATT_SET_DESC_VAL		0x0129

#define OCF_GATT_READ_HANDLE_VALUE      0x012A
typedef __packed struct _gatt_read_handle_val_cp{
	uint16_t	attr_handle;
} PACKED gatt_read_handle_val_cp;
#define GATT_READ_HANDLE_VALUE_CP_SIZE 2

#define OCF_L2CAP_CONN_PARAM_UPDATE_REQ  0x0181
typedef __packed struct _l2cap_conn_param_update_req_cp{
  uint16_t conn_handle;
  uint16_t interval_min;
  uint16_t interval_max;
  uint16_t slave_latency;
  uint16_t timeout_multiplier;
} PACKED l2cap_conn_param_update_req_cp;
#define L2CAP_CONN_PARAM_UPDATE_REQ_CP_SIZE 10

#define OCF_L2CAP_CONN_PARAM_UPDATE_RESP  0x0182
typedef __packed struct _l2cap_conn_param_update_resp_cp{
  uint16_t conn_handle;
  uint16_t interval_min;
  uint16_t interval_max;
  uint16_t slave_latency;
  uint16_t timeout_multiplier;
  uint8_t id;
  uint8_t accept;
} PACKED l2cap_conn_param_update_resp_cp;
#define L2CAP_CONN_PARAM_UPDATE_RESP_CP_SIZE 12

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 * @defgroup BlueNRG_Events BlueNRG events (vendor specific)
 * @{
 */

/**
 * Vendor specific event for BlueNRG.
 */
typedef __packed struct _evt_blue_aci{
  uint16_t ecode; /**< One of the BlueNRG event codes. */
  uint8_t  data[0];
} PACKED evt_blue_aci;


/**
 * @}
 */

#endif /* __BLUENRG_ACI_CONST_H_ */
