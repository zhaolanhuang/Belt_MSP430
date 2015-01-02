/**********************************************

存储器接口函数库

存储器大小为8Mbits
储存空间4096(0 - 4095)页，每页储存256(0 - 255)字节

当数据储存单位是一个字节时，每页有256(0 - 255)个位置地址，每个位置储存一个数据
当数据储存单位是两个字节时，每页有128(0 - 127)个位置地址，每个位置储存一个数据
*/
/**********************速度测试数据*********
当将DCO设为12MHz，8位发送，具体如下：
BCSCTL1 = CALBC1_12MHZ;
DCOCTL = CALDCO_12MHZ;
54s写完8Mbits(写前自动删除待写页内容)
9s读完8Mbits
12s写完8Mbits(写前不删除待写页内容,需手动删除)


当将DCO设为12MHz，16位发送，具体如下：
BCSCTL1 = CALBC1_12MHZ;
DCOCTL = CALDCO_12MHZ;
80s写完8Mbits(写前自动删除待写页内容)
45s读完8Mbits
50s写完8Mbits(写前不删除待写页内容,需手动删除)

当将DCO设为1MHz，16位发送，具体如下：
BCSCTL1 = CALBC1_1MHZ;
DCOCTL = CALDCO_1MHZ;
130s写完8Mbits(写前自动删除待写页内容)
90s读完8Mbits
90s写完8Mbits(写前不删除待写页内容,需手动删除)

********************************************/

#ifndef MEMORIZER_H_
#define MEMORIZER_H_

#include"MSP430G2553.h"
#include"SPI.h"
#include"AT45DB081.h"

//功能：初始化存储器工作模式
void AT45DB081_init();
//功能：清除整个存储器的数据
void erase_chip();

//功能：写入到存储器（写前自动删除待写页内容）
//注意：储存单位为一个字节，所以字符数组类型为unsigned char
//unsigned int page,要储存到第几页，小于4096
//unsigned int start_address,页中的具体位置，储存的起始位置,小于256
//unsigned int length,要储存的数据数量，小于256
//unsigned char *buffer，字符数组，将其中的储存的数据写入存储器
//示例：write_8(0,0,256,MyBuff);从存储器的第一页的第一个位置开始，写入数组MyBuff中的256个数据
//void write_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer);

//功能：读取存储器
//注意：储存单位为一个字节，所以字符数组类型为unsigned char
//unsigned int page,要读取第几页，小于4096
//unsigned int start_address,页中的具体位置，读取的起始位置，小于256
//unsigned int length,要读取的数据数量，小于256
//unsigned char *buffer，字符数组，将要读取的数据储存的这个数组中
//示例：read_8(0,0,256,MyBuff);从存储器的第一页的第一个位置开始，读取256个数据，存入MyBuff中
//void read_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer);

//功能：写入到存储器（写前不删除待写页内容,需手动删除）
//特点：相对write_8函数，本函数速度较快(没算上删除时间)，
//但删除速度很快
//注意：储存单位为一个字节，所以字符数组类型为unsigned char
//unsigned int page,要储存到第几页，小于4096
//unsigned int start_address,页中的具体位置，储存的起始位置,小于256
//unsigned int length,要储存的数据数量，小于256
//unsigned int *buffer，数组，将其中的储存的数据写入存储器
//void write_8_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer);

//功能：写入到存储器（写前自动删除待写页内容）
//注意：储存单位为两个字节，所以字符数组类型为unsigned int
//unsigned int page,要储存到第几页，小于4096
//unsigned int start_address,页中的具体位置，储存的起始位置,小于128
//unsigned int length,要储存的数据数量，小于128
//unsigned char *buffer，字符数组，将其中的储存的数据写入存储器
//示例：write_16(0,0,120,MyBuff_16);从存储器的第一页的第一个位置开始，写入数组MyBuff_16中的120个数据
void write_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer);

//功能：读取存储器
//注意：储存单位为两个字节，所以字符数组类型为unsigned int
//unsigned int page,要读取第几页，小于4096
//unsigned int start_address,页中的具体位置，读取的起始位置，小于128
//unsigned int length,要读取的数据数量，小于128
//unsigned char *buffer，字符数组，将要读取的数据储存的这个数组中
//示例：read_16(0,0,120,MyBuff_16);从存储器的第一页的第一个位置开始，读取120个数据，存入MyBuff_16中
void read_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer);

//功能：写入到存储器（写前不删除待写页内容,需手动删除）
//特点：相对write_16函数，本函数速度较快(没算上删除时间)，
//但删除速度很快
//注意：储存单位为一个字节，所以字符数组类型为unsigned char
//unsigned int page,要储存到第几页，小于4096
//unsigned int start_address,页中的具体位置，储存的起始位置,小于128
//unsigned int length,要储存的数据数量，小于128
//unsigned int *buffer，数组，将其中的储存的数据写入存储器
//void write_16_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer);
#endif
