#ifndef AT45DB081_H_
#define AT45DB081_H_

#include"MSP430G2553.h"
#include"SPI.h"


#define DF_RESET     P2OUT &=~BIT4; P2OUT |= BIT4;      // AT45DB081 reset
#define BUFFER_1_READ 0xD4     // buffer 1 read (change to 0xD4 for SPI mode 0,3)
#define BUFFER_2_READ 0xD6     // buffer 2 read (change to 0xD6 for SPI
#define BUFFER_1_WRITE 0x84     // buffer 1 write
#define BUFFER_2_WRITE 0x87
#define STATUS_REGISTER 0xD7
#define B1_TO_PAGE_WITH_ERASE 0x83
#define PAGE_TO_B2_XFER 0x55     // transfer flash page to buffer 2 
#define PAGE_TO_B1_XFER 0x53     // transfer flash page to buffer 1 
#define B1_TO_PAGE_WITHOUT_ERASE 0x88   // buffer 1 to flash page
#define PAGE_PROG_THROUGH_B1 0x82    

#define CHIP_ERASE_1 0xC7
#define CHIP_ERASE_2 0x94
#define CHIP_ERASE_3 0x80
#define CHIP_ERASE_4 0x9A

void chip_erase();
void FlashAutoProgViaBuffer1(unsigned int AT450XXPageAddr,unsigned int start_addr, unsigned int len,unsigned char *buffer);
unsigned char GetFlashStatus();
void FlashBuffer1ProgAutoErase(unsigned int AT450XXPageAddr);
void PageToBuffer2(unsigned int AT450XXPageAddr);
void PageToBuffer1(unsigned int AT450XXPageAddr);
void FlashBuffer2Read(unsigned int star_addr,unsigned int len, unsigned char *buffer);
void FlashBuffer1Read(unsigned int star_addr,unsigned int len, unsigned char *buffer);
void FlashBuffer1Write(unsigned int start_addr, unsigned int len,unsigned char *buffer);
void FlashBuffer2Write(unsigned int start_addr, unsigned int len,unsigned char *buffer);
void FlashBuffer1ProgNoErase(unsigned int AT450XXPageAddr) ;

#endif
