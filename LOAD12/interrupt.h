#ifndef	_INTERRUPT_H_
#define	_INTERRUPT_H_

extern char	sofvec;
#define	SOFVEC_ADDR	(&sofvec)
typedef	short	sofvec_type_t;
typedef void	(*sofvec_handler_t)(sofvec_type_t type, unsigned long sp);
#define SOFVEC	((sofvec_handler_t *)SOFVEC_ADDR)

#define	INTR_ENABLE		asm volatile ("andc.b #0x3f,ccr")
#define	INTR_DISABLE	asm	volatile ("orc.b #0xc0,ccr");

int		sofvec_init(void);
int		sofvec_set_intr(sofvec_type_t type, sofvec_handler_t handler);
void	interrupt(sofvec_type_t type, unsigned long sp);	

#endif