#include "flash.h"
#include"main.h"
#include <string.h>

/*
 * 説明：flush sector1の内容を消去
 * 引数：無し
 * 戻り値：無し
 */
void eraseFlash(void) {
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_PAGES;  // select sector
	erase.Banks = FLASH_BANK_1;               // set selector1
	erase.Page = 127;        // set to erase one sector
	erase.NbPages = 1; // set voltage range (2.7 to 3.6V)

	uint32_t pageError = 0;
	    // erase sector
	HAL_FLASHEx_Erase(&erase, &pageError);
}

/*
 * 説明：flush sector1に書き込み
 * 引数：address 書き込み先先頭アドレス
 * 　　　data 書き込みデータ
 * 　　　size 書き込むデータのサイズ(byte)
 * 戻り値：無し
 */
void writeFlash(uint32_t address, uint64_t *data, uint32_t size) {
	printf("write flash\n");
	HAL_FLASH_Unlock();        // unlock flash
	eraseFlash();            // erease sector1
	for (uint32_t add = address; add < (address + size); add+=8) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, add, *data);
		data++;  // add data pointer
	}

	HAL_FLASH_Lock();        // lock flash
}

/*
 * 説明：flush sector1から読み出し
 * 引数：address 読み出すデータの先頭アドレス
 * 　　　data データ格納先のアドレス
 * 　　　size データ格納先のサイズ(byte)
 * 戻り値：無し
 */
void loadFlash(uint32_t address, uint8_t *data, uint32_t size) {
	printf("road flash\n");
	memcpy(data, (uint8_t*) address, size); // copy data
}
