#!/usr/bin/python

import smbus, time

bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

DEVICE_ADDRESS = 0x04      #7 bit address (will be left shifted to add the read write bit)
DEVICE_REG_MODE1 = 0x00
DEVICE_REG_LEDOUT0 = 0x1d

#Write a single register
#bus.write_byte_data(DEVICE_ADDRESS, DEVICE_REG_MODE1, 0x80)

#Write an array of registers
while True:
	var = input("Please enter a number 0-127: ")
	print("You entered " + str(var))
	var2 = input("Please enter another number 0-127: ")
	ledout_values = [chr(int(var)), chr(int(var2))]
	print(ledout_values)
	bus.write_i2c_block_data(DEVICE_ADDRESS, DEVICE_REG_LEDOUT0, ledout_values)
	time.sleep(2)

	ledout_values = [chr(0), chr(12)]
	print(ledout_values)
	bus.write_i2c_block_data(DEVICE_ADDRESS, DEVICE_REG_LEDOUT0, ledout_values)
	time.sleep(3)

