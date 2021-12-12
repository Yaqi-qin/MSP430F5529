#include "driverlib.h"
#include "msp430.h"



//******************************************************************************
//定时器 TAR 的值从 TACCR0-1 计数到 TACCR0 时，中断标志 CCIFG0 置位；
//当定时器从 1 减计数到 0 时，中断标志 TAIFG 置位
//设置好时钟源和中断后，设置好TACCR0/TACCR1/TACCR2的值即可启动定时器。
//******************************************************************************

unsigned char count;

void main(void) {

    WDT_A_hold(WDT_A_BASE);
    P6DIR|=BIT1;  //仅仅当作输出口，当作捕获比较输入输出口时，要有PxSEL操作

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


