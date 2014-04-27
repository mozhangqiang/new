#include "graph.h"
#include <math.h>
/****************************************************
说    明:转换坐标画点
入口参数:(x,y)--画点位置,color--颜色。
出口参数:无
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
说    明:画横线1
入口参数:(x,y)--起点, length--长度, color--颜色。
出口参数:无
****************************************************/
void draw_Hline1(U32 x,U32 y,U32 length,U16 color)
{
	U32 i;
	for(i=0;i<length;i++)
		pixel(x+i,y,color);
}
/****************************************************
说    明:画横线2
入口参数:x1--起点x坐标,x2--终点x坐标,y--y坐标, color--颜色。
出口参数:无
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
说    明:画竖线1
入口参数:(x,y)--起点, height--长度, color--颜色。
出口参数:无
****************************************************/
void draw_Vline1(U32 x,U32 y,U32 height,U16 color)
{
	U32 i;
	for(i=0;i<height;i++)
		pixel(x,y+i,color);
}
/****************************************************
说    明:画竖线2
入口参数:x--x坐标,y1--起点y坐标,y2--终点y坐标,color--颜色。
出口参数:无
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
说    明:画空心矩形
入口参数:(x1,y1)左下角坐标, (x2,y2)右上角坐标, color颜色。
出口参数:无
****************************************************/
void draw_rect(U32 x1,U32 y1,U32 x2,U32 y2,U16 color)
{
	draw_Vline2(x1,y1+1,y2,color);
	draw_Hline2(x1+1,x2,y2,color);
	draw_Vline2(x2,y2-1,y1,color);
	draw_Hline2(x2-1,x1,y1,color);
}
/****************************************************
说    明:画实心矩形
入口参数:(x1,y1)左下角坐标, (x2,y2)右上角坐标, color颜色。
出口参数:无
****************************************************/
void draw_FilledRect(U32 x1,U32 y1,U32 x2,U32 y2,U16 color)
{
	U32 i,j;
	for(j=y1;j<=y2;j++)
		for(i=x1;i<=x2;i++)
			pixel(i,j,color);
}
/****************************************************
说    明:画任意直线
入口参数:(x1,y1)起点, (x2,y2)终点, color颜色。
出口参数:无
****************************************************/ 
void draw_line(U32 x1,U32 y1,U32 x2,U32 y2,U16 color)  
{  
    U32 t;  
    int xerr=0,yerr=0,delta_x,delta_y,distance;  
    int incx,incy;  
    U32 row,col;  
    delta_x = x2-x1;//计算坐标增量  
    delta_y = y2-y1;  
    col=x1;  
    row=y1;  
    if(delta_x>0) incx=1;//设置单步方向  
    else   
    {  
        if(delta_x==0) incx=0;//垂直线  
        else {incx=-1;delta_x=-delta_x;}  
    }  
    if(delta_y>0)incy=1;  
    else  
    {  
        if(delta_y==0) incy=0;//水平线  
        else {incy=-1;delta_y=-delta_y;}  
    }  
    if(delta_x>delta_y) distance=delta_x;//选取基本增量坐标轴  
    else distance=delta_y;  

    for(t=0;t<=distance+1;t++)  
	{                                     //画线输出 
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
说    明:画任意直线
入口参数:(x1,y1)起点, (x2,y2)终点, color颜色。
出口参数:无
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

