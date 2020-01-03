#ifndef __TFT_DEMO_H__
#define __TFT_DEMO_H__
#include "Rcc.h"
void Redraw_Mainmenu(void);
void Num_Test(void);
void Font_Test(void);
void Color_Test(void);
void showimage(const unsigned char *p); 
void Test_Demo(void);

/*======Myself======*/
struct Meun meun;

struct Meun
{
    uint8_t Frist_meun;
    uint8_t Second_meun;
    uint8_t Thired_meun;
};

void Init_Tft(void);
void First_Menu(void);
void Second_Menu(void);
void Thired_Meun(void);
#endif
