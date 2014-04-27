#ifndef font_def_h
#define font_def_h
/*�����ң����ϵ��£���λ��ǰ*/
/*����--16*16*/
/*"Ƕ",0*/
static const U8 qian[]=
{
	0x01,0x00,0x21,0x08,0x3F,0xF8,0x00,0x00,0x24,0x40,0x24,0x40,0x7E,0x7C,0x24,0x84,
	0x25,0x28,0x3C,0x20,0x24,0x20,0x24,0x50,0x3C,0x48,0x24,0x8E,0x25,0x04,0x02,0x00	
};
/*"��",0*/
static const U8 ru[]=
{
	0x0C,0x00,0x06,0x00,0x02,0x00,0x01,0x00,0x03,0x00,0x02,0x80,0x02,0x80,0x04,0x40,
	0x04,0x20,0x08,0x20,0x08,0x10,0x10,0x08,0x20,0x0E,0x40,0x04,0x80,0x00,0x00,0x00
};
/*"ʽ",0*/
static const U8 shi[]=
{
	0x00,0xA0,0x00,0x98,0x00,0x90,0x7F,0xFC,0x00,0x80,0x00,0x80,0x00,0x80,0x3E,0x80,
	0x08,0x40,0x08,0x40,0x08,0x40,0x0B,0x20,0x1C,0x22,0x70,0x12,0x20,0x0A,0x00,0x04
};
/**************************************************************
 �(0) �(1) ��(2) Ů(3) ��(4) ��(5) ��(6) ��(7) ��(8) ��(9)
****************************************************************/
static const U8 hanzi[]=
{
0x02,0x00,0x01,0x00,0x7F,0xFE,0x44,0x24,0x18,0x10,0x60,0x4C,0x10,0x40,0x15,0xF8,
0x24,0x48,0x78,0x48,0x10,0x48,0x14,0x48,0x24,0x88,0x7C,0x88,0x05,0x50,0x02,0x20,/*"�",0*/

0x02,0x00,0x01,0x00,0x7F,0xFE,0x46,0x22,0x18,0x18,0x62,0x46,0x02,0x40,0x22,0x48,
0x12,0x50,0x0A,0x60,0x32,0x58,0xC4,0x48,0x04,0x40,0x08,0x42,0x30,0x42,0xC0,0x3E,/*"�",1*/

0x44,0x00,0x24,0x00,0x24,0x7C,0x87,0x44,0x44,0x44,0x44,0x44,0x1F,0xA8,0x24,0x28,
0x24,0x28,0x4D,0x10,0xD4,0x90,0x54,0xA8,0x64,0x4C,0x44,0x86,0x55,0x04,0x48,0x00,/*"��",2*/

0x02,0x00,0x02,0x00,0x02,0x00,0x04,0x00,0x04,0x00,0xFF,0xFE,0x08,0x20,0x08,0x20,
0x10,0x40,0x0C,0x40,0x03,0x80,0x01,0xC0,0x02,0x30,0x0C,0x18,0x30,0x0C,0xC0,0x08,/*"Ů",3*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x10,0x00,0x20,0x00,0x00,0x00,/*"��",4*/

0x00,0x00,0x3F,0xF8,0x02,0x08,0x02,0x08,0xFF,0xFE,0x04,0x08,0x04,0x08,0x3F,0xF8,
0x04,0x08,0x08,0x00,0x1F,0xF8,0x18,0x08,0x28,0x08,0x48,0x08,0x8F,0xF8,0x08,0x08,/*"��",5*/

0x00,0x00,0x3F,0xF0,0x00,0x20,0x00,0x40,0x00,0x80,0x01,0x00,0x01,0x00,0x01,0x04,
0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00,/*"��",6*/

0x10,0x00,0x11,0xFC,0x10,0x08,0x10,0x10,0xFC,0x20,0x24,0x20,0x24,0x20,0x27,0xFE,
0x44,0x20,0x64,0x20,0x18,0x20,0x08,0x20,0x14,0x20,0x26,0x20,0x44,0xA0,0x80,0x40,/*"��",7*/

0x00,0x40,0x40,0x50,0x20,0x48,0x2F,0xFE,0x00,0x40,0x04,0x48,0xE2,0x50,0x20,0xE0,
0x21,0x50,0x22,0x4C,0x2C,0x44,0x21,0x40,0x20,0x80,0x50,0x00,0x8F,0xFE,0x00,0x00,/*"��",8*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x30,0x00,0x48,0x00,0x48,0x00,0x30,0x00,0x00,0x00,0x00,0x00,/*"��",9*/
};
#endif /*font_def_h*/