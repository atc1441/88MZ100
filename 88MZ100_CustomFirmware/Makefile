
PROJECT_NAME=test

ARMGCC=../armgcc/bin/
CC=$(ARMGCC)arm-none-eabi-gcc
AS=$(ARMGCC)arm-none-eabi-as
OBJCOPY=$(ARMGCC)arm-none-eabi-objcopy

CC_FlAGS=-mcpu=cortex-m3 -g -O0 -mthumb -Wall -fdata-sections -ffunction-sections
CC_END_FLAGS=-lc -lnosys -L. -T mz100.ld -fPIE --specs=nosys.specs -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -O0 -flto -ffunction-sections -fdata-sections -DARM_GNU

build: clean compile flash_uart_flash

swd: clean compile flash_swd

uart: clean compile flash_uart

compile:
	@$(AS) -mcpu=cortex-m3 --gdwarf-2 -mthumb-interwork -o build/startup.o startup.S
	@$(CC) $(CC_FlAGS) -c epd.c -o build/epd.o
	@$(CC) $(CC_FlAGS) -c mz100_clock.c -o build/mz100_clock.o
	@$(CC) $(CC_FlAGS) -c mz100_driver.c -o build/mz100_driver.o
	@$(CC) $(CC_FlAGS) -c mz100_pinmux.c -o build/mz100_pinmux.o
	@$(CC) $(CC_FlAGS) -c mz100_ssp.c -o build/mz100_ssp.o
	@$(CC) $(CC_FlAGS) -c mz100_rtc.c -o build/mz100_rtc.o
	@$(CC) $(CC_FlAGS) -c $(PROJECT_NAME).c -o build/$(PROJECT_NAME).o
	@$(CC) $(CC_FlAGS) -c mz100_gpio.c -o build/mz100_gpio.o
	@$(CC) $(CC_FlAGS) -c xflash.c -o build/xflash.o
	@$(CC) $(CC_FlAGS) -c mz100_uart.c -o build/mz100_uart.o
	@$(CC) $(CC_END_FLAGS) build/epd.o build/startup.o build/mz100_clock.o build/mz100_driver.o build/mz100_pinmux.o build/mz100_ssp.o build/mz100_rtc.o build/mz100_gpio.o build/xflash.o build/mz100_uart.o build/$(PROJECT_NAME).o -o $(PROJECT_NAME).axf
	@$(OBJCOPY) -v -O binary $(PROJECT_NAME).axf $(PROJECT_NAME).bin
	
clean:
	@
	
flash_swd:
	@python3 flash_helper.py $(PROJECT_NAME)
	
flash_uart:
	@python3 88MZ100_Uart_flasher.py com6 write $(PROJECT_NAME).bin
	
flash_uart_flash:
	@python3 88MZ100_Uart_flasher.py com6 write_flash $(PROJECT_NAME).bin
	
flash_stock:
	@python3 88MZ100_Uart_flasher.py com6 write_flash stock.bin
	
flash_dump:
	@python3 88MZ100_Uart_flasher.py com6 read dump.bin