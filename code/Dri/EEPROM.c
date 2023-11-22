#include "EEPROM.h"

bit EEPROM_WriteByte(u8 add, u8 *p_dat, u8 count)
{
    return IIC_WriteRegister(DEV_ADDR, add, p_dat, count);
}

bit EEPROM_ReadByte(u8 add, u8 *p_dat, u8 count)
{
    return IIC_ReadRegister(DEV_ADDR, add, p_dat, count);
}
