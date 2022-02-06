/**
 * Middle-level operations of flash
 * For example, write array of bytes/words to designated page and page address
 */

#include"memorizer.h"

unsigned char D[2];

/**
 * Write words to FLASH without erasing the page
 * 
 * @param page page index
 * @param start_address page offset
 * @param length number of words
 * @param buffer pointer to array of words
 */
void write_16_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer)
{

    FlashBuffer1ProgNoErase(page);

    int i;
    for(i=0; i<length; i++)
    {
        *(D)= ((unsigned char)((buffer[i]) >> 8));
        *(D+1) = ((unsigned char)(buffer[i]));
        FlashBuffer1Write(start_address*2+i*2,2,D);

    }
    FlashBuffer1ProgNoErase(page);

}
/**
 * Initialize AT45DB081
 */
void AT45DB081_init()
{
    DF_RESET; //Reset AT45DB081 
    SPI_init();
    SPI_HighSpeed();
}
/**
 * Earse the whole Flash
 */
void erase_chip()
{
    chip_erase();
}

/**
 * Write bytes to FLASH without erasing the page
 * 
 * @param page page index
 * @param start_address page offset
 * @param length number of bytes
 * @param buffer pointer to array of bytes
 */
void write_8_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer)
{
    FlashBuffer1Write(start_address,length,buffer);
    FlashBuffer1ProgNoErase(page);

}

/**
 * Write bytes to FLASH with erasing the page
 * 
 * @param page page index
 * @param start_address page offset
 * @param length number of bytes
 * @param buffer pointer to array of bytes
 */
void write_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer)
{

    FlashBuffer1Write(start_address,length,buffer);
    FlashBuffer1ProgAutoErase(page);
}

/**
 * Read bytes from FLASH
 * 
 * @param page page index
 * @param start_address page offset
 * @param length number of bytes
 * @param buffer pointer to array of bytes
 */
void read_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer)
{
    PageToBuffer2(page);
    FlashBuffer2Read(start_address,length,buffer);
}

/**
 * Write words to FLASH with erasing the page
 * 
 * @param page page index
 * @param start_address page offset
 * @param length number of words
 * @param buffer pointer to array of words
 */
void write_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer)
{

    int i;
    for(i=0; i<length; i++)
    {
        *(D)= ((unsigned char)((buffer[i]) >> 8));
        *(D+1) = ((unsigned char)(buffer[i]));
        FlashBuffer1Write(start_address*2+i*2,2,D);

    }

    FlashBuffer1ProgAutoErase(page);

}

/**
 * Read words from FLASH
 * 
 * @param page page index
 * @param start_address page offset
 * @param length number of words
 * @param buffer pointer to array of words
 */
void read_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer)
{
    int i;

    PageToBuffer2(page);

    for(i=0; i<length; i++)
    {
        FlashBuffer2Read(start_address*2+i*2,2,D);
        buffer[i] = ((D[0] * 256) + (D[1]));
    }



}
