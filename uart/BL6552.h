# ifndef __BL6552_H__
# define __BL6552_H__

#include "usart.h"
#include "delay.h"

#define READ_CMD 0x35
#define WRITE_CMD 0xca


void BL6552Read(uint8_t * read_addr, uint32_t *read_data);
void BL6552Write(uint8_t * write_addr, uint32_t *write_data);

# endif /*__BL6552_H__*/
