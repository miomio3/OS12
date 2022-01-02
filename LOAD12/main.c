#include "defines.h"
#include "serial.h"
#include "xmodem.h"
#include "lib.h"
#include "elf.h"

static int  init(void)
{
  extern int rodata_end, data_start, data_end, bss_start, bss_end;

  memcpy(&data_start, &rodata_end, (long)(&data_end - &data_start));
  memset(&bss_start, 0, (long)(&bss_end - &bss_start));
  serial_init(SERIAL_DEFAULT_DEVICE);
  return (0);
}

static int  dump(char *buf, long size)
{
  long  i;

  if(size < 0){
    puts("nodata.\n");
    return (-1);
  }
  for(i = 0; i < size; i++){
    putxval(buf[i], 2);
    if((i & 0xf) == 15){
      puts("\n");
    }
    else{
      if((i & 0xf) == 7){
        puts(" ");
      }
    }
  }
  puts("\n");
  return (0);
}

static void wait(void)
{
  volatile long i;
  for(i = 0; i < 300000; i++);
}

int main(void)
{
  static char buf[16];
  static long size;
  static unsigned char  *loadbuf;
  extern int  buffer_start;
  char	*entry_point;
  void	(*f)(void);

  init();
  puts("OS12 has start.\n");

  while(1)
  {
    puts("OS12> ");
    gets(buf);
  
    if(!strcmp(buf, "load")){
      loadbuf = (char *)&buffer_start;
      size = xmodem_recv(loadbuf);
      wait();
      if(size < 0){
        puts("Receive error.\n");
      }
      else{
        puts("Receive succeeded.\n");
      }
    }
    else if(!strcmp(buf, "dump")){
      puts("size: ");
      putxval(size, 0);
      puts("\n");
      dump(loadbuf, size);
    }
    else if(!strcmp(buf, "run")){
    	entry_point = elf_load(loadbuf);
		if(!entry_point){
			puts("Run error.\n");
		}
		else{
			puts("Entry point: ");
			putxval((unsigned long)entry_point, 1);
			puts("\n");
			f = (void (*)(void))entry_point;
			f();
		}
    }
    else{
      puts("Input load or dump or run.\n");
    }
  }
  return (0);
}