/**********************************************

�洢���ӿں�����

�洢����СΪ8Mbits
����ռ�4096(0 - 4095)ҳ��ÿҳ����256(0 - 255)�ֽ�

�����ݴ��浥λ��һ���ֽ�ʱ��ÿҳ��256(0 - 255)��λ�õ�ַ��ÿ��λ�ô���һ������
�����ݴ��浥λ�������ֽ�ʱ��ÿҳ��128(0 - 127)��λ�õ�ַ��ÿ��λ�ô���һ������
*/
/**********************�ٶȲ�������*********
����DCO��Ϊ12MHz��8λ���ͣ��������£�
BCSCTL1 = CALBC1_12MHZ;
DCOCTL = CALDCO_12MHZ;
54sд��8Mbits(дǰ�Զ�ɾ����дҳ����)
9s����8Mbits
12sд��8Mbits(дǰ��ɾ����дҳ����,���ֶ�ɾ��)


����DCO��Ϊ12MHz��16λ���ͣ��������£�
BCSCTL1 = CALBC1_12MHZ;
DCOCTL = CALDCO_12MHZ;
80sд��8Mbits(дǰ�Զ�ɾ����дҳ����)
45s����8Mbits
50sд��8Mbits(дǰ��ɾ����дҳ����,���ֶ�ɾ��)

����DCO��Ϊ1MHz��16λ���ͣ��������£�
BCSCTL1 = CALBC1_1MHZ;
DCOCTL = CALDCO_1MHZ;
130sд��8Mbits(дǰ�Զ�ɾ����дҳ����)
90s����8Mbits
90sд��8Mbits(дǰ��ɾ����дҳ����,���ֶ�ɾ��)

********************************************/

#ifndef MEMORIZER_H_
#define MEMORIZER_H_

#include"MSP430G2553.h"
#include"SPI.h"
#include"AT45DB081.h"

//���ܣ���ʼ���洢������ģʽ
void AT45DB081_init();
//���ܣ���������洢��������
void erase_chip();

//���ܣ�д�뵽�洢����дǰ�Զ�ɾ����дҳ���ݣ�
//ע�⣺���浥λΪһ���ֽڣ������ַ���������Ϊunsigned char
//unsigned int page,Ҫ���浽�ڼ�ҳ��С��4096
//unsigned int start_address,ҳ�еľ���λ�ã��������ʼλ��,С��256
//unsigned int length,Ҫ���������������С��256
//unsigned char *buffer���ַ����飬�����еĴ��������д��洢��
//ʾ����write_8(0,0,256,MyBuff);�Ӵ洢���ĵ�һҳ�ĵ�һ��λ�ÿ�ʼ��д������MyBuff�е�256������
//void write_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer);

//���ܣ���ȡ�洢��
//ע�⣺���浥λΪһ���ֽڣ������ַ���������Ϊunsigned char
//unsigned int page,Ҫ��ȡ�ڼ�ҳ��С��4096
//unsigned int start_address,ҳ�еľ���λ�ã���ȡ����ʼλ�ã�С��256
//unsigned int length,Ҫ��ȡ������������С��256
//unsigned char *buffer���ַ����飬��Ҫ��ȡ�����ݴ�������������
//ʾ����read_8(0,0,256,MyBuff);�Ӵ洢���ĵ�һҳ�ĵ�һ��λ�ÿ�ʼ����ȡ256�����ݣ�����MyBuff��
//void read_8(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer);

//���ܣ�д�뵽�洢����дǰ��ɾ����дҳ����,���ֶ�ɾ����
//�ص㣺���write_8�������������ٶȽϿ�(û����ɾ��ʱ��)��
//��ɾ���ٶȺܿ�
//ע�⣺���浥λΪһ���ֽڣ������ַ���������Ϊunsigned char
//unsigned int page,Ҫ���浽�ڼ�ҳ��С��4096
//unsigned int start_address,ҳ�еľ���λ�ã��������ʼλ��,С��256
//unsigned int length,Ҫ���������������С��256
//unsigned int *buffer�����飬�����еĴ��������д��洢��
//void write_8_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned char *buffer);

//���ܣ�д�뵽�洢����дǰ�Զ�ɾ����дҳ���ݣ�
//ע�⣺���浥λΪ�����ֽڣ������ַ���������Ϊunsigned int
//unsigned int page,Ҫ���浽�ڼ�ҳ��С��4096
//unsigned int start_address,ҳ�еľ���λ�ã��������ʼλ��,С��128
//unsigned int length,Ҫ���������������С��128
//unsigned char *buffer���ַ����飬�����еĴ��������д��洢��
//ʾ����write_16(0,0,120,MyBuff_16);�Ӵ洢���ĵ�һҳ�ĵ�һ��λ�ÿ�ʼ��д������MyBuff_16�е�120������
void write_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer);

//���ܣ���ȡ�洢��
//ע�⣺���浥λΪ�����ֽڣ������ַ���������Ϊunsigned int
//unsigned int page,Ҫ��ȡ�ڼ�ҳ��С��4096
//unsigned int start_address,ҳ�еľ���λ�ã���ȡ����ʼλ�ã�С��128
//unsigned int length,Ҫ��ȡ������������С��128
//unsigned char *buffer���ַ����飬��Ҫ��ȡ�����ݴ�������������
//ʾ����read_16(0,0,120,MyBuff_16);�Ӵ洢���ĵ�һҳ�ĵ�һ��λ�ÿ�ʼ����ȡ120�����ݣ�����MyBuff_16��
void read_16(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer);

//���ܣ�д�뵽�洢����дǰ��ɾ����дҳ����,���ֶ�ɾ����
//�ص㣺���write_16�������������ٶȽϿ�(û����ɾ��ʱ��)��
//��ɾ���ٶȺܿ�
//ע�⣺���浥λΪһ���ֽڣ������ַ���������Ϊunsigned char
//unsigned int page,Ҫ���浽�ڼ�ҳ��С��4096
//unsigned int start_address,ҳ�еľ���λ�ã��������ʼλ��,С��128
//unsigned int length,Ҫ���������������С��128
//unsigned int *buffer�����飬�����еĴ��������д��洢��
//void write_16_without(unsigned int page,unsigned int start_address,unsigned int length,unsigned int *buffer);
#endif
