#pragma once

struct pinmux_reg {                                           
    /* 0x000-0x13c: GPIO_PINMUX Configuration register */
    union {                                                    
        struct {                                               
            uint32_t FSEL_XR          :  4;  /* [3:0]   r/w */ 
            uint32_t RESERVED_12_4    :  8;  /* [11:4]  rsvd */
            uint32_t DI_EN            :  1;  /* [12]     r/w */
            uint32_t PIO_PULLDN_R     :  1;  /* [13]    r/w */ 
            uint32_t PIO_PULLUP_R     :  1;  /* [14]    r/w */ 
            uint32_t PIO_PULL_SEL_R   :  1;  /* [15]    r/w */ 
            uint32_t RESERVED_31_16   : 16;  /* [31:16] rsvd */ 
        } BF;                                                  
        uint32_t WORDVAL;                                      
    } GPIO_PINMUX[80];   
                                           
    /* 0x140: Serial Flash HOLDn Configuration register */
    union {
        struct {
            uint32_t RESERVED_2_0     :  3;  /* [2:0]   rsvd */
            uint32_t DI_EN            :  1;  /* [3]     r/w */
            uint32_t RESERVED_31_4    : 28;  /* [31:4] rsvd */
        } BF;
        uint32_t WORDVAL;
    } SFLASH_HOLDn;

    uint8_t zReserved0x144[4];  /* pad 0x144 - 0x147 */

    /* 0x148: Serial Flash DIO Configuration register */
    union {
        struct {
            uint32_t RESERVED_2_0     :  3;  /* [2:0]   rsvd */
            uint32_t DI_EN            :  1;  /* [3]     r/w */
            uint32_t RESERVED_31_4    : 28;  /* [31:4] rsvd */
        } BF;
        uint32_t WORDVAL;
    } SFLASH_DIO;

    /* 0x14C: Serial Flash Write Protect Configuration register */
    union {
        struct {
            uint32_t RESERVED_2_0     :  3;  /* [2:0]   rsvd */
            uint32_t DI_EN            :  1;  /* [3]     r/w */
            uint32_t RESERVED_31_4    : 28;  /* [31:4] rsvd */
        } BF;
        uint32_t WORDVAL;
    } SFLASH_WP;

    /* 0x150: Serial Flash DO Configuration register */
    union {
        struct {
            uint32_t RESERVED_2_0     :  3;  /* [2:0]   rsvd */
            uint32_t DI_EN            :  1;  /* [3]     r/w */
            uint32_t RESERVED_31_4    : 28;  /* [31:4] rsvd */
        } BF;
        uint32_t WORDVAL;
    } SFLASH_DO;
};                                                             
                                                               
typedef volatile struct pinmux_reg pinmux_reg_t;             

#ifdef PINMUX_IMPL
BEGIN_REG_SECTION(pinmux_registers)
pinmux_reg_t PINMUXREG;
END_REG_SECTION(pinmux_registers)
#else
extern pinmux_reg_t PINMUXREG;
#endif