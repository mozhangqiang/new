/**************************************************
**	�ļ���:Time.h
**	�汾��:V 1.0
**	�ļ�˵��:��ʱ����������
***************************************************/

#ifndef TIMER_H
#define TIMER_H
void __irq Timer0_ISR(void);
void __irq Timer4_ISR(void);
void Timer0Init(void);
void time_ISRInit(void);
extern void bright(U8 dat);
#endif
