#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

int serial_init(int index);                       /* �ǥХ�������� */
int serial_is_send_enable(int index);
int	serial_is_recv_enable(int index);
int serial_send_byte(int index, unsigned char b); /* ��ʸ������ */
unsigned char serial_recv_byte(int index);

#endif
