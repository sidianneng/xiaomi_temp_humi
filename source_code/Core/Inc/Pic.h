#ifndef _PIC_H_
#define _PIC_H_

const unsigned char gImage_2424_bt[72] = { /* 0X01,0X01,0X18,0X00,0X18,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0X00,0XC0,0X01,0X81,0X80,0X00,0XC3,0X00,0X00,0X66,0X00,0X00,0X3C,0X00,0X00,0X18,
0X00,0X7F,0XFF,0XFE,0XFF,0XFF,0XFF,0XC0,0X3C,0X03,0X60,0X66,0X06,0X30,0XC3,0X0C,
0X19,0X81,0X98,0X0F,0X00,0XF0,0X06,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

const unsigned char gImage_2424_nobt[72] = { /* 0X01,0X01,0X18,0X00,0X18,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

const unsigned char gImage_2424_bat[72] = { /* 0X01,0X01,0X18,0X00,0X18,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0X00,0X00,0XFE,0X00,0X07,0XFF,0XC0,0X04,
0X00,0X40,0X04,0X00,0X40,0X04,0X00,0X40,0X04,0X00,0X40,0X04,0X00,0X40,0X04,0X00,
0X40,0X04,0X00,0X40,0X04,0X00,0X40,0X04,0X00,0X40,0X04,0X00,0X40,0X04,0X00,0X40,
0X04,0X00,0X40,0X05,0XFF,0X40,0X05,0XFF,0X40,0X05,0XFF,0X40,0X04,0X00,0X40,0X07,
0XFF,0XC0,0X03,0XFF,0X80,0X00,0X00,0X00,};

const unsigned char gImage_2424_nobat[72] = { /* 0X01,0X01,0X18,0X00,0X18,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

const unsigned char gImage_2464_colon[192] = { /* 0X01,0X01,0X18,0X00,0X40,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XE0,0X00,0XFE,0X00,0X00,
0X00,0X00,0X0F,0XF0,0X01,0XFF,0X00,0X00,0X00,0X00,0X0F,0XF0,0X01,0XFF,0X00,0X00,
0X00,0X00,0X0F,0XF0,0X01,0XFF,0X00,0X00,0X00,0X00,0X0F,0XF0,0X01,0XFF,0X00,0X00,
0X00,0X00,0X0F,0XF0,0X01,0XFF,0X00,0X00,0X00,0X00,0X0F,0XF0,0X01,0XFF,0X00,0X00,
0X00,0X00,0X07,0XE0,0X00,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_1224_c[36] = { /* 0X01,0X01,0X0C,0X00,0X18,0X00, */
0X00,0X30,0X00,0X00,0X30,0X00,0X00,0X00,0X00,0X00,0X1F,0XE0,0X00,0X3F,0XF8,0X00,
0X60,0X18,0X00,0X60,0X18,0X00,0X60,0X18,0X00,0X60,0X18,0X00,0X60,0X18,0X00,0X60,
0X18,0X00,0X30,0X30,};

const unsigned char gImage_1224_f[36] = { /* 0X01,0X01,0X0C,0X00,0X18,0X00, */
0X00,0X30,0X00,0X00,0X30,0X00,0X00,0X00,0X00,0X00,0X7F,0XF8,0X00,0X7F,0XF8,0X00,
0X63,0X00,0X00,0X63,0X00,0X00,0X63,0X00,0X00,0X63,0X00,0X00,0X63,0X00,0X00,0X60,
0X00,0X00,0X00,0X00,};

const unsigned char gImage_6432_smile_sad[256] = { 
0X00,0X00,0X00,0X00,0X00,0X3F,0XFC,0X00,0X03,0XFF,0XFF,0XC0,0X07,0XFF,0XFF,0XF0,
0X1F,0X00,0X00,0XF8,0X1C,0X00,0X00,0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0X06,0X00,0X00,0X00,0X0E,0X00,0X00,0X00,0X1E,0X00,
0X00,0X00,0X3C,0X00,0X00,0X00,0X78,0X00,0X00,0X00,0XF0,0X00,0X00,0X00,0XE0,0X00,
0X00,0X00,0XF0,0X00,0X00,0X00,0X78,0X00,0X00,0X00,0X3C,0X00,0X00,0X00,0X1E,0X00,
0X00,0X00,0X0E,0X00,0X00,0X00,0X06,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,0X00,0X00,0X38,0X1F,0X80,0X01,0XF8,
0X07,0XFF,0XFF,0XF0,0X01,0XFF,0XFF,0XC0,0X00,0X1F,0XFC,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_6432_smile_happy[256] = { 
0X00,0X00,0X00,0X00,0X00,0X3F,0XFC,0X00,0X01,0XFF,0XFF,0XC0,0X0F,0XFF,0XFF,0XF0,
0X1F,0X80,0X01,0XF8,0X1E,0X00,0X00,0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X04,0X00,0X00,0X00,0X0C,0X00,0X00,0X00,0X1C,0X00,0X00,
0X00,0X38,0X00,0X00,0X00,0X70,0X00,0X00,0X00,0XE0,0X00,0X00,0X01,0XC0,0X00,0X00,
0X00,0XE0,0X00,0X00,0X00,0X70,0X00,0X00,0X00,0X38,0X00,0X00,0X00,0X1C,0X00,0X00,
0X00,0X0C,0X00,0X00,0X00,0X04,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,
0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,
0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,
0X00,0X00,0X06,0X00,0X00,0X00,0X06,0X00,0X00,0X04,0X00,0X00,0X00,0X0C,0X00,0X00,
0X00,0X1C,0X00,0X00,0X00,0X38,0X00,0X00,0X00,0X70,0X00,0X00,0X00,0XE0,0X00,0X00,
0X01,0XC0,0X00,0X00,0X00,0XE0,0X00,0X00,0X00,0X70,0X00,0X00,0X00,0X38,0X00,0X00,
0X00,0X1C,0X00,0X00,0X00,0X0C,0X00,0X00,0X00,0X04,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1E,0X00,0X00,0X38,0X1F,0X80,0X01,0XF8,
0X0F,0XFF,0XFF,0XF0,0X01,0XFF,0XFF,0X80,0X00,0X1F,0XF8,0X00,0X00,0X00,0X00,0X00,
};

#endif



