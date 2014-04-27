#ifndef _RADIO_API_H_
#define _RADIO_API_H_
/*********************************************************/

void delay_us(UINT16 us);
void delay_ms(UINT16 ms);
void tuner_mute(unsigned char mute);
void Set_FM_StereoMono(void);
void BK1086_POWER(UINT8 dir);
unsigned int BK1086_FreqToChan(unsigned int frequency);
void BK1086_SetFreq( unsigned int curFreq );
unsigned char BK1086_ValidStop(UINT16 freq);
void Tuner_Init(void);
void Radio_Reg_Read(UINT8 reg,UINT8 *pBuf,UINT8 len);
void Radio_Reg_Write(UINT8 reg,UINT8 *pBuf,UINT8 len);
void BK1086_SetVolumeLevel(unsigned char level);
#endif //_RADIO_API_H_


