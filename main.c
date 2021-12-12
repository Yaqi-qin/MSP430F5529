#include "driverlib.h"
#include "msp430.h"



//******************************************************************************
//��ʱ�� TAR ��ֵ�� TACCR0-1 ������ TACCR0 ʱ���жϱ�־ CCIFG0 ��λ��
//����ʱ���� 1 �������� 0 ʱ���жϱ�־ TAIFG ��λ
//���ú�ʱ��Դ���жϺ����ú�TACCR0/TACCR1/TACCR2��ֵ����������ʱ����
//******************************************************************************

unsigned char count;

void main(void) {

    WDT_A_hold(WDT_A_BASE);
    P6DIR|=BIT1;  //������������ڣ���������Ƚ����������ʱ��Ҫ��PxSEL����

    TA0CTL=TASSEL__SMCLK+MC_1+TACLR;
    TA0CCTL0=CCIE;
    TA0CCR0=1000;
    count=0;

    _EINT();

    while(1)
    {
        __no_operation();
    }
}



#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    count++;
    if(count>=50)
    {
        count=0;
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,GPIO_PIN0);
    }
}

//huhu


