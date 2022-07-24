/*
 * AS5047P.c
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */

#include "AS5047P.h"
#include"timer.h"
#include"main.h"
//データシートに記載されている手順に従い、SPIをデュプレックスマスター、2バイトモード、低クロック極性、フェーズ2、ソフトウェアイネーブルとして構成します
// CSNはSPIチップセレクトイネーブル信号、低レベルイネーブルであり、出力モードとして構成されています。必要に応じてピン番号を変更できます。
extern SPI_HandleTypeDef hspi2;
float angle[2] = { 0 };

AS5047_TypeDef Devs[] = { { &hspi2, GPIOA, GPIO_PIN_8 }, { &hspi2, GPIOA,
GPIO_PIN_4 } };

#define assert_idx(__devidx)   if(__devidx<0 && __devidx >sizeof(Devs)/sizeof(AS5047_TypeDef) ) error_inf_loop();
#define CS_1(__devidx) HAL_GPIO_WritePin(Devs[__devidx].CSNport,Devs[__devidx].CSNpin,GPIO_PIN_SET)
#define CS_0(__devidx) HAL_GPIO_WritePin(Devs[__devidx].CSNport,Devs[__devidx].CSNpin,GPIO_PIN_RESET)

void error_inf_loop() {
	while (1)
		;
}

uint16_t Parity_bit_Calculate(uint16_t data_2_cal) {
	uint16_t parity_bit_value = 0;
	//　下位ビットからパリティのカウントを開始します
	while (data_2_cal != 0) {
		//（（（⑤^④）^③）^②）^ ①——式1は、⑤と④が異なることを前提としており、⑤^④の演算結果は1であり、1であることを意味します。式1は次のように変換できます：（（1 ^③）^②）^①-式2
		parity_bit_value ^= data_2_cal;
		data_2_cal >>= 1;
	}
	return (parity_bit_value & 0x1);
}

uint16_t SPI_ReadWrite_OneByte(int devidx, uint16_t _txdata) {
	assert_idx(devidx);
	CS_0(devidx);
	uint16_t rxdata;
	//　警告は気にしないでください。アドレスデータは切り捨てられません。HALライブラリは、16バイトのデータ形式に従った構成に従って16バイトを送信します。
	if (HAL_SPI_TransmitReceive(Devs[devidx].hspin, (uint8_t*) &_txdata,
			(uint8_t*) &rxdata, 1, 100) != HAL_OK) {
		rxdata = 0;
		printf("encspiERR\n");
	}
	CS_1(devidx);
	return rxdata;
}
uint16_t AS5047_WriteData(int devidx, uint16_t addr, uint16_t data) {
	//　　アドレス命令を送信します
	//　＆0x3fffは、パリティ計算のために13：0のデータデータを取得します
	if (Parity_bit_Calculate(addr & 0x3fff) == 1)
		addr |= 0x8000;  // 15ビットを1偶数パリティに設定
	CS_0(devidx);
	SPI_ReadWrite_OneByte(devidx, addr);
	CS_1(devidx);

	//　データ命令を送信します
	if (Parity_bit_Calculate(data & 0x3fff) == 1)
		data |= 0x8000;

	uint16_t feedback;
	CS_0(devidx);
	feedback = SPI_ReadWrite_OneByte(devidx, data);
	CS_1(devidx);

	return feedback;
}
uint16_t AS5047_ReadData(int devidx, uint16_t addr) {
	uint16_t data;
	if (Parity_bit_Calculate(addr) == 0)
		addr |= 0x8000; //1000 0000 0000 0000
	addr |= AS5047_COMMAND_READ; //0100 0000 0000 0000
	SPI_ReadWrite_OneByte(devidx, addr);
	data = SPI_ReadWrite_OneByte(devidx, NOP_AS5047P_VOL_REG_ADD); //ANGLECOM_AS5047P_VOL_REG_ADD=11 1111 1111
	data &= 0x3fff;

	SPI_ReadWrite_OneByte(devidx, addr);
	//	データ= SPI_ReadWrite_OneByte（devidx、addr）;
	//　ここでパリティチェックを実行して、正しいデータが受信されているかどうかを判断できますが、実行する必要はありません。15、14ビットを削除するだけです。
	data &= 0x3fff;
	return data;
}

void AS5047_Init(void) {
	//设置ABI模式，输出分辨1024.
	for (int i = 0; i < sizeof(Devs) / sizeof(AS5047_TypeDef); i++) {
		AS5047_WriteData(i, SETTINGS1_AS5047P_nVOL_REG_ADD, 5); //0000 0101
		Delay_ms(100);
		AS5047_WriteData(i, SETTINGS2_AS5047P_nVOL_REG_ADD, 0);
		Delay_ms(100);
	}

}
void AS5047_SetZeroPosition(int devidx) {
	uint16_t DIAAGC = AS5047_ReadData(devidx, DIAAGC_AS5047P_VOL_REG_ADD);
	printf("id=%ddiaagc=%d\n", devidx, DIAAGC);
	//　获取当前角度
	Delay_ms(100);
	uint16_t ANGLEUNC = AS5047_ReadData(devidx, ANGLEUNC_AS5047P_VOL_REG_ADD);
	printf("id=%dANGLEUNC=%d\n", devidx, ANGLEUNC);
	//												ANGLEUNC是13:0 14个有效数字，右移6获取高8位。
	Delay_ms(100);
	AS5047_WriteData(devidx, ZPOSM_AS5047P_nVOL_REG_ADD,
			(ANGLEUNC >> 6) & 0x00ff);
	Delay_ms(100);
	//																							得到低6位 & 11 1111
	AS5047_WriteData(devidx, ZPOSL_AS5047P_nVOL_REG_ADD, ANGLEUNC & 0x003f);
}

void AS5047_Diagnostics(void) {
	;
}

uint16_t AS5047D_Get_MAGCORDIC_Value(int devidx) {
	unsigned int CORDICMAG = AS5047_ReadData(devidx, MAG_AS5047P_VOL_REG_ADD);
	return CORDICMAG;
}

unsigned int AS5047P_Get_AGC_Value(int devidx) {
	unsigned int DIAAGC = AS5047_ReadData(devidx, DIAAGC_AS5047P_VOL_REG_ADD);
	return (unsigned char) ((DIAAGC >> 8) & 0x00FF);
}

uint16_t AS5047_Get_ZeroPosition(int devidx) {
	uint16_t ZPOSM = AS5047_ReadData(devidx, ZPOSM_AS5047P_nVOL_REG_ADD);
	uint16_t ZPOSL = AS5047_ReadData(devidx, ZPOSL_AS5047P_nVOL_REG_ADD);
	//将高八位和低6位拼起来
	return (ZPOSM << 6) & (ZPOSL & 0x003f);
}

uint16_t AS5047_Get_ERRFL(int devidx) {
	return AS5047_ReadData(devidx, ERRFL_AS5047P_VOL_REG_ADD);
}

float AS5047_ReloadAngle(int devidx) {
	angle[devidx] = ((float) (AS5047_ReadData(devidx,
	ANGLEUNC_AS5047P_VOL_REG_ADD))) / (16383.0f / 360.0f) * PI / 180.0f; //AS5047_ReadSPI(0);
//	printf("id=%dang=%d\n",devidx,ang);
	return angle[devidx];
}
float AS5047_GetAngle(int devidx) {
	return angle[devidx];
}

float AS5047_GetSpeed(int devidx, float angle_prev) {
//	int8_t direction = AS5047_GetDirection(devidx, angle_prev);

	float move = angle[devidx] - angle_prev;

	//変化点を1023から0//へ移動したときの補正
			if( move < -1.0f*PI && angle_prev >PI){
//				printf("1023-0 %f-%f=%f\n",angle[devidx],angle_prev,move);
				move += (2.0f * PI);
			}
			//変化点を0から1023へ移動したときの補正
			else if(move > PI*1.0f && angle_prev<=PI){
//				printf("0-1023 %f-%f=%f\n",angle[devidx],angle_prev,move);
				move -= (2.0f * PI);
			}
//
//
//						snprintf(buf, 100, "MOVE=%f\n",move);
//						print_dma(buf, 100);

//	if (direction == AS5047_ROTATE_FORWERD && move < -4) {
//		move += 2 * PI;
//	}
//
//	if (direction == AS5047_ROTATE_REVERCE && move > 4) {
//		move -= 2 * PI;
//	}
	return move * TIRE_DIAMETER/2.0f;
}

int8_t AS5047_GetDirection(int devidx, float angle_prev) {
	static int8_t direction[2] = { AS5047_ROTATE_NON };
	float move = angle[devidx] - angle_prev;

	if (direction[devidx] == AS5047_ROTATE_FORWERD && move < -4) {
		move =1;
	}

	if (direction[devidx] == AS5047_ROTATE_REVERCE && move > 4) {
		move = -1;
	}

//	printf("move=%f\n",move);
		if (move > 0.0f) {
			direction[devidx] = AS5047_ROTATE_FORWERD;
		} else if (move < 0.0f) {
			direction[devidx] = AS5047_ROTATE_REVERCE;
		} else {
			direction[devidx] = AS5047_ROTATE_NON;
		}
//	printf("id=%dmove=%fdirection=%d\n", devidx, move, direction[devidx]);
	return direction[devidx];
}
