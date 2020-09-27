#pragma once

struct gpio_reg {
    /* 0x04: GPIO Pin Level Register */
    union {
        struct {
            uint32_t GPLR   : 32;  /* [31:0]  r/o */
        } BF;
        uint32_t WORDVAL;
    } GPLR;

    /* 0x08: GPIO Pin Direction Register */
    union {
        struct {
            uint32_t GPDR   : 32;  /* [31:0]  r/w */
        } BF;
        uint32_t WORDVAL;
    } GPDR;

    /* 0x0c - x4c: RESERVED */
    union {
        uint32_t WORDVAL;
	} RESERVED[0x12];

    /* 0x50: GPIO Read State Register */
    union {
        struct {
            uint32_t GPCR   : 32;  /* [31:0]  w/o */
        } BF;
        uint32_t WORDVAL;
    } GPRS;

};

typedef volatile struct gpio_reg gpio_reg_t;

#ifdef GPIO_IMPL
BEGIN_REG_SECTION(gpio_registers)
gpio_reg_t GPIOREG;
END_REG_SECTION(gpio_registers)
#else
extern gpio_reg_t GPIOREG;
#endif