#include<lpc17xx.h> 
#include "lcd_func.c" 
#define ROWS (0x0F<<4) 
#define COLS (0X0F<<0) 
int b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0,q=0; 
void uartcon(){ 
LPC_PINCON->PINSEL0 |= (1 << 4);   
LPC_PINCON->PINSEL0 &= ~(1 << 5); 
LPC_PINCON->PINSEL0 |= (1 << 6);  
LPC_PINCON->PINSEL0 &= ~(1 << 7); 
LPC_SC->CLKSRCSEL = 0x00; 
LPC_SC->PCLKSEL0 &= ~((1 << 7) | (1 << 6)); 
LPC_UART0->LCR |= 0x03; 
LPC_UART0->LCR |= (1 << 7); 
LPC_UART0->DLM = 0x00; 
LPC_UART0->DLL = 0x06;  
LPC_UART0->FDR |= 0xC1; 
LPC_UART0->FCR |= 0x07;  
LPC_UART0->LCR &= ~(1 << 7); 
} 
char uartreceive() { 
while ((LPC_UART0->LSR & (1 << 0)) == 0) { 
}  
return LPC_UART0->RBR;  
} 
void uarttrans(char c){ 
while (!(LPC_UART0->LSR & (1 << 5))) { }  
LPC_UART0->THR = c;  
} 
void ustr(char *str){ 
while(*str){ 
uarttrans(*str++); 
} 
uarttrans('\r'); 
uarttrans('\n'); 
} 
void keypadin(void){ 
int val1,val2; 
LPC_GPIO2->FIODIR|=COLS; 
LPC_GPIO2->FIODIR&=~ROWS; 
val1=LPC_GPIO2->FIOPIN&ROWS; 
val1=val1>>4; 
LPC_GPIO2->FIODIR|=ROWS; 
LPC_GPIO2->FIODIR&=~COLS; 
val2=LPC_GPIO2->FIOPIN&COLS; 
val2=val2>>0; 
if(val1==0X0E && val2==0X0E){ 
  if(b==0){ 
   lcdstr("Student-1/IN"); 
   delay(10); 
   ustr("Student1 IN"); 
   delay(10); 
   b=1; 
  } 
  else{ 
   lcdstr("Student-1/OUT"); 
   delay(10); 
   ustr("Student-1/OUT"); 
   b=0; 
  }  
 } 
 else if(val1==0X0E && val2==0X0D){ 
  if(c==0){ 
   lcdstr("Student-2/IN"); 
   delay(10); 
   ustr("Student-2/IN"); 
   c=1; 
  } 
  else{ 
   lcdstr("Student-2/OUT"); 
   delay(10); 
   ustr("Student-2/OUT"); 
   c=0; 
  } 
 } 
 else if(val1==0X0E && val2==0X0B){ 
  if(d==0){ 
   lcdstr("Student-3/IN"); 
   delay(10); 
   ustr("Student-3/IN"); 
   d=1; 
  } 
  else{ 
   lcdstr("Student-3/OUT"); 
   delay(10); 
   ustr("Student-3/OUT"); 
   d=0; 
  } 
 } 
 else if(val1==0X0E && val2==0X07){ 
  if(e==0){ 
   lcdstr("Student-4/IN"); 
   delay(10); 
   ustr("Student-4/IN"); 
   e=1; 
  } 
  else{ 
   lcdstr("Student-4/OUT"); 
   delay(10); 
   ustr("Student-4/OUT"); 
   e=0; 
  } 
 } 
 else if(val1==0X0D && val2==0X0E){ 
  if(f==0){ 
   lcdstr("Student-5/IN"); 
   delay(10); 
   ustr("Student-5/IN"); 
   f=1; 
  } 
  else{ 
   lcdstr("Student-5/OUT"); 
   delay(10); 
   ustr("Student-5/OUT"); 
   f=0; 
  } 
 } 
 else if(val1==0X0D && val2==0X0D){ 
  if(g==0){ 
   lcdstr("Student-6/IN"); 
   delay(10); 
   ustr("Student-6/IN"); 
   g=1; 
  } 
  else{ 
   lcdstr("Student-6/OUT"); 
   delay(10); 
   ustr("Student-6/OUT"); 
   g=0; 
  } 
 } 
 else if(val1==0X0D && val2==0X0B){ 
  if(h==0){ 
   lcdstr("Student-7/IN"); 
   delay(10); 
   ustr("Student-7/IN"); 
   h=1; 
  } 
  else{ 
   lcdstr("Student-7/OUT"); 
   delay(10); 
   ustr("Student-7/OUT"); 
   h=0; 
  } 
 } 
 else if(val1==0X0D && val2==0X07){ 
  if(i==0){ 
   lcdstr("Student-8/IN"); 
   delay(10); 
   ustr("Student-8/IN"); 
   i=1; 
  } 
  else{ 
   lcdstr("Student-8/OUT"); 
   delay(10); 
   ustr("Student-8/OUT"); 
   i=0; 
  } 
 } 
 else if(val1==0X0B && val2==0X0E){ 
  if(j==0){ 
   lcdstr("Student-9/IN"); 
   delay(10); 
   ustr("Student-9/IN"); 
   j=1; 
  } 
  else{ 
   lcdstr("Student-9/OUT"); 
   delay(10); 
   ustr("Student-9/OUT"); 
   j=0; 
  } 
 } 
 else if(val1==0X0B && val2==0X0D){ 
  if(k==0){ 
   lcdstr("Student-10/IN"); 
   delay(10); 
   ustr("Student-10/IN"); 
   k=1; 
  } 
  else{ 
   lcdstr("Student-10/OUT"); 
   delay(10); 
   ustr("Student-10/OUT"); 
   k=0; 
  } 
 } 
 else if(val1==0X0B && val2==0X0B){ 
  if(l==0){ 
   lcdstr("Student-11/IN"); 
   delay(10); 
   ustr("Student-11/IN"); 
   l=1; 
  } 
  else{ 
   lcdstr("Student-11/OUT"); 
   delay(10); 
   ustr("Student-11/OUT"); 
   l=0; 
  } 
 } 
 else if(val1==0X0B && val2==0X07){ 
  if(m==0){ 
   lcdstr("Student-12/IN"); 
   delay(10); 
   ustr("Student-12/IN"); 
   m=1; 
  } 
  else{ 
   lcdstr("Student-12/OUT"); 
   delay(10); 
   ustr("Student-12/OUT"); 
   m=0; 
  } 
 } 
 else if(val1==0X07 && val2==0X0E){ 
  if(n==0){ 
   lcdstr("Student-13/IN"); 
   delay(10); 
   ustr("Student-13/IN"); 
   n=1; 
  } 
  else{ 
   lcdstr("Student-13/OUT"); 
   delay(10); 
   ustr("Student-13/OUT"); 
   n=0; 
  } 
 } 
 else if(val1==0X07 && val2==0X0D){ 
  if(o==0){ 
   lcdstr("Student-14/IN"); 
   delay(10); 
   ustr("Student-14/IN"); 
   o=1; 
  } 
  else{ 
   lcdstr("Student-14/OUT"); 
   delay(10); 
   ustr("Student-14/OUT"); 
   o=0; 
  } 
 } 
 else if(val1==0X07 && val2==0X0B){ 
  if(p==0){ 
   lcdstr("Student-15/IN"); 
   delay(10); 
   ustr("Student-15/IN"); 
   p=1; 
  } 
  else{ 
   lcdstr("Student-15/OUT"); 
   delay(10); 
   ustr("Student-15/OUT"); 
   p=0; 
  } 
 } 
 else if(val1==0X07 && val2==0X07){ 
  if(q==0){ 
   lcdstr("Student-16/IN"); 
   delay(10); 
   ustr("Student-16/IN"); 
   q=1; 
  } 
  else{ 
   lcdstr("Student-16/OUT"); 
   delay(10); 
   ustr("Student-16/"); 
   q=0; 
  } 
 } 
 else{ 
  lcdcmd(0x01); 
  delay(10); 
 } 
} 
void toggle(){ 
int i; 
for(i=1;i<=10;i++){ 
LPC_GPIO1->FIOSET=(0XFF<<19)|(1<<27); 
delay(200); 
LPC_GPIO1->FIOCLR=(0XFF<<19)|(1<<27); 
delay(200); 
} 
} 
int main(){ 
char ch; 
//int a; 
LPC_GPIO1->FIODIR|=(0XFF<<19); 
LPC_GPIO1->FIODIR|=(1<<28)|(1<<27); 
LPC_GPIO1->FIOSET=(1<<28); 
LPC_GPIO0->FIODIR&=~(1<<9); 
lcdcon(); 
uartcon();   
while(1) 
{   
keypadin(); 
if(LPC_GPIO0->FIOPIN&(1<<9)){ 
LPC_GPIO1->FIOSET=(1<<28);    
} 
else{ 
LPC_GPIO1->FIOCLR=(1<<28)|(1<<27); 
lcdcmd(0x01); 
delay(100); 
lcdstr("EMERGENCY"); 
toggle(); 
uarttrans(ch-48);
}
}
}
 