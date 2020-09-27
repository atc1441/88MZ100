/* File: startup_ARMCM3.S
 * Purpose: startup file for Cortex-M3 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V2.0
 * Date: 16 August 2013
 *
/* Copyright (c) 2011 - 2013 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/
	.syntax	unified
	.arch	armv7-m

	.section .stack
	.align	4
#ifdef __STACK_SIZE
	.equ	Stack_Size, __STACK_SIZE
#else
	.equ	Stack_Size, 0x4000
#endif
	.globl	__StackTop
	.globl	__StackLimit
__StackLimit:
	.space	Stack_Size
	.size	__StackLimit, . - __StackLimit
__StackTop:
	.size	__StackTop, . - __StackTop

	.section .heap
	.align	4
#ifdef __HEAP_SIZE
	.equ	Heap_Size, __HEAP_SIZE
#else
	.equ	Heap_Size, 0
#endif
	.globl	__HeapBase
	.globl	__HeapLimit
__HeapBase:
	.if	Heap_Size
	.space	Heap_Size
	.endif
	.size	__HeapBase, . - __HeapBase
__HeapLimit:
	.size	__HeapLimit, . - __HeapLimit

	.section .isr_vector
	.align	2
	.globl	__isr_vector
__isr_vector:
	.long	__StackTop            /* Top of Stack */
	.long	Reset_Handler         /* Reset Handler */
	.long	NMI_Handler           /* NMI Handler */
	.long	HardFault_Handler     /* Hard Fault Handler */
	.long	MemManage_Handler     /* MPU Fault Handler */
	.long	BusFault_Handler      /* Bus Fault Handler */
	.long	UsageFault_Handler    /* Usage Fault Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	SVC_Handler           /* SVCall Handler */
	.long	DebugMon_Handler      /* Debug Monitor Handler */
	.long	0                     /* Reserved */
	.long	PendSV_Handler        /* PendSV Handler */
	.long	SysTick_Handler       /* SysTick Handler */
	.long	RTC_IRQHandler        /* RTC_IRQ Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	RC32M_IRQHandler      /* RC32M_IRQHandler */
	.long	0                     /* not Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	ADC_IRQHandler        /* ADC_IRQHandler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	AES_IRQHandler        /* AES_IRQHandler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	GPIO_IRQHandler       /* GPIO_IRQHandler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	QSPI_IRQHandler       /* QSPI_IRQHandler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	UART0_IRQHandler      /* UART0_IRQHandler */
	.long	UART1_IRQHandler      /* UART1_IRQHandler */
	.long	ZIGBEE_IRQ_Handler    /* ZIGBEE_IRQ_Handler */
	.long	0                     /* Reserved */
	.long	ZIGBEE_IRQ1_Handler   /* ZIGBEE_IRQ1_Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	GPIO0_WAKEUP_handler  /* GPIO0_WAKEUP_handler */
	.long	GPIO1_WAKEUP_handler  /* GPIO1_WAKEUP_handler */
	.long	GPIO2_WAKEUP_handler  /* GPIO2_WAKEUP_handler */
	.long	GPIO3_WAKEUP_handler  /* GPIO3_WAKEUP_handler */
	.long	GPIO4_WAKEUP_handler  /* GPIO4_WAKEUP_handler */
	.long	GPIO5_WAKEUP_handler  /* GPIO5_WAKEUP_handler */
	.long	GPIO6_WAKEUP_handler  /* GPIO6_WAKEUP_handler */
	.long	GPIO7_WAKEUP_handler  /* GPIO7_WAKEUP_handler */
	.long	GPIO8_WAKEUP_handler  /* GPIO8_WAKEUP_handler */
	.long	GPIO9_WAKEUP_handler  /* GPIO9_WAKEUP_handler */
	.long	GPIO10_WAKEUP_handler /* GPIO10_WAKEUP_handler */
	.long	GPIO11_WAKEUP_handler /* GPIO11_WAKEUP_handler */
	.long	GPIO12_WAKEUP_handler /* GPIO12_WAKEUP_handler */
	.long	GPIO13_WAKEUP_handler /* GPIO13_WAKEUP_handler */
	.long	GPIO14_WAKEUP_handler /* GPIO14_WAKEUP_handler */
	.long	GPIO15_WAKEUP_handler /* GPIO15_WAKEUP_handler */
	.long	GPIO16_WAKEUP_handler /* GPIO16_WAKEUP_handler */
	.long	GPIO17_WAKEUP_handler /* GPIO17_WAKEUP_handler */
	.long	GPIO18_WAKEUP_handler /* GPIO18_WAKEUP_handler */
	.long	GPIO19_WAKEUP_handler /* GPIO19_WAKEUP_handler */
	.long	GPIO20_WAKEUP_handler /* GPIO20_WAKEUP_handler */
	.long	GPIO21_WAKEUP_handler /* GPIO21_WAKEUP_handler */
	.long	GPIO22_WAKEUP_handler /* GPIO22_WAKEUP_handler */
	.long	GPIO23_WAKEUP_handler /* GPIO23_WAKEUP_handler */
	.long	GPIO24_WAKEUP_handler /* GPIO24_WAKEUP_handler */
	.long	GPIO25_WAKEUP_handler /* GPIO25_WAKEUP_handler */
	.long	GPIO26_WAKEUP_handler /* GPIO26_WAKEUP_handler */
	.long	GPIO27_WAKEUP_handler /* GPIO27_WAKEUP_handler */
	.long	GPIO28_WAKEUP_handler /* GPIO28_WAKEUP_handler */

	/* External interrupts */
	.long	Default_Handler

	.size	__isr_vector, . - __isr_vector

	.text
	.thumb
	.thumb_func
	.align	2
	.globl	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.


/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

.L_loop1:
	cmp	r2, r3
	ittt	lt
	ldrlt	r0, [r1], #4
	strlt	r0, [r2], #4
	blt	.L_loop1

	ldr	r3, =__StackTop
	mov	sp, r3

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

	movs	r0, 0
.L_loop3:
	cmp	r1, r2
	itt	lt
	strlt	r0, [r1], #4
	blt	.L_loop3

	bl	_start

	.pool
	.size	Reset_Handler, . - Reset_Handler

	.align	1
	.thumb_func
	.weak	Default_Handler
	.type	Default_Handler, %function
Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	MemManage_Handler
	def_irq_handler	BusFault_Handler
	def_irq_handler	UsageFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	DebugMon_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler
	def_irq_handler	RTC_IRQHandler
	def_irq_handler	RC32M_IRQHandler
	def_irq_handler	ADC_IRQHandler
	def_irq_handler	AES_IRQHandler
	def_irq_handler	GPIO_IRQHandler
	def_irq_handler	QSPI_IRQHandler
	def_irq_handler	UART0_IRQHandler
	def_irq_handler	UART1_IRQHandler
	def_irq_handler	ZIGBEE_IRQ_Handler
	def_irq_handler	ZIGBEE_IRQ1_Handler
	def_irq_handler	GPIO0_WAKEUP_handler
	def_irq_handler	GPIO1_WAKEUP_handler
	def_irq_handler	GPIO2_WAKEUP_handler
	def_irq_handler	GPIO3_WAKEUP_handler
	def_irq_handler	GPIO4_WAKEUP_handler
	def_irq_handler	GPIO5_WAKEUP_handler
    def_irq_handler GPIO6_WAKEUP_handler 
    def_irq_handler GPIO7_WAKEUP_handler 
    def_irq_handler GPIO8_WAKEUP_handler 
    def_irq_handler GPIO9_WAKEUP_handler 
    def_irq_handler GPIO10_WAKEUP_handler
    def_irq_handler GPIO11_WAKEUP_handler
    def_irq_handler GPIO12_WAKEUP_handler
    def_irq_handler GPIO13_WAKEUP_handler
    def_irq_handler GPIO14_WAKEUP_handler
    def_irq_handler GPIO15_WAKEUP_handler
    def_irq_handler GPIO16_WAKEUP_handler
    def_irq_handler GPIO17_WAKEUP_handler
    def_irq_handler GPIO18_WAKEUP_handler
    def_irq_handler GPIO19_WAKEUP_handler
    def_irq_handler GPIO20_WAKEUP_handler
    def_irq_handler GPIO21_WAKEUP_handler
    def_irq_handler GPIO22_WAKEUP_handler
    def_irq_handler GPIO23_WAKEUP_handler
    def_irq_handler GPIO24_WAKEUP_handler
    def_irq_handler GPIO25_WAKEUP_handler
    def_irq_handler GPIO26_WAKEUP_handler
    def_irq_handler GPIO27_WAKEUP_handler
    def_irq_handler GPIO28_WAKEUP_handler

	def_irq_handler	DEF_IRQHandler
	.end
