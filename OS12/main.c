#include "defines.h"
#include "serial.h"
#include "lib.h"

int	main(void)
{
	static char	buf[32];

	puts("Hello, world!\n");
	while(1)
	{
		puts("> ");
		gets(buf);
	
		if(!strncmp(buf, "echo", 4)){
			puts(buf + 4);
			puts("\n");
		}
		else if(!strcmp(buf, "exit")){
			break;
		}
		else{
			puts("Unknown.\n");
		}
	}
	return (0);
}