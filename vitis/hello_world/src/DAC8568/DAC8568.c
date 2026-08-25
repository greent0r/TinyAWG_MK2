#include "DAC8568.h"
#include <stdint.h>


static void Mcpdely()
{
	usleep(1);
}


//-----------------------------------------------------------------//
// 功 能： 模拟8位SPI通信，发送控制命令
// 入口参数: / 发送的SPI数据
// 出口参数: / 接收的SPI数据
// 全局变量: /   
// 备 注: 发送函数
//-----------------------------------------------------------------//
static void SPI_SendByte(u8 m)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		SCLK_SET; //clk上升沿读取dout数据
		if(m & 0x80)
		{
			DIN_SET;
		}
		else
		{
			DIN_CLR;
		}
		m = m<<1;
		SCLK_CLR; //clk下降沿把din上的数据传到ad
		Mcpdely();
	}
}

 

/**
* @brief DAC8568寄存器的32bit数据
* @param PreConbyte: 4bit-Prefix bits + 4bit-control bits
* @param Addressbyte：4bit-Address bits
* @param Datashort: 16bit-Data bits
* @param Featurebyte：4bit-Feature bits
*/
static uint32_t ChatToInt(uint8_t PreConbyte, uint8_t Addressbyte, uint16_t Datashort, uint8_t Featurebits)
{
	uint32_t ret_val = 0;

	Addressbyte &= 0x0f;
	Featurebits &= 0x0f;
	ret_val = PreConbyte;
	ret_val <<= 4;
	ret_val |= Addressbyte;
	ret_val <<= 16;
	ret_val |= Datashort;
	ret_val <<= 4;
	ret_val |= Featurebits;

	return ret_val;
}


/**
* @brief DAC8568指定通道写数据
* @param Addressbyte: 0-7对应通道A到通道H
* @param Datashort：寄存器SR的32 bit数据
*/
static void DAC8568_Write_passageway(uint8_t Addressbyte, uint16_t Datashort)
{
	uint32_t SRData; //发送给DA8568移位寄存器SR的值
	SRData = ChatToInt(PrefixControlbyte, Addressbyte, Datashort, Featurebyte);
	SYNC_CLR;
	Mcpdely();
	SPI_SendByte((SRData & 0xFF000000) >> 24); //发送DB31-DB24位
	SPI_SendByte((SRData & 0xFF0000) >> 16); //发送DB23-DB16位
	SPI_SendByte((SRData & 0xFF00) >> 8); //发送DB15-DB8位
	SPI_SendByte(SRData & 0xFF); //发送DB7-DB0位
	SYNC_SET;
	Mcpdely();
}


/**
* @brief DAC8568写指定命令
* @param Addressbyte: 0-7对应通道A到通道H
* @param Datashort：寄存器SR的32 bit数据
*/
static void DAC8568_Write_Command(uint8_t command)
{
	switch(command)
	{
		//给内部基准电压上电 - 静态模式
		//注意：当所有 DAC 掉电时，基准电压会掉电；当任何DAC上电时，基准电压会上电
		case SETUP_INTERNAL_REGISTER:
		{
			SYNC_CLR;
			SPI_SendByte(0x08); //发送DB31-DB24位
			SPI_SendByte(0); //发送DB23-DB16位
			SPI_SendByte(0); //发送DB15-DB8位
			SPI_SendByte(0x01); //发送DB7-DB0位
			SYNC_SET;
			break;
		}

		//通过将相应位设置为“1”，为DAC A、B、C、D、E、F、G、H通电
		case POWER_UP:
		{
			SYNC_CLR;
			SPI_SendByte(0x04); //发送DB31-DB24位
			SPI_SendByte(0); //发送DB23-DB16位
			SPI_SendByte(0); //发送DB15-DB8位
			SPI_SendByte(0xff); //发送DB7-DB0位
			SYNC_SET;
			break;
		}
		//重启
		case RESET:
		{
			SYNC_CLR;
			SPI_SendByte(0x07); //发送DB31-DB24位
			SPI_SendByte(0); //发送DB23-DB16位
			SPI_SendByte(0); //发送DB15-DB8位
			SPI_SendByte(0); //发送DB7-DB0位
			SYNC_SET;
			break;
		}
	}
}

 

/**
* @brief 设置DAC8568通道 电压
* @param mCH:通道，0-7
* @param mVol：设置的电压值
*/
void DAC8568_SetVolt(unsigned char Ch, float Vol)
{
	float mDatafloat;
	uint16_t mDtashort;
	mDatafloat = Vol * 65535 / 5.0f;//对于CD版本的8568,增益为2
	
	mDtashort = (uint16_t)mDatafloat;
	SYNC_SET;
	Mcpdely();
	
	switch(Ch){
		case 0://DA8568的A通道 
		{
			DAC8568_Write_passageway(AddressOutA, mDtashort);
			break;
		}
		case 1: //DA8568的B通道
		{
			DAC8568_Write_passageway(AddressOutB, mDtashort);
			break;
		}
		case 2: //DA8568的C通道
		{
			DAC8568_Write_passageway(AddressOutC, mDtashort);
			break;
		}
		case 3: //DA8568的D通道
		{
			DAC8568_Write_passageway(AddressOutD, mDtashort);
			break;
		}
		case 4: //DA8568的E通道
		{
			DAC8568_Write_passageway(AddressOutE, mDtashort);
			break;
		}
		case 5: //DA8568的F通道
		{
			DAC8568_Write_passageway(AddressOutF, mDtashort);
			break;
		}
		case 6: //DA8568的G通道
		{
			DAC8568_Write_passageway(AddressOutG, mDtashort);
			break;
		}
		case 7: //DA8568的H通道
		{
			DAC8568_Write_passageway(AddressOutH, mDtashort);
			break;
		}
	}
}


//DA8568初始化
void DAC8568_Init(void)
{
	LDAC_CLR;
	CLR_SET;
	DAC8568_Write_Command(RESET); //重启
	DAC8568_Write_Command(POWER_UP); //通过将相应位设置为“1”，为DAC A、B、C、D、E、F、G、H通电
	DAC8568_Write_Command(SETUP_INTERNAL_REGISTER); //给内部基准电压上电 - 静态模式
}

