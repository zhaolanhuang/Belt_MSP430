/**
 * Low-leval operations on the Flash AT45DB081
 * Read/Write the flash by specific commands through SPI
 * Buffer1 and Buffer2 are the buffers in the flash, not in the memory of MCU
 */


#include"AT45DB081.h"


unsigned char CMD[5];


//缓存1写主存
/**
 * Flush buffer 1 to specific page
 * @param AT450XXPageAddr page index
 */
void FlashBuffer1ProgNoErase(unsigned int AT450XXPageAddr) //直接将缓存1写入Flash一页(不擦除)
{


    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (B1_TO_PAGE_WITHOUT_ERASE);
    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = (0x00);

    SPI_TxFrame(CMD,4);

    SPI_CS_High();
}

/**
 * Erase the flash with zero-filled
 */
void chip_erase()
{
    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (CHIP_ERASE_1);
    CMD[1] = (CHIP_ERASE_2);
    CMD[2] = (CHIP_ERASE_3);
    CMD[3] = (CHIP_ERASE_4);

    SPI_TxFrame(CMD,4);

    SPI_CS_High();
}

/**
 * Write data to flash through buffer 1
 * @param AT450XXPageAddr page index
 * @param start_addr page offset
 * @param len number of words to be written
 * @param buffer array of words to be written
 */
void FlashAutoProgViaBuffer1(unsigned int AT450XXPageAddr,unsigned int start_addr, unsigned int len,unsigned char *buffer)
//将指定数据通过缓存1写入Flash指定位置(先擦除)
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (PAGE_PROG_THROUGH_B1);//缓冲区1为82H
    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1 + start_addr>>8));
    CMD[3] = ((unsigned char)start_addr);

    SPI_TxFrame(CMD,4);
    SPI_TxFrame(buffer,len);

    SPI_CS_High();
}

/**
 * @return flash status
 */
unsigned char GetFlashStatus()
{
    unsigned char staus[1];

    SPI_CS_Low();//芯片选择
    CMD[0] = STATUS_REGISTER;
    SPI_TxFrame(CMD,1);


    SPI_RxFrame(staus,1);
    SPI_CS_High();
    return staus[0];

}

//擦除＋缓存1写主存
/**
 * Erase page and flush buffer 1 to it
 * @param AT450XXPageAddr page index
 */
void FlashBuffer1ProgAutoErase(unsigned int AT450XXPageAddr) //直接将缓存1写入Flash一页(先擦除)
{
    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (B1_TO_PAGE_WITH_ERASE);
    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = 0;

    SPI_TxFrame(CMD,4);

    SPI_CS_High();
}

/**
 * read specific page to buffer 2
 * @param AT450XXPageAddr page index
 */
void PageToBuffer2(unsigned int AT450XXPageAddr)    //从Flash读一页至缓存2
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (PAGE_TO_B2_XFER);

    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = 0;

    SPI_TxFrame(CMD,4);
    SPI_CS_High();

}

/**
 * read specific page to buffer 1
 * @param AT450XXPageAddr page index
 */
void PageToBuffer1(unsigned int AT450XXPageAddr)    //从Flash读一页至缓存2
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();


    CMD[0] = (PAGE_TO_B1_XFER);

    CMD[1] = ((unsigned char)(AT450XXPageAddr >> 7));
    CMD[2] = ((unsigned char)(AT450XXPageAddr << 1));
    CMD[3] = 0;

    SPI_TxFrame(CMD,4);
    SPI_CS_High();

}

//启用缓存2读
/**
 * read specific data from buffer 2
 * @param star_addr start address of data
 * @param len data length
 * @param buffer 
 */
void FlashBuffer2Read(unsigned int star_addr,unsigned int len, unsigned char *buffer)
//从缓冲区2的指定位置(0-255)中读入指定字节
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_2_READ);

    CMD[1] = 0;

    CMD[2] = ((unsigned char)(star_addr>>8));
    CMD[3] = ((unsigned char)(star_addr));

    CMD[4] = 0;

    SPI_TxFrame(CMD,5);

    SPI_RxFrame(buffer,len);



    SPI_CS_High();

}
//启用缓存1读
/**
 * read specific data from buffer 1
 * @param star_addr start address of data
 * @param len data length
 * @param buffer 
 */
void FlashBuffer1Read(unsigned int star_addr,unsigned int len, unsigned char *buffer)
//从缓冲区1的指定位置(0-255)中读入指定字节
{

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_1_READ);

    CMD[1] = 0;

    CMD[2] = ((unsigned char)(star_addr>>8));
    CMD[3] = ((unsigned char)(star_addr));

    CMD[4] = 0;

    SPI_TxFrame(CMD,5);

    SPI_RxFrame(buffer,len);



    SPI_CS_High();

}

//启用缓存1写
/**
 * Write specific data to buffer 1
 * @param star_addr start address of data
 * @param len data length
 * @param buffer array to be written
 */
void FlashBuffer1Write(unsigned int start_addr, unsigned int len,unsigned char *buffer)
//向缓冲区1的指定位置(0-255)写入指定字节
{
    unsigned int i;

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_1_WRITE);
    CMD[1] = 0;
    CMD[2] = ((unsigned char)(start_addr>>8));
    CMD[3] = ((unsigned char)(start_addr ));


    SPI_TxFrame(CMD,4);


    SPI_TxFrame(buffer,len);

    SPI_CS_High();
}
//启用缓存2写
/**
 * Write specific data to buffer 2
 * @param star_addr start address of data
 * @param len data length
 * @param buffer array to be written
 */
void FlashBuffer2Write(unsigned int start_addr, unsigned int len,unsigned char *buffer)
//向缓冲区2的指定位置(0-255)写入指定字节
{
    unsigned int i;

    while(!(GetFlashStatus()&128));
    SPI_CS_Low();
    CMD[0] = (BUFFER_2_WRITE);
    CMD[1] = 0;
    CMD[2] = ((unsigned char)(start_addr>>8));
    CMD[3] = ((unsigned char)start_addr);

    SPI_TxFrame(CMD,4);


    SPI_TxFrame(buffer,len);

    SPI_CS_High();
}
