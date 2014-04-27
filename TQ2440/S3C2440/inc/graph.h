#ifndef graph_h
#define graph_h

#include "config.h"

/***************** ÉùÃ÷ ***************************/
void pixel(U32 x,U32 y,U32 color);
void draw_Hline1(U32 x,U32 y,U32 length,U16 color);
void draw_Vline1(U32 x,U32 y,U32 height,U16 color);
void draw_Hline2(U32 x1,U32 x2,U32 y,U16 color);
void draw_Vline2(U32 x,U32 y1,U32 y2,U16 color);
void draw_rect(U32 x1,U32 y1,U32 x2,U32 y2,U16 color);
void draw_FilledRect(U32 x1,U32 y1,U32 x2,U32 y2,U16 color);
void draw_line(U32 x1,U32 y1,U32 x2,U32 y2,U16 color);
void draw_circle(U32 x,U32 y,U32 r,U16 color);
#endif /*graph_h*/
