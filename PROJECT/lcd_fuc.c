#include"lcd_header.h"						 
void lcd_config(void)
{
  LPC_GPIO0->FIODIR|=RS|EN|DATA;
  lcdcmd(0x30);
  lcdcmd(0                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        x01);
  lcdcmd(0x0E);
  lcdcmd(0x80);
}
void lcdcmd(unsigned char c)
{
																								  
 LPC_GPIO0->FIOCLR=(0xFF<<15); 
 LPC_GPIO0->FIOSET=(c<<15);
 LPC_GPIO0->FIOCLR=RS;
 LPC_GPIO0->FIOSET=EN;
 delay(10);
 LPC_GPIO0->FIOCLR=EN;
}
void lcddata(unsigned char d)
{
 LPC_GPIO0->FIOCLR=(0xFF<<15);
 LPC_GPIO0->FIOSET=(d<<15);
 LPC_GPIO0->FIOSET=RS;
 LPC_GPIO0->FIOSET=EN;
 delay(50);
 LPC_GPIO0->FIOCLR=EN;
}
void lcdstr(unsigned char *ptr)
{
 while(*ptr!='\0'){
 lcddata(*ptr);
 *ptr++;
 }
 }
void delay(unsigned int a)
{
 unsigned int i,j;
 for(i=0;i<a;i++)
  for(j=0;j<5000;j++);
}
