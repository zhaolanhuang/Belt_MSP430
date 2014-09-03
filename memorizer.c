#include"memorizer.h"

unsigned char D[2];

/*void write_16_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer)
{

    FlashBuffer1ProgNoErase(page);

    int i;
    for(i=0; i<length; i++)
    {
        *(D)= ((unsigned char)((buffer[i]) >> 8));
        *(D+1) = ((unsigned char)(buffer[i]));
        FlashBuffer1Write(start_address+i*2,2,D);

    }
    FlashBuffer1ProgNoErase(page);

}*/
void AT45DB081_init()
{
    DF_RESET;
    SPI_init();
    SPI_HighSpeed();
}
void erase_chip()
{
    chip_erase();
}
/*
void write_8_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer)
{
    FlashBuffer1Write(start_address,length,buffer);
    FlashBuffer1ProgNoErase(page);

}
void write_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer)
{

    FlashBuffer1Write(start_address,length,buffer);
    FlashBuffer1ProgAutoErase(page);
}
void read_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer)
{
    PageToBuffer2(page);
    FlashBuffer2Read(start_address,length,buffer);
}
*/
void write_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer)
{
    int i;
    for(i=0; i<length; i++)
    {
        *(D)= ((unsigned char)((buffer[i]) >> 8));
        *(D+1) = ((unsigned char)(buffer[i]));
        FlashBuffer1Write(start_address+i*2,2,D);

    }

    FlashBuffer1ProgAutoErase(page);
}
void read_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer)
{
    int i;

    PageToBuffer2(page);

    for(i=0; i<length; i++)
    {
        FlashBuffer2Read(start_address+i*2,2,D);
        buffer[i] = ((D[0] * 256) + (D[1]));
    }


}
