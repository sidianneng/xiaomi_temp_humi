#include "EPD.h"

/*******************************************************************
 * function: determine if the lcd is busy
 * input: void
 * output block in here if the lcd is busy
*******************************************************************/
void EPD_READBUSY(void)
{
  while(1)
  {
    if(EPD_ReadBusy==0)
    {
      break;
    }
  }
}

/*******************************************************************
 * function: lcd hardware reset
 * input: void
 * output: void
*******************************************************************/
void EPD_HW_RESET(void)
{
  delay_ms(100);
  EPD_RES_Clr();
  delay_ms(10);
  EPD_RES_Set();
  delay_ms(10);
  EPD_READBUSY();
}

/*******************************************************************
 * function: enable display update to lcd
 * input: void
 * output: void
*******************************************************************/
void EPD_Update(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xF4);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
 * function: partial refresh update
 * input: void
 * output: void
*******************************************************************/
void EPD_PartUpdate(void)
{  
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xDC);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
 * function: quick refresh update
 * input: void
 * output: void
*******************************************************************/
void EPD_FastUpdate(void)
{
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xC7);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
 * function: enable sleep for lcd
 * input: void
 * output: void
*******************************************************************/
void EPD_DeepSleep(void)
{
  EPD_WR_REG(0x10);
  EPD_WR_DATA8(0x01);
  delay_ms(200);
}

/*******************************************************************
 * function: software init lcd
 * input: void
 * output: void
*******************************************************************/
void EPD_Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();   
  EPD_WR_REG(0x12);  //software reset
  EPD_READBUSY();   
}

/*******************************************************************
 * function: init quick refresh mode 1 for lcd
 * input: void
 * output: void
*******************************************************************/
void EPD_FastMode1Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12);  
  EPD_READBUSY();
  EPD_WR_REG(0x18);
  EPD_WR_DATA8(0x80);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xB1);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
  EPD_WR_REG(0x1A);
  EPD_WR_DATA8(0x64);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0x91);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
 * function: init quick refresh mode 2 for lcd
 * input: void
 * output: void
*******************************************************************/
void EPD_FastMode2Init(void)
{
  EPD_HW_RESET();
  EPD_READBUSY();
  EPD_WR_REG(0x12); 
  EPD_READBUSY();
  EPD_WR_REG(0x18);
  EPD_WR_DATA8(0x80);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0xB1);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
  EPD_WR_REG(0x1A);
  EPD_WR_DATA8(0x5A);
  EPD_WR_DATA8(0x00);
  EPD_WR_REG(0x22);
  EPD_WR_DATA8(0x91);
  EPD_WR_REG(0x20);
  EPD_READBUSY();
}

/*******************************************************************
 * function: clear the display
 * input: void
 * output: void
*******************************************************************/
void EPD_Display_Clear(void)
{
  uint16_t i;
  EPD_WR_REG(0x3C);
  EPD_WR_DATA8(0x05);
  EPD_WR_REG(0x24);
  for(i=0;i<2888;i++)
  {
    EPD_WR_DATA8(0xFF);
  }  
  EPD_READBUSY();
  EPD_WR_REG(0x26);
  for(i=0;i<2888;i++)
  {
    EPD_WR_DATA8(0x00);
  }  
}

/*******************************************************************
 * function: clear the display for partial refresh
 * input: void
 * output: void
*******************************************************************/
void EPD_Clear_R26H(void)
{
  uint16_t i;
  EPD_READBUSY();
  EPD_WR_REG(0x26);
  for(i=0;i<2888;i++)
  {
    EPD_WR_DATA8(0xFF);
  }
}

/*******************************************************************
 * function: update image data to lcd 
 * input: void
 * output: void
*******************************************************************/
void EPD_Display(const uint8_t *image)
{
  uint16_t i,j,Width,Height;
  Width=(EPD_W%8==0)?(EPD_W/8):(EPD_W/8+1);
  Height=EPD_H;
  EPD_WR_REG(0x24);
  for (j=0;j<Height;j++) 
  {
    for (i=0;i<Width;i++) 
    {
      EPD_WR_DATA8(image[i+j*Width]);
    }
  }
}


