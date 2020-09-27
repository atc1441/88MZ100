
PROJECT_NAME=test

CC=armgcc/bin/arm-none-eabi-gcc
AS=armgcc/bin/arm-none-eabi-as
READELF=armgcc/bin/arm-none-eabi-readelf
OBJCOPY=armgcc/bin/arm-none-eabi-objcopy

#change this to the correct one if its different, will be shown after compiling
ENTRYPOINT=0x1004d9

build: clean compile run

compile:
	@$(AS) -mcpu=cortex-m3 --gdwarf-2 -mthumb-interwork -o build/startup.o startup.S
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_clock.c -o build/mz100_clock.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_driver.c -o build/mz100_driver.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_pinmux.c -o build/mz100_pinmux.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_ssp.c -o build/mz100_ssp.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_rtc.c -o build/mz100_rtc.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c $(PROJECT_NAME).c -o build/$(PROJECT_NAME).o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_gpio.c -o build/mz100_gpio.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c xflash.c -o build/xflash.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c mz100_uart.c -o build/mz100_uart.o
	@$(CC) -mcpu=cortex-m3 -g -Os -mthumb -Wall -fdata-sections -ffunction-sections -c epd.c -o build/epd.o
	@$(CC) -lc -lc -lnosys -L. -T mz100.ld -fPIE --specs=nosys.specs -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -Os -flto -ffunction-sections -fdata-sections -DARM_GNU build/startup.o build/mz100_clock.o build/mz100_driver.o build/mz100_pinmux.o build/mz100_ssp.o build/mz100_rtc.o build/mz100_gpio.o build/xflash.o build/mz100_uart.o build/epd.o build/$(PROJECT_NAME).o -o $(PROJECT_NAME).axf
	@$(READELF) -h $(PROJECT_NAME).axf 
	@$(OBJCOPY) -v -O binary $(PROJECT_NAME).axf $(PROJECT_NAME).bin
	
clean:
	@
run:
	@openocd -d0 -c "source [find openocd.cfg]"; -c "load_image $(PROJECT_NAME).axf"; -c "resume $(ENTRYPOINT)"; -c "shutdown";