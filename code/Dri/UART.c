#include "UART.h"

// 串口缓存结构体
typedef struct
{
    u8 arr[16];
    u8 start;
    u8 len;
} queue;

static queue buff;
static bit busy;

// 从缓存中读取数据
static char UART_QueueRead(queue *p_queue)
{
    u8 t_data;
    if (p_queue->len == 0)
        return 0;
    t_data = p_queue->arr[p_queue->start];
    p_queue->start++;
    p_queue->len--;
    if (p_queue->start == BUFF_LEN)
        p_queue->start = 0;
    return t_data;
}

// 向缓存中写入数据
static void UART_QueueWrite(queue *p_queue, char p_data)
{
    u8 t_pos;
    if (p_queue->len == BUFF_LEN)
        return;
    t_pos = p_queue->start + p_queue->len;
    if (t_pos >= BUFF_LEN)
    {
        t_pos -= BUFF_LEN;
    }
    p_queue->arr[t_pos] = p_data;
    ++p_queue->len;
}

void UART_Init()
{
    // 打开中断总开关和串口中断开关
    EA = 1;
    ES = 1;

    // 设置串口工作模式
    SCON = 0x50;

    // 结合计时器1设置串口工作频率
    PCON = 0x00;

    // 设置计时器1工作模式
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TR1 = 1;
    TH1 = T2TEMP;
    TL1 = T2TEMP;

    buff.start = 0;
    buff.len   = 0;
    busy       = 0;
}

void UART_Close()
{
    TR1 = 0;
    ES  = 0;
}

bit UART_Available()
{
    return buff.len > 0;
}

char UART_ReadChar()
{
    if (buff.len == 0)
    {
        return 0;
    }
    return UART_QueueRead(&buff);
}

void UART_SendChar(char ch)
{
    while (busy)
        ;
    busy = 1;
    SBUF = ch;
}

void UART_SendStr(char *str)
{
    while (*str)
    {
        UART_SendChar(*str);
        str++;
    }
}

u8 UART_ReadStr(char *str)
{
    u8 count   = 0;
    u8 t_count = 0;
    while (t_count < 50)
    {
        if (buff.len > 0)
        {
            str[count++] = UART_QueueRead(&buff);
            t_count      = 0;
        }
        else
        {
            Util_Delay10US(1);
            t_count++;
        }
    }
    str[count] = 0;

    return count;
}

void UART_ISR() interrupt 4 using 2
{
    if (RI)
    {
        UART_QueueWrite(&buff, SBUF);
        RI = 0;
    }
    if (TI)
    {
        busy = 0;
        TI   = 0;
    }
}
