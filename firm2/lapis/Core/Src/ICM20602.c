#include "icm20602.h"
#include"timer.h"
#include"main.h"
//========ICM20602 register address=======================
/********************************************
 *All register addresses are 0 after reset, except
 *Register 26  CONFIG				= 0x80
 *Register 107 Power Management 1 	= 0x41
 *Register 117 WHO_AM_I 				= 0x12
 *********************************************/
//Gyro temperature compensation
#define	ICM20_XG_OFFS_TC_H				0x04
#define	ICM20_XG_OFFS_TC_L				0x05
#define	ICM20_YG_OFFS_TC_H				0x07
#define	ICM20_YG_OFFS_TC_L				0x08
#define	ICM20_ZG_OFFS_TC_H				0x0A
#define	ICM20_ZG_OFFS_TC_L				0x0B
//Acceleration self-check output (set at the time of production, used to compare with the user's self-check output value)
#define	ICM20_SELF_TEST_X_ACCEL			0x0D
#define	ICM20_SELF_TEST_Y_ACCEL			0x0E
#define	ICM20_SELF_TEST_Z_ACCEL			0x0F
//Gyro static offset
#define	ICM20_XG_OFFS_USRH				0x13
#define	ICM20_XG_OFFS_USRL				0x14
#define	ICM20_YG_OFFS_USRH				0x15
#define	ICM20_YG_OFFS_USRL				0x16
#define	ICM20_ZG_OFFS_USRH				0x17
#define	ICM20_ZG_OFFS_USRL				0x18

#define	ICM20_SMPLRT_DIV				0x19
#define	ICM20_CONFIG					0x1A
#define	ICM20_GYRO_CONFIG				0x1B
#define	ICM20_ACCEL_CONFIG				0x1C
#define	ICM20_ACCEL_CONFIG2				0x1D
#define	ICM20_LP_MODE_CFG				0x1E

//Sport wake up acceleration threshold
#define	ICM20_ACCEL_WOM_X_THR			0x20
#define	ICM20_ACCEL_WOM_Y_THR			0x21
#define	ICM20_ACCEL_WOM_Z_THR			0x22

#define	ICM20_FIFO_EN					0x23
#define	ICM20_FSYNC_INT					0x36
#define	ICM20_INT_PIN_CFG				0x37
//#define	ICM20_INT_ENABLE				0x38
#define	ICM20_FIFO_WM_INT_STATUS		0x39
#define	ICM20_INT_STATUS				0x3A

//Acceleration output
#define	ICM20_ACCEL_XOUT_H				0x3B
#define	ICM20_ACCEL_XOUT_L				0x3C
#define	ICM20_ACCEL_YOUT_H				0x3D
#define	ICM20_ACCEL_YOUT_L				0x3E
#define	ICM20_ACCEL_ZOUT_H				0x3F
#define	ICM20_ACCEL_ZOUT_L				0x40
//Temperature output
#define	ICM20_TEMP_OUT_H				0x41
#define	ICM20_TEMP_OUT_L				0x42
//Angular velocity output
#define	ICM20_GYRO_XOUT_H				0x43
#define	ICM20_GYRO_XOUT_L				0x44
#define	ICM20_GYRO_YOUT_H				0x45
#define	ICM20_GYRO_YOUT_L				0x46
#define	ICM20_GYRO_ZOUT_H				0x47
#define	ICM20_GYRO_ZOUT_L				0x48
//Gyro self-check output
#define	ICM20_SELF_TEST_X_GYRO			0x50
#define	ICM20_SELF_TEST_Y_GYRO			0x51
#define	ICM20_SELF_TEST_Z_GYRO			0x52

#define	ICM20_FIFO_WM_TH1				0x60
#define	ICM20_FIFO_WM_TH2				0x61
#define	ICM20_SIGNAL_PATH_RESET			0x68
#define	ICM20_ACCEL_INTEL_CTRL 			0x69
#define	ICM20_USER_CTRL					0x6A
//power control
#define	ICM20_PWR_MGMT_1				0x6B
#define	ICM20_PWR_MGMT_2				0x6C

#define	ICM20_I2C_IF					0x70
#define	ICM20_FIFO_COUNTH				0x72
#define	ICM20_FIFO_COUNTL				0x73
#define	ICM20_FIFO_R_W					0x74

#define	ICM20_WHO_AM_I 					0x75
//Acceleration static offset
#define	ICM20_XA_OFFSET_H				0x77
#define	ICM20_XA_OFFSET_L				0x78
#define	ICM20_YA_OFFSET_H				0x7A
#define	ICM20_YA_OFFSET_L				0x7B
#define	ICM20_ZA_OFFSET_H				0x7D
#define	ICM20_ZA_OFFSET_L 				0x7E
//===========================================================

extern SPI_HandleTypeDef hspi1;

static float _accel_scale;
static float _gyro_scale;
float gyro_drift;
float accel_drift;

static uint8_t tx, rx;
static uint8_t tx_buff[14];
//static uint8_t mpu_buff[14];
#define ICM20602_ADDRESS	0xD2

uint8_t icm20602_read_buffer(uint8_t const regAddr, uint8_t *pData, uint8_t len) {
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, 0);
	tx = regAddr | 0x80;
	tx_buff[0] = tx;
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 55);
	HAL_SPI_TransmitReceive(&hspi1, tx_buff, pData, len, 55);
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, 1);
	return 0;
}

uint8_t icm20602_write_reg(uint8_t reg, uint8_t val) {

	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, 0);
	tx = reg & 0x7F;
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 55);
	tx = val;
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 55);
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, 1);

	return 0;
}

uint8_t icm20602_read_reg(uint8_t reg) {
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, 0);
	tx = reg | 0x80;
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 55);
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 55); //This should just be a random number
	HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin, 1); //The source code sent is ff

	return rx;
}

uint8_t icm20602_init() {
	char buf[100] = { 0 };
	if (icm20602_write_reg(ICM20_PWR_MGMT_1, 0x80)) // reset, bit 0x41 after reset, sleep mode,
			{

		snprintf(buf, 100, "icm_20602 reset fail\r\n");
		print_dma(buf, 100);
		return 1;
	}

	Delay_ms(100);
	icm20602_write_reg(ICM20_PWR_MGMT_1, 0x01); //Turn off sleep and automatically select the clock
	Delay_ms(100);

	Delay_ms(100);
	icm20602_write_reg(ICM20_SMPLRT_DIV, 0); //The number of divisions = 0+1, the data output rate is the internal sampling rate
	Delay_ms(100);
	icm20602_write_reg(ICM20_CONFIG, DLPF_BW_20); //GYRO low pass filter setting
	Delay_ms(100);
	icm20602_write_reg(ICM20_ACCEL_CONFIG2, ACCEL_AVER_4 | ACCEL_DLPF_BW_21); //ACCEL low pass filter setting
	Delay_ms(100);

	icm20602_set_accel_fullscale(ICM20_ACCEL_FS_8G);
	Delay_ms(100);
	icm20602_set_gyro_fullscale(ICM20_GYRO_FS_2000);

	Delay_ms(100);
	icm20602_get_gyro_drift();
	icm20602_get_accel_drift();

	snprintf(buf, 100, "id=%x gyro_drift=%f accel_drift=%f\n",
			icm20602_read_reg(ICM20_WHO_AM_I), gyro_drift, accel_drift);
	print_dma(buf, 100);

	Delay_ms(100);

	return 0;
}

uint8_t icm20602_set_gyro_fullscale(uint8_t fs) {
	switch (fs) {
	case ICM20_GYRO_FS_250:
		_gyro_scale = 1.0f / 131.068f;	//32767/250
		break;
	case ICM20_GYRO_FS_500:
		_gyro_scale = 1.0f / 65.534f;
		break;
	case ICM20_GYRO_FS_1000:
		_gyro_scale = 1.0f / 32.767f;
		break;
	case ICM20_GYRO_FS_2000:
		_gyro_scale = 1.0f / 16.4f;
		break;
	default:
		fs = ICM20_GYRO_FS_2000;
		_gyro_scale = 1.0f / 16.3835f;
		break;

	}

	return icm20602_write_reg(ICM20_GYRO_CONFIG, fs);

}

uint8_t icm20602_set_accel_fullscale(uint8_t fs) {
	switch (fs) {
	case ICM20_ACCEL_FS_2G:
		_accel_scale = 1.0f / 16348.0f;
		break;
	case ICM20_ACCEL_FS_4G:
		_accel_scale = 1.0f / 8192.0f;
		break;
	case ICM20_ACCEL_FS_8G:
		_accel_scale = 1.0f / 4096.0f;
		break;
	case ICM20_ACCEL_FS_16G:
		_accel_scale = 1.0f / 2048.0f;
		break;
	default:
		fs = ICM20_ACCEL_FS_8G;
		_accel_scale = 1.0f / 4096.0f;
		break;

	}
	return icm20602_write_reg(ICM20_ACCEL_CONFIG, fs);
}

uint8_t icm20602_get_accel_adc(int16_t *accel) {
	uint8_t buf[2];
	if (icm20602_read_buffer(ICM20_ACCEL_YOUT_H, buf, 2))
		return 1;

	*accel = ((int16_t) buf[0] << 8) + buf[1];
	return 0;
}

uint8_t icm20602_get_gyro_adc(int16_t *gyro) {
	uint8_t buf[2];
	if (icm20602_read_buffer(ICM20_GYRO_ZOUT_H, buf, 2))
		return 1;
	*gyro = (buf[0] << 8) + buf[1];
	return 0;
}
uint8_t icm20602_get_gyro(float *gyro) {
	int16_t gyro_adc;
	if (icm20602_get_gyro_adc(&gyro_adc))
		return 1;

	*gyro = _gyro_scale * gyro_adc;
	*gyro -= gyro_drift;
	*gyro *= 1.00f;
	return 0;
}
uint8_t icm20602_get_accel(float *accel) {
	int16_t accel_adc;
	if (icm20602_get_accel_adc(&accel_adc))
		return 1;
	*accel = _accel_scale * accel_adc;
	*accel -= accel_drift;
	return 0;
}

float icm20602_get_temp() {
	int16_t temp_adc;
	uint8_t buf[2];
	if (icm20602_read_buffer(ICM20_TEMP_OUT_H, buf, 2))
		return 0.0f;

	temp_adc = (buf[0] << 8) + buf[1];

	return (25.0f + (float) temp_adc / 326.8f);
}

void icm20602_get_deg(float *degree, float gyro, float gyro_prev, float t) {
	*degree += t * (gyro_prev +  (gyro - gyro_prev)* 0.1f);
//	if (*degree > 360.0f) {
//		*degree -= 360.0f;
//	}
//	if (*degree < -360.0f) {
//		*degree += 360.0f;
//	}

	return;
}

void icm20602_get_gyro_drift(void) {
	float buff = 0, drift = 0;
	gyro_drift = 0;

	for (int i = 0; i < 100; i++) {
		icm20602_get_gyro(&buff);
		drift += buff;
		Delay_ms(10);
	}
	gyro_drift = drift / 100.0f;
	return;
}

void icm20602_get_accel_drift(void) {
	float buff = 0, drift = 0;
	accel_drift = 0;

	for (int i = 0; i < 100; i++) {
		icm20602_get_accel(&buff);
		drift += buff;
		Delay_ms(10);
	}
	accel_drift = drift / 100.0f;
	return;
}

