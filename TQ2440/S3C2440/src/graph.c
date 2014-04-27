#include "graph.h"
#include <math.h>
/****************************************************
˵    ��:ת�����껭��
��ڲ���:(x,y)--����λ��,color--��ɫ��
���ڲ���:��
****************************************************/
void pixel(U32 x,U32 y,U32 color)
{
	U32 i,j;
// 	i=319-y;
// 	j=x;
	i=x;
	j=239-y;
	//	LCD_BUFFER[j][i] =color;
	if ( (i < SCR_XSIZE_TFT) && (j < SCR_YSIZE_TFT) )
	PutPixel(i,j,color);
} 
/****************************************************
˵    ��:������1
��ڲ���:(x,y)--���, length--����, color--��ɫ��
���ڲ���:��
****************************************************/
void draw_Hline1(U32 x,U32 y,U32 length,U16 color)
{
	U32 i;
	for(i=0;i<length;i++)
		pixel(x+i,y,color);
}
/****************************************************
˵    ��:������2
��ڲ���:x1--���x����,x2--�յ�x����,y--y����, color--��ɫ��
���ڲ���:��
****************************************************/
void draw_Hline2(U32 x1,U32 x2,U32 y,U16 color)
{
	U32 i;
	if(x1<=x2)
	{
		for(i=x1;i<=x2;i++)
			pixel(i,y,color);
	}
	else
	{
		for(i=x2;i<=x1;i++)
			pixel(i,y,color);
	}
}
/****************************************************
˵    ��:������1
��ڲ���:(x,y)--���, height--����, color--��ɫ��
���ڲ���:��
****************************************************/
void draw_Vline1(U32 x,U32 y,U32 height,U16 color)
{
	U32 i;
	for(i=0;i<height;i++)
		pixel(x,y+i,color);
}
/****************************************************
˵    ��:������2
��ڲ���:x--x����,y1--���y����,y2--�յ�y����,color--��ɫ��
���ڲ���:��
****************************************************/
void draw_Vline2(U32 x,U32 y1,U32 y2,U16 color)
{
	U32 i;
	if(y1<=y2)
	{
		for(i=y1;i<=y2;i++)
			pixel(x,i,color);
	}
	else
	{
		for(i=y2;i<=y1;i++)
			pixel(x,i,color);
	}
}
/****************************************************
˵    ��:�����ľ���
��ڲ���:(x1,y1)���½�����, (x2,y2)���Ͻ�����, color��ɫ��
���ڲ���:��
****************************************************/
void draw_rect(U32 x1,U32 y1,U32 x2,U32 y2,U16 color)
{
	draw_Vline2(x1,y1+1,y2,color);
	draw_Hline2(x1+1,x2,y2,color);
	draw_Vline2(x2,y2-1,y1,color);
	draw_Hline2(x2-1,x1,y1,color);
}
/****************************************************
˵    ��:��ʵ�ľ���
��ڲ���:(x1,y1)���½�����, (x2,y2)���Ͻ�����, color��ɫ��
���ڲ���:��
****************************************************/
void draw_FilledRect(U32 x1,U32 y1,U32 x2,U32 y2,U16 color)
{
	U32 i,j;
	for(j=y1;j<=y2;j++)
		for(i=x1;i<=x2;i++)
			pixel(i,j,color);
}
/****************************************************
˵    ��:������ֱ��
��ڲ���:(x1,y1)���, (x2,y2)�յ�, color��ɫ��
���ڲ���:��
****************************************************/ 
void draw_line(U32 x1,U32 y1,U32 x2,U32 y2,U16 color)  
{  
    U32 t;  
    int xerr=0,yerr=0,delta_x,delta_y,distance;  
    int incx,incy;  
    U32 row,col;  
    delta_x = x2-x1;//������������  
    delta_y = y2-y1;  
    col=x1;  
    row=y1;  
    if(delta_x>0) incx=1;//���õ�������  
    else   
    {  
        if(delta_x==0) incx=0;//��ֱ��  
        else {incx=-1;delta_x=-delta_x;}  
    }  
    if(delta_y>0)incy=1;  
    else  
    {  
        if(delta_y==0) incy=0;//ˮƽ��  
        else {incy=-1;delta_y=-delta_y;}  
    }  
    if(delta_x>delta_y) distance=delta_x;//ѡȡ��������������  
    else distance=delta_y;  

    for(t=0;t<=distance+1;t++)  
	{                                     //������� 
	//	PutPixel(col,row,color); 
		pixel(col,row,color); 
        xerr+=delta_x;  
        yerr+=delta_y;  
      	if(xerr>distance)  
        {  
            xerr-=distance;  
            col+=incx;  
        }  
        if(yerr>distance)  
        {  
            yerr-=distance;  
            row+=incy;  
        }  
    }  
}
/****************************************************
˵    ��:������ֱ��
��ڲ���:(x1,y1)���, (x2,y2)�յ�, color��ɫ��
���ڲ���:��
****************************************************/ 
void draw_circle(U32 x,U32 y,U32 r,U16 color)
{
	int a,b,xs,ys,xt,yt,d;
	a=r;
	b=0;
	while(a>=b)
	{
		pixel(x + a, y - b,color); // 0~1
		pixel(x - a, y - b,color); // 0~7
		pixel(x - a, y + b,color); // 4~5
	    pixel(x + a, y + b,color); // 4~3
	
	    pixel(x + b, y + a,color); // 2~3
	    pixel(x + b, y - a,color); // 2~1
	    pixel(x - b, y - a,color); // 6~7
	    pixel(x - b, y + a,color); // 6~5

		xs=a-1;ys=b+1;
		xt=a;  yt=b+1;
		d=2*(b+1)*(b+1)+a*a+(a-1)*(a-1)-2*r*r;
		if(d<0)
		{
			a=xt;b=yt;
		}
		else
		{
			a=xs;b=ys;
		}

	}
}

