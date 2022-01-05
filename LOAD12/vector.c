#include "defines.h"

extern void	start(void);
extern void	intr_soferr(void);
extern void	intr_syscall(void);
extern void	intr_serintr(void);

void	(*vectors[])(void) = {
	start, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	intr_syscall, intr_soferr, intr_soferr, intr_soferr,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	intr_serintr, intr_serintr, intr_serintr, intr_serintr,
	intr_serintr, intr_serintr, intr_serintr, intr_serintr,
	intr_serintr, intr_serintr, intr_serintr, intr_serintr,
};