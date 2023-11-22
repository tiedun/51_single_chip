#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "IIC.h"
#include "../Com/Util.h"

// ���յ�·��EEPROM��ַӦΪ0b1010000������Ϊ16����Ϊ0x50
#define DEV_ADDR 0x50

/**
 * @brief ��EEPROMָ����ַд���ֽ�
 *
 * @param add ָ����ַ
 * @param p_dat Ҫд�������ָ��
 * @param count Ҫд������ݳ���
 * @return 0 �ɹ� 1 ʧ��
 */
bit EEPROM_WriteByte(u8 add, u8 *p_dat, u8 count);

/**
 * @brief ��ָ����ַ��������
 *
 * @param add ָ����ַ
 * @param P_dat ��ȡ���ݻ�����ָ��
 * @param count ��ȡ���ݳ���
 * @return 0 �ɹ� 1 ʧ��
 */
bit EEPROM_ReadByte(u8 add, u8 *p_dat, u8 count);

#endif