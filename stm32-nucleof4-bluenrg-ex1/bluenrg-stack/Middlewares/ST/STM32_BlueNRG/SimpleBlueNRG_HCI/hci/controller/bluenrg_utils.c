
#include "hal.h"
#include "hal_types.h"
#include "ble_status.h"
#include "bluenrg_aci.h"
#include "bluenrg_utils.h"
#include "hci.h"
#include "osal.h"
#include "string.h"
//#include "SDK_EVAL_Spi_Driver.h"

#define SUPPORTED_BOOTLOADER_VERSION_MIN  3
#define SUPPORTED_BOOTLOADER_VERSION_MAX  5

#define BASE_ADDRESS 0x10010000

#define FW_OFFSET       (2*1024)  // 2 KB
#define FULL_STACK_SIZE (66*1024) // 66 KB
#define BOOTLOADER_SIZE (2*1024)  // 2 kB
#define DATA_SIZE       64        // 64 bytes
#define SECTOR_SIZE     (2*1024)  // 2 KB

// x**32 + x**26 + x**23 + x ** 22 + x**16 + x**12 + x**11 +
// x**10 + x**8 + x**7 + x**5 + x**4 + x**2 + x**1 + x**0
#define CRC_POLY        0x04C11DB7      // the poly without the x**32

#define IFR_SIZE 192
#define IFR_BASE_ADDRESS 0x10020000

typedef struct{
  uint8_t cold_ana_act_config_table[64];
}cold_table_TypeDef;

static uint32_t updater_calc_crc(const uint8_t* data, uint16_t nr_of_bytes)
{
    uint32_t i, j, a1;
    uint32_t crc, value;

    crc = 0;
    for (i = 0; i < nr_of_bytes; i += 4) {
      value = data[i]|((uint32_t)data[i+1]<<8)|((uint32_t)data[i+2]<<16)|((uint32_t)data[i+3]<<24);
      
        crc = crc ^ value;
        for (j = 0; j < 32; j ++) {
            a1 = (crc >> 31) & 0x1;
            crc = (crc << 1) ^ (a1 * CRC_POLY);
        }
    }
    return crc;
}

int program_device(const uint8_t *fw_image, uint32_t fw_size, uint8_t skip_bootloader_verif)
{
  uint8_t version;
  uint8_t verify_from_sector = 0;
  uint8_t number_sectors;
  uint8_t last_sector[SECTOR_SIZE];
  const uint8_t *last_image, *addr_image;
  uint16_t last_size;
  uint32_t address;
  uint32_t crc, crc2;
  tBleStatus ret;  
  
  BlueNRG_HW_Bootloader();
  HCI_Process();

  if(aci_get_updater_version(&version))
    return BLE_UTIL_ACI_ERROR;
  
  if(version < SUPPORTED_BOOTLOADER_VERSION_MIN || version > SUPPORTED_BOOTLOADER_VERSION_MAX)
    return BLE_UTIL_UNSUPPORTED_VERSION;
  
  if(skip_bootloader_verif){
    verify_from_sector = 1;
  }

  if (fw_size > FULL_STACK_SIZE)
    return BLE_UTIL_WRONG_IMAGE_SIZE;

  /***********************************************************************
  * Erase BLUE flag
  ************************************************************************/
  
  if(aci_erase_blue_flag()) 
    return BLE_UTIL_ACI_ERROR;
  
  /***********************************************************************
  * Erase sectors
  ************************************************************************/  
  
  for(int i = FW_OFFSET; i < FULL_STACK_SIZE; i += SECTOR_SIZE){
    ret = aci_updater_erase_sector(BASE_ADDRESS + i);
    if(ret) return BLE_UTIL_ACI_ERROR;
    HCI_Process();
  }
  
  /***********************************************************************
  * Flashing firmware
  ************************************************************************/

  /* Calculate the number of sectors necessary to contain the fw image.
     If the fw image is the bootloader we need to add a sector because 
     the flashing start with an offset of 2 KB 
  */
  number_sectors = (fw_size / SECTOR_SIZE);
  if (skip_bootloader_verif)
    number_sectors++;

  for(int i = FW_OFFSET; i < (number_sectors*SECTOR_SIZE); i += DATA_SIZE){
    /* If bootloader image we need to subtract the 2KB offset */
    if (skip_bootloader_verif)
      addr_image = fw_image + i - FW_OFFSET;
    else
      addr_image = fw_image + i;
    ret = aci_updater_program_data_block(BASE_ADDRESS+i, DATA_SIZE, addr_image);
    if(ret) return BLE_UTIL_ACI_ERROR;
    HCI_Process();
  }
  
  /* If the image is not multiple of a sector size */
  if (fw_size % SECTOR_SIZE) {
    /* If bootloader image we need to subtract the 2KB offset */
    if (skip_bootloader_verif) {
      last_image = fw_image + (number_sectors-1) * SECTOR_SIZE;
      last_size = fw_size -(number_sectors-1) * SECTOR_SIZE;
    } else {
      last_image = fw_image + number_sectors * SECTOR_SIZE;
      last_size = fw_size - number_sectors * SECTOR_SIZE;
    }
    memset(last_sector, 0xFF, SECTOR_SIZE);
    memcpy (last_sector, last_image, last_size);
    address = BASE_ADDRESS + (number_sectors * SECTOR_SIZE);
    for(int i = 0; i < SECTOR_SIZE; i += DATA_SIZE){
      ret = aci_updater_program_data_block(address+i, DATA_SIZE, last_sector+i);
      if(ret) return BLE_UTIL_ACI_ERROR;
      HCI_Process();
    }
  }

  /***********************************************************************
  * Verify firmware
  ************************************************************************/
  
  for(int i = (verify_from_sector*SECTOR_SIZE); i < (number_sectors*SECTOR_SIZE); i += SECTOR_SIZE){
    address = BASE_ADDRESS + i;
    if(aci_updater_calc_crc(address, 1, &crc))
      return BLE_UTIL_ACI_ERROR;
    
    /* If bootloader image we need to subtract the 2KB offset */
    if (skip_bootloader_verif) {
      crc2 = updater_calc_crc(fw_image+i-FW_OFFSET,SECTOR_SIZE);
    } else {
      crc2 = updater_calc_crc(fw_image+i,SECTOR_SIZE);
    }
    
    if(crc!=crc2)
      return BLE_UTIL_CRC_ERROR;

    HCI_Process();
  }

  /* If the image is not multiple of a sector size */
  if (fw_size % SECTOR_SIZE) {
    address = BASE_ADDRESS + (number_sectors*SECTOR_SIZE);
    if(aci_updater_calc_crc(address, 1, &crc))
      return BLE_UTIL_ACI_ERROR;
    
    crc2 = updater_calc_crc(last_sector,SECTOR_SIZE);
    
    if(crc!=crc2)
      return BLE_UTIL_CRC_ERROR;

    HCI_Process();

  }    
  
  if(aci_reset_blue_flag())
    return BLE_UTIL_ACI_ERROR;
  
  BlueNRG_RST();
  
  HCI_Process();

  return 0;
}

int read_IFR(uint8_t *data)
{
  uint8_t version;
  tBleStatus ret;
  
  aci_updater_start();
  if(aci_get_updater_version(&version))
    return BLE_UTIL_ACI_ERROR;
  
  if(version < SUPPORTED_BOOTLOADER_VERSION_MIN || version > SUPPORTED_BOOTLOADER_VERSION_MAX)
    return BLE_UTIL_UNSUPPORTED_VERSION;
  
  /***********************************************************************
  * Reading last 3 IFR 64-byte blocks
  ************************************************************************/
  
  for(int i = 66*1024 - 3*64; i < 66*1024; i += 64){
    ret = aci_updater_read_data_block(BASE_ADDRESS+i, 64, data);
    if(ret) return BLE_UTIL_ACI_ERROR;
  }
  
  BlueNRG_RST();

  return 0;
  
}

void parse_IFR_data_config(const uint8_t data[64], IFR_config2_TypeDef *IFR_config)
{
  IFR_config->stack_mode = data[0];
  IFR_config->slave_sca_ppm = LE_TO_HOST_16(data+28);
  IFR_config->master_sca = data[30];
  IFR_config->hs_startup_time = LE_TO_HOST_16(data+32);
  IFR_config->year = BCD_TO_INT(data[41]);
  IFR_config->month = BCD_TO_INT(data[42]);
  IFR_config->day = BCD_TO_INT(data[43]);    
}

int IFR_validate(IFR_config2_TypeDef *IFR_config)
{
  if(IFR_config->stack_mode < 1 || IFR_config->stack_mode > 3)
    return BLE_UTIL_PARSE_ERROR; // Unknown Stack Mode
  if(IFR_config->master_sca > 7)
    return BLE_UTIL_PARSE_ERROR; // Invalid Master SCA
  if(IFR_config->month > 12 || IFR_config->month < 1)
    return BLE_UTIL_PARSE_ERROR; // Invalid date
  if(IFR_config->day > 31 || IFR_config->day < 1)
    return BLE_UTIL_PARSE_ERROR; // Invalid date
  if(IFR_config->month > 12 || IFR_config->month < 1)
    return BLE_UTIL_PARSE_ERROR; // Invalid date
  
  return 0;
}

/* TODO: Function to generate data from given options. */

void change_IFR_data_config(IFR_config2_TypeDef *IFR_config, uint8_t data[64])
{
  data[0] = IFR_config->stack_mode;
  HOST_TO_LE_16(data+28, IFR_config->slave_sca_ppm);
  data[30] = IFR_config->master_sca;
  HOST_TO_LE_16(data+32, IFR_config->hs_startup_time);  
  data[41] = INT_TO_BCD(IFR_config->year);
  data[42] = INT_TO_BCD(IFR_config->month);
  data[43] = INT_TO_BCD(IFR_config->day);
}


int program_IFR(const IFR_config_TypeDef *ifr_image)
{
  uint8_t version;
  tBleStatus ret;  
  uint8_t ifr_data[2*1024];
  
  aci_updater_start();
  if(aci_get_updater_version(&version))
    return BLE_UTIL_ACI_ERROR;
  
  if(version < SUPPORTED_BOOTLOADER_VERSION_MIN || version > SUPPORTED_BOOTLOADER_VERSION_MAX)
    return BLE_UTIL_UNSUPPORTED_VERSION;
  
  /***********************************************************************
   * READ IFR data
   ************************************************************************/  
  for(int i = 0; i < (2*1024); i += 64){
    ret = aci_updater_read_data_block(IFR_BASE_ADDRESS+i, 64, ifr_data+i);
    if(ret != BLE_STATUS_SUCCESS){
      return ret;
    }
  }
  
  /***********************************************************************
  * Erase IFR sectors
  ************************************************************************/  
  ret = aci_updater_erase_sector(IFR_BASE_ADDRESS);
  if(ret != BLE_STATUS_SUCCESS) 
    return BLE_UTIL_ACI_ERROR;
  
  /***********************************************************************
  * Flashing IFR
  ************************************************************************/
  Osal_MemCpy(&ifr_data[2*1024-IFR_SIZE], ifr_image, IFR_SIZE);
  for(int i = 0; i < (2*1024); i += 64){
    ret = aci_updater_program_data_block(IFR_BASE_ADDRESS+i, 64, ifr_data+i);
    if(ret != BLE_STATUS_SUCCESS) 
      return BLE_UTIL_ACI_ERROR;
  }

  /***********************************************************************
  * Verify IFR
  ************************************************************************/  
  {
    uint8_t ifr_updated[64];
    for(int i = 0; i < (2*1024); i += 64){
      ret = aci_updater_read_data_block(IFR_BASE_ADDRESS+i, 64, ifr_updated);
      if(ret != BLE_STATUS_SUCCESS){
	return ret;
      }
      if (memcmp(ifr_updated, ifr_data+i, 64) != 0)
	return BLE_UTIL_WRONG_VERIFY;
    }
  }

  BlueNRG_RST();
    
  return 0;
}

uint8_t verify_IFR(const IFR_config_TypeDef *ifr_data)
{
  uint8_t ifr_updated[64];
  uint8_t version, ret;
    
  aci_updater_start();
  if(aci_get_updater_version(&version))
    return BLE_UTIL_ACI_ERROR;
  for(int i = 0; i < (3*64); i += 64){
    ret = aci_updater_read_data_block((IFR_BASE_ADDRESS+2048-IFR_SIZE)+i, 64, ifr_updated);
    if(ret != BLE_STATUS_SUCCESS){
      return ret;
    }
    if (memcmp(ifr_updated, ((uint8_t*)ifr_data)+i, 64) != 0)
      return BLE_UTIL_WRONG_VERIFY;
  }

  BlueNRG_RST();
  
  return 0;
}

uint8_t getBlueNRGVersion(uint8_t *hwVersion, uint16_t *fwVersion)
{
  uint8_t status;
  uint8_t hci_version, lmp_pal_version;
  uint16_t hci_revision, manufacturer_name, lmp_pal_subversion;

  status = hci_le_read_local_version(&hci_version, &hci_revision, &lmp_pal_version, 
				     &manufacturer_name, &lmp_pal_subversion);

  if (status == BLE_STATUS_SUCCESS) {
    *hwVersion = hci_revision >> 8;
    *fwVersion = (hci_revision & 0xFF) << 8;              // Major Version Number
    *fwVersion |= ((lmp_pal_subversion >> 4) & 0xF) << 4; // Minor Version Number
    *fwVersion |= lmp_pal_subversion & 0xF;               // Patch Version Number
  }

  HCI_Process();

  return status;
}

uint8_t getBlueNRGUpdaterVersion(uint8_t *version)
{
  HCI_Process();

  BlueNRG_HW_Bootloader();

  HCI_Process();

  if(aci_get_updater_version(version))
    return BLE_UTIL_ACI_ERROR;
  
  if(*version < SUPPORTED_BOOTLOADER_VERSION_MIN || *version > SUPPORTED_BOOTLOADER_VERSION_MAX)
    return BLE_UTIL_UNSUPPORTED_VERSION;

  BlueNRG_RST();

  HCI_Process();

  return BLE_STATUS_SUCCESS;
}
