#include "/Projekty/C(C++) projects/AVR projects/Atmega328p_Peripherals/Atmega328p_Peripherals/inc/i2c.h"

static uint16_t I2C_slave_write(uint16_t ADDR)
{
	return ((ADDR << 1) | TW_WRITE);
}

static uint16_t I2C_slave_read(uint16_t ADDR)
{
	return ((ADDR << 1) | TW_READ);
}

/**
 * @brief I2C send start condition 
 */
static uint16_t I2C_send_start();

/**
 * @brief I2C send stop condition 
 */
static void I2C_send_stop();

/**
 * @brief I2C send slave address 
 * @param addres of slave
 */
static uint16_t I2C_send_slave_address(uint8_t slaveAddress);

/**
 * @brief I2C send data
 * @param data to send
 */
static uint16_t I2C_write_data(uint8_t data);

/**
 * @brief I2C receive data 
 * @param read acknowledge -> 1 = true, 0 = false
 */
static uint8_t I2C_read_data(uint8_t readAcknowledge);



static uint16_t I2C_send_start()
{
	// Send start condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); 
	
	// Wait for TWINT Flag set. This indicates that the START condition has been transmitted
	while (!(TWCR &(1<<TWINT))); 
	
	if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START)
	{
		return TW_STATUS;
	}
	
	return 0; // Success
}

static void I2C_send_stop()
{
	// Transmit stop condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); 
}

static uint16_t I2C_send_slave_address(uint8_t slaveAddress)
{
	// Send slave address 
	TWDR = slaveAddress; 
	
	// Clear TWINT bit in TWCR to start transmission of addres
	TWCR = (1<<TWINT) | (1<<TWEN); 
	
	// This indicates that the slave address has been transmitted, and ACK/NACK has been received
	while (!(TWCR & (1<<TWINT))); 
	
	if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
	{
		// ERROR();
		return TW_STATUS;
	}
	
	return 0; // success
}

static uint16_t I2C_write_data(uint8_t data)
{
	// Load DATA into TWDR Register.
	TWDR = data;
	
	// Clear TWINT bit in TWCR to start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN); 
	
	// Wait for TWINT Flag set. This indicates that the DATA has been transmitted, and ACK/NACK has been received
	while (!(TWCR & (1<<TWINT))); 
	
	if (TW_STATUS != TW_MT_DATA_ACK)
	{
		// ERROR();
		return TW_STATUS;
	}
	
	return 0; // Success
}

static uint8_t I2C_read_data(uint8_t readAcknowledge)
{
	if (readAcknowledge == 1)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_ACK)
		{
			return TW_STATUS;
		}
	}
	else
	{
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_NACK)
		{
			return TW_STATUS;
		}
	}
	uint8_t data = TWDR;
	return data;
}

void I2C_init(uint8_t freqMode, uint8_t pullupEnable)
{
	DDRC  |= (1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN);
	if (pullupEnable == 1)
	{
		PORTC |= (1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN);
	}
	else
	{
		PORTC &= ~((1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN));
	}
	DDRC  &= ~((1 << I2C_SDA_PIN) | (1 << I2C_SCL_PIN));
	
	if(freqMode == 0)
	{
		// Set bit rate register 72 and prescaler to 1 resulting in SCL_freq = 16MHz/(16 + 2*72*1) = 100KHz
		
		TWBR = 72;
	}
	else if(freqMode == 1)
	{
		// Set bit rate register 24 and prescaler to 1 resulting in SCL_freq = 16MHz/(16 + 2*24*1) = 250KHz
		
		TWBR = 24;
	}
	else
	{
		// Set bit rate register 12 and prescaler to 1 resulting in SCL_freq = 16MHz/(16 + 2*12*1) = 400KHz	
		TWBR = 12;
	}
}


uint16_t I2C_transmit(uint8_t slaveAddres, uint8_t* data, uint8_t length, uint8_t repeatStart)
{
	uint16_t error_code;
	
	// Send START condition 
	error_code = I2C_send_start();
	if (error_code != 0)
	{
		return error_code;
	}
	
	// Send slave address with WRITE flag
	error_code = I2C_send_slave_address(I2C_slave_write(slaveAddres));
	if (error_code != 0)
	{
		return error_code;
	}
	
	// Send data byte in single or burst mode
	for (int i = 0; i < length; ++i)
	{
		error_code = I2C_write_data(data[i]);
		if (error_code != 0)
		{
			return error_code;
		}
	}
	
	if (!repeatStart)
	{
		// Send STOP condition
		I2C_send_stop();
	}
	
	return 0;
}


uint16_t I2C_receive(uint8_t slaveAddres, uint8_t* data, uint8_t length)
{
	uint16_t error_code;
	
	// Send START condition
	error_code = I2C_send_start();
	if (error_code != 0)
	{
		return error_code;
	}
	
	// Write slave address with READ flag 
	error_code = I2C_send_slave_address(I2C_slave_read(slaveAddres));
	if (error_code != 0)
	{
		return error_code;
	}
	
	// Read single or multiple data byte and send ack
	for (int i = 0; i < length-1; ++i)
	{
		data[i] = I2C_read_data(I2C_READ_ACK);
	}
	data[length-1] = I2C_read_data(I2C_READ_NACK);
	
	// Send STOP condition 
	I2C_send_stop();
	
	return 0;
}
