#include <REGX52.H>

/**
 * @brief ��ʼ������
 * @param ��
 * @retval ��
 */
void UART_Init()	    //4800bps@11.0592MHz
{
    PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x40;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFA;			//���ö�ʱ��ʼֵ
	TH1 = 0xFA;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ

}

/**
 * @brief ���ڷ���һ���ֽ�����
 * @param Byte Ҫ���͵�һ���ֽ�����
 * @retval ��
 */
void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte;
    while(TI == 0);     //��⵽���ݣ�TI��1��������
	TI = 0;             //�����λTI
}