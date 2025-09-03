#include <REGX52.H>

/**
 * @brief ��ʼ������
 * @param ��
 * @retval ��
 */
void UART_Init()	    //4800bps@11.0592MHz
{
    PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//������գ�0x40ֻ���Ͳ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFA;			//���ö�ʱ��ʼֵ
	TH1 = 0xFA;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
    EA = 1;             //����ʱ���������жϣ������Ϳ�ע��
    ES = 1;             //����ʱ���������жϣ������Ϳ�ע��
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

/**
 * @brief �����жϷ�����
 * @param ��
 * @retval ��
 */
// void UART_Routine()  interrupt 4
// {
// 	if(RI == 1)         //���ͺͽ��ն��ᴥ���жϣ��������жϽ����ж�
// 	{
//         /*
//         code        
//         */
// 		RI = 0;
// 	}
// }