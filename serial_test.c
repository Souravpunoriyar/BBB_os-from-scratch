#include "serial.h"
#include "get_core_details.h"
#include "led.h"
#include "mmu.h"
#include "dumper.h"

void get_hex_string(int num , char *hex_string, int string_size)
{
  int rmndr = 0, temp = 0;
  int quo = 0, i = 0, j = 0, k =0;
  quo = num;
  char store_hex_string[50]= {"0"};
  while(quo != 0)
  {
    temp = quo % 16;
    if(temp < 10) 
      temp = temp + 48;
   else
      temp = temp + 55;
   store_hex_string[i] = temp;
   quo =quo / 16;
   i++;
  }

  for(j = (i-1); j>= 0; j--)
  {
    hex_string[k]=store_hex_string[j];
    k++;
  }

}

#define BASE_ADRESS (0x80000000)
/*make separate file main_switch*/
void main_switch(char check_case)
{
	
	unsigned int i = 0;
	char hex_string[50] = {0};
	char *mem = (char*)BASE_ADRESS;  
	switch(check_case) 
	{
	
	  case '?':serial_tx("Help---- use below commands \r\n");
	           serial_tx("a: Get Running Core Details \r\n");
	           serial_tx("b: Core init \r\n");   	   	
	           serial_tx("c: Beaglebone black ddr3  init \r\n");
	           serial_tx("d: Test ddr memory range \r\n");
	           serial_tx("e: MMU init \r\n");
	           serial_tx("f: led on \r\n");
		   serial_tx("g: led off \r\n");
		   serial_tx("h: dumper default location:0x402F0400 siz 50\r\n");
	         break; 
		
	  case 'a':get_core_details(); 	
	         break; 
	  
	  case 'b':core_init(); 	
	         break; 
	         
	  case 'c':config_ddr_x(); 	
	         break; 
	         
	  case 'd' :
	           /*
	          for(i=0; i<5000; i--){
	              get_hex_string( (int*)(mem+i) , hex_string, 50);  
	              serial_tx("\r\n");
	              serial_tx(hex_string);
	            }*/
	         break; 

	  case 'e' :mmu_init();
		 break;

	  case 'f' : led_on();
		break;	 

	  case 'g' : led_off();
		break;

	  case 'h':dumper(0x402F0400,50);
      		break;		   
	         
	  default:
	       serial_tx("Default case \r\n");	
	       serial_tx("Help---- use below commands \r\n");
	       serial_tx("'?' for help....... \r\n");
	       serial_tx("a: Get Running Core Details \r\n");
	       serial_tx("b: Core init \r\n");
	       serial_tx("c: Beaglebone black ddr3 init \r\n");   	   	   	   	
	       serial_tx("d: Test ddr memory range \r\n");  
	       serial_tx("e: MMU init \r\n");
	       serial_tx("f: led on \r\n");
	       serial_tx("g: led off \r\n");
	       serial_tx("h: dumper default location:0x402F0400 siz 50\r\n");

	}
		
	
}



int c_entry(void)
{
	char str[32];
    int num = 45;
    int fret = 0;
    char hex_string[32] = {0};
    int i =0;
    
	serial_init(115200);
	int val = 0;
	serial_byte_rx();
	serial_tx("Welcome to 1st bootloader\r\n");
    serial_tx("Enter ? for help\r\n");    
    for (;;)
	{
//		led_on();
		serial_tx("Cmd> ");
		serial_rx(str, 32);
		serial_tx("You entered: ");
		serial_tx(str);
		serial_tx("\r\n");
//		led_off();
		main_switch(str[0]);  
		
	}
	serial_shut();
	return 0;
}



