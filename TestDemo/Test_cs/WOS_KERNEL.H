/******************************************************************************/
/*�ӿ�˵��:
/*----------------------------------------------------------------------------*/
/*MacroDefs:
/*	SysDef_WatchDogFeed()					/*��:���Ź���λ*/
/*Functions:
/*	void Sys_WatchDogReset();				/*:���Ź���λ*/
/*	void Sys_To_FeedWatchDog();				/*�������Ź�ι��*/
/*
/*	void Sys_Halt();						/*ϵͳֹͣ���ȴ�Ӳ����λ*/
/*	void Sys_InitReg();						/*ϵͳ�Ĵ�����ʼ��*/
/*	long Sys_GetSysTickCounter();		          	/*ϵͳ��ȡϵͳ�ܼ�����*/
/*	long Sys_GetPassedSysTicks(long pValue);                /*ϵͳ����ϵͳ����ʱ��*/
/*	void Sys_DelayNms(Word N);				/*ϵͳN������ʱ(0..30000)*/
/******************************************************************************/
#ifndef _UWOSKERNELH_
#define _UWOSKERNELH_

#include "WOS_WTYPE.H"

extern void WOS_Halt();
extern void WOS_InitReg();

extern long  WOS_GetSysTickCounter();
extern short WOS_GetSysTickCounter_Int16();
extern long  WOS_GetPassedSysTicks(long pValue);
extern short WOS_GetPassedSysTicks_Int16(short pValue);

extern void WOS_SetDalayWatchDogProc(TFarProc pWatchDogProc);
extern void WOS_DelayN100us(Word N);
extern void WOS_DelayNms(Word N);

#endif

//Begin********External Variable 
//End**********External Variable

//Begin********Internal Variable 
//End**********Internal Variable
