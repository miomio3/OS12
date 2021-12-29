#include "defines.h"
#include "serial.h"
#include "lib.h"
#include "xmodem.h"

int global_data = 0x10;
int global_bss;
int static_data = 0x20;
int static_bss;

static int dump(char *buf, long size)
{
  long i;

  if(size < 0){
    puts("No data.\n");
    return (-1);
  }
  for(i = 0; i < size; i++){
    putxval(buf[i], 2);
    if(i & 0xf == 15){
      puts("\n");
    }
    else if(i & 0xf == 7){
      puts(" ");
    }
  }
  puts("\n");
  return (0);
}

static void wait()
{
  volatile long i;

  for(i = 0; i < 300000; i++);
}

static int init(void)
{
  extern int rodata_start, rodata_end, data_start, data_end, bss_start, bss_end;
  
  memcpy(&data_start, &rodata_end, (long)(&data_end - &data_start));
  memset(&bss_start, 0, (long)(&bss_end - &bss_start));
  serial_init(SERIAL_DEFAULT_DEVICE);
  return (0);
}

int main(void)
{
  static char buf[16];
  static long size;
  static unsigned char *loadbuf;
  extern int buffer_start;

  size = 0;
  loadbuf = NULL;

  init();

  puts("12load(boot loader) started. \n");
  while(1)
  {
    puts("12load> ");
    gets(buf);
  
    if(!strcmp(buf, "load")){
      loadbuf = (char *)(&buffer_start);
      size = xmodem_recv(loadbuf);
      wait(); //stop until control of xmodem-app stop
      if(size < 0){
        puts("\nXMODEM receive error.\n");
      }
      else{
        puts("\nXMODEM receive suceeded.\n");
      }
    }
    else if(!strcmp(buf, "dump")){
      puts("size: ");
      putxval(size, 0);
      puts("\n");
      dump(loadbuf, size);
    }
    else{
      puts("dump error.\n");
    }
  }

  return 0;
}
