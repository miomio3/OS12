#include "defines.h"
#include "serial.h"
#include "lib.h"
#include "intr.h"
#include "interrupt.h"

static void	intr(sofvec_type_t type, unsigned long sp)
{
	int	c;
	static char	buf[32];
	static int	len;

	c = getc();
	if(c != '\n'){
		buf[len] = c;
		len++;
	}
	else{
		buf[len] = '\0';
		if(!strncmp(buf, "echo", 4)){
			puts(buf + 4);
			puts("\n");
		}
		else{
			puts("Unknown.\n");
		}
		puts("> ");
		len = 0;
	}
}

int	main(void)
{
	sofvec_set_intr(SOFVEC_TYPE_SERINTR, intr);
	serial_intr_recv_enable(SERIAL_DEFAULT_DEVICE);
	puts("Hello, world!\n");
	puts("> ");
	while(1)
	{
		INTR_ENABLE;
		asm volatile("sleep");
	}
	return (0);
}