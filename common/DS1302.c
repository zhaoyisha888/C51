#include <REGX52.H>

//д��ַ��д�ĵ�ַ����0x01���Ƕ��ĵ�ַ
#define DS1302_SECOND          0x80
#define DS1302_MINUTE          0x82
#define DS1302_HOUR            0x84
#define DS1302_DATE            0x86
#define DS1302_MONTH           0x88
#define DS1302_WEEK            0x8A
#define DS1302_YEAR            0x8C
#define DS1302_CONTROL         0x8E

sbit DS1302_SCLK = P3^6;
sbit DS1302_CE = P3^5;
sbit DS1302_IO = P3^4;


char DS1302_Time[] = {02,8,1,9,30,23,4};


/**
 * @brief DS1302��ʼ��
 * @param ��
 * @retval ��
 */                               
void DS1302_Init(void)
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}


/**
 * @brief ��DS1302д��һ���ֽ�
 * @param Command Ҫд����ֽڵĵ�ַ
 * @param Data Ҫд����ֽ�
 * @retval ��
 */
void DS1302_WriteByte(unsigned char Command,unsigned char Data)
{ 
    unsigned int i;

    DS1302_CE = 1;

    for(i = 0;i < 8;i ++)
    {
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }

    for(i = 0;i < 8;i ++)
    {
        DS1302_IO = Data & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    DS1302_CE = 0;
}


/**
 * @brief ��DS1302��ȡһ���ֽ�
 * @param Command Ҫ��ȡ���ֽڵĵ�ַ
 * @retval ��ȡ�����ֽ�
 */
unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned int i,Data = 0x00;
    Command |= 0x01;
    DS1302_CE = 1;

    for(i = 0;i < 8;i ++)
    {
        DS1302_IO = Command &(0x01 << i);
        DS1302_SCLK = 0;
        DS1302_SCLK = 1;
    }
	
    for(i = 0;i < 8;i ++)
    {
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
        if(DS1302_IO)
        {
            Data |= (0x01 << i);
        }
    }
    DS1302_CE = 0;  
	DS1302_IO = 0;
    return Data;
}


/**
 * @brief DS1302����ʱ��
 * @note ���ｫ�����е�ʮ��������ת��ΪBCD��д��DS1302
 * @param ��
 * @retval ��
 */
void DS1302_SetTime(void)
{
    //�ر�д����
    DS1302_WriteByte(DS1302_CONTROL,0x00);
    
    DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
    DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
    DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
    DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
    DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
    DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
    DS1302_WriteByte(DS1302_WEEK,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
}


/**
 * @brief DS1302��ȡʱ��
 * @note ���ｫDS1302�е�BCD�룬ת��Ϊʮ������������
 * @param ��
 * @retval ��
 */
void DS1302_ReadTime(void)
{
    unsigned char temp;

    temp = DS1302_ReadByte(DS1302_YEAR);
    DS1302_Time[0] = temp/16*10+temp%16;

    temp = DS1302_ReadByte(DS1302_MONTH);
    DS1302_Time[1] = temp/16*10+temp%16;

    temp = DS1302_ReadByte(DS1302_DATE);
    DS1302_Time[2] = temp/16*10+temp%16;

    temp = DS1302_ReadByte(DS1302_HOUR);
    DS1302_Time[3] = temp/16*10+temp%16;

    temp = DS1302_ReadByte(DS1302_MINUTE);
    DS1302_Time[4] = temp/16*10+temp%16;

    temp = DS1302_ReadByte(DS1302_SECOND);
    DS1302_Time[5] = temp/16*10+temp%16;

    temp = DS1302_ReadByte(DS1302_WEEK);
    DS1302_Time[6] = temp/16*10+temp%16;
    
}