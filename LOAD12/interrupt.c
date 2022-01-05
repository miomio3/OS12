#include "defines.h"
#include "intr.h"
#include "interrupt.h"

int	sofvec_init(void)
{
	int	type;
	for(type = 0; type < SOFVEC_TYPE_NUM; type++)
		sofvec_set_intr(type, NULL);
	return (0);
}

int	sofvec_set_intr(sofvec_type_t type, sofvec_handler_t handler)
{
	SOFVEC[type] = handler;
	return (0);
}

void	interrupt(sofvec_type_t type, unsigned long sp)
{
	sofvec_handler_t	handler;

	handler = SOFVEC[type];
	handler(type, sp);
}