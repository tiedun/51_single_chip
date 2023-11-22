#include "IIC.h"

/**
 * @brief IIC初始化信号
 *
 */
static void IIC_Init()
{
    scl = 1;
    sda = 1;
    sda = 0;
}

/**
 * @brief IIC终止信号
 *
 */
static void IIC_Stop()
{
    scl = 1;
    sda = 0;
    sda = 1;
}

/**
 * @brief IIC向总线写一个字节，并等待从机ACK
 *
 * @param dat
 *
 * @return 0成功，1失败
 */
static bit IIC_Write(u8 dat)
{
    u8 i;
    scl = 0;
    // 发送8个bit
    for (i = 0; i < 8; i++)
    {
        if (dat & 0x80)
        {
            sda = 1;
        }
        else
        {
            sda = 0;
        }
        dat <<= 1;
        scl = 1; // 拉高scl,让从机接收sda
        scl = 0; // 占用scl,让sda允许改变
    }

    // 等待ACK回复
    sda = 1;
    scl = 1;
    i   = 0;

    while (sda)
    {
        if (++i > 200)
        {
            // 超过200循环仍然没有收到ACK
            scl = 0;
            return 1;
        }
    }

    // 正常收到ack
    scl = 0;
    return 0;
}

/**
 * @brief IIC从总线读取一个字节
 *
 * @param p_dat 要读取的数据指针
 *
 * @return 0成功，1失败
 */
static bit IIC_Read(u8 *p_dat)
{
    u8 i;
    *p_dat = 0;

    scl = 0; // 在改变sda前先确保scl为低电平
    sda = 1; // 主机释放sda,以便从机可以改变sda

    for (i = 0; i < 8; i++)
    {
        scl = 1; // 拉高scl,接收从机发来的sda
        *p_dat <<= 1;
        *p_dat |= sda;
        scl = 0; // 拉低scl,让从机可以改变sda的电平
    }

    // 回复ACK
    sda = 0;
    scl = 1;
    scl = 0;

    return 0;
}

bit IIC_ReadRegister(u8 dev_addr, u8 reg_addr, u8 *p_dat, u8 count)
{
    u8 i;
    bit status = 0;
    // 地址左移一位，预留控制位
    dev_addr <<= 1;
    IIC_Init();
    // 发送设备地址
    status |= IIC_Write(dev_addr);
    // 发送寄存器地址
    status |= IIC_Write(reg_addr);
    IIC_Init();
    // 发送要读取的设备，附加读取控制位
    status |= IIC_Write(dev_addr | 1);

    // 接收从机数据
    for (i = 0; i < count; i++)
    {
        status |= IIC_Read(p_dat + i);
    }
    IIC_Stop();
    return status;
}

bit IIC_WriteRegister(u8 dev_addr, u8 reg_addr, u8 *p_dat, u8 count)
{
    u8 i;
    bit status = 0;
    // 地址左移一位，预留控制位
    dev_addr <<= 1;
    IIC_Init();
    // 发送设备地址
    status |= IIC_Write(dev_addr);
    // 发送寄存器地址
    status |= IIC_Write(reg_addr);
    // 发送要写的数据
    for (i = 0; i < count; i++)
    {
        status |= IIC_Write(*(p_dat + i));
    }
    IIC_Stop();
    return status;
}
