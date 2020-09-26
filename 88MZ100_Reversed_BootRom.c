/*

Reversed BootRom of the Marvell 88MZ100 
this is an UART Bootloader and will load the Firmware from flash to RAM on normal boot

Made by Aaron Christophel ( https://atcnetz.de ) 

*/

#include <defs.h>

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

struct UART_cmd_struct
{
  char length_cmd;
  char cmd;
  char check;
  char length_data;
  int password_or_answer_buffer;
  int address;
  int request_data;
};
//-------------------------------------------------------------------------
// Function declarations

void UART_init(unsigned __int16 baudrade, int portNo, unsigned int UART_GPIO);
__int8 UART_read_byte_0();
__int8 UART_read_byte();
int UART_something();
int UART_something_0();
char __fastcall UART_read_bytes(_BYTE *buffer, unsigned int max_length);
void UART_send_byte(int byte);
void UART_send_bytes(_BYTE *byte_buffer, int length);
signed int __fastcall UART_wait_for_input(int a1, int a2, int timeout); // idb
signed int __fastcall UART_init_wait_for_input(unsigned __int16 baudrate); // idb
void DSB_ISB();
void __cdecl set_timeout(int time);
void set_timeout_pre(int a1, int time);
void __fastcall set_timeoutPRE(int enabled, int time); // idb
bool is_timer_ended();
void disable_timeout();
int __cdecl NVIC_get_current_SYStick();
signed int __cdecl NVIC_read_COUNTFLAG_and_check_if_timeout_enabled();
void __cdecl delay_SYStick(int time);
void __noreturn Chip_RESET(int a1);
void QSPI_software_reset();
void QSPI_something_4();
int QSPI_something();
void QSPI_init();
void QSPI_config(int a1, char a2, int a3);
unsigned int __fastcall QSPI_something_0(int a1);
void QSPI_write_byte(int result);
__int8 QSPI_read_byte();
void PINMUX(int result, unsigned int count, int a3);
void pin_mux_something(int a1, char a2);
void __fastcall pin_mux_UART(int port_num, int a2); // idb
void __fastcall pin_mux_something_1(int a1, int a2);
void QSPI_send_command(int cmd, char a2, int a3);
void QSPI_sleep_or_wakeup(int sleep);
__int8 QSPI_read_status_register(signed int statusIdx);
__int8 QSPI_something_2();
__int8 QSPI_something_3();
void QSPI_chip_erase();
void QSPI_set_address(int address, char a2);
void QSPI_something_1();
unsigned int __fastcall QSPI_write_bytes(int address, int buffer, unsigned int length); // idb
void __fastcall QSPI_prepare_read_bytes(int address, char config, int length); // idb
int __fastcall QSPI_read_bytes(int address, int data_buffer, int length, int crc_mode, int with_timeout); // idb
void QSPI_set_state(unsigned int QSPI_state);
void __cdecl CRC_init(int length, char crc_mode);
void CRC_FeedData(int result);
int __cdecl Get_CRC_result();
void __cdecl Init_NVIC_interrupt_and_QSPI();
void NVIC_disable_and_clear_interrupt();
void mem_set(_BYTE *buffer, char set_to, unsigned int len);
void __fastcall delay(int time); // idb
int __fastcall RUN_given_address(int a1);
signed int __fastcall Some_delay_request(int a1, int time, unsigned int a3); // idb
int QSPI_something_5();
void sub_994();
void sub_9D6();
void UART_send_buffer_plus_MAIN_state(_BYTE *byte_buffer, int length);
void __noreturn MAIN_loading();
int __fastcall Memory_read_or_write(int mode, int address, int *buffer, int length); // idb
unsigned int __fastcall QSPI_read_or_write(int mode, int address, int buffer, int length_1, char *a5); // idb
void UART_cmd_handler(int mode);
void nullsub_1();
signed int get_201250D4();
void nullsub_2();
_DWORD *__fastcall sub_ED0(int a1, int a2, int a3, int a4);
_DWORD *sub_ED4();

//-------------------------------------------------------------------------
// Data declarations

int dword_EF0[5] = { 3810, 3814, 3818, 3860, 3864 }; // weak
_UNKNOWN unk_F2C; // weak
char *word_F3F = (char *)0x65724B4F;
_UNKNOWN unk_20124000; // weak
_DWORD *UART1_Register_address;
_UNKNOWN current_SYStick; // weak
_UNKNOWN is_timeout_enabled; // weak
_UNKNOWN unk_2012500C; // weak
_UNKNOWN unk_20125010; // weak
_DWORD *dword_20125014[3]; // idb
_UNKNOWN QSPI_state; // weak
char timeout_delay; // weak
char HEADER_count_of_wrong_pass_trys; // weak
_UNKNOWN MAIN_state_status; // weak
char security_enabled; // weak
unsigned __int8 CRC_check;
unsigned __int16 baudrate; // idb
int enable_custom_boot_delay; // weak
int FIRMWARE_HEADER; // weak
_DWORD CONFIG_1; // idb
int IMAGE_LENGTH; // idb
__int16 CONFIG_2; // weak
_UNKNOWN baudrate_0; // weak
int PASSWORD; // weak
int LOADING_POINT; // idb
int ENTRY_POINT; // idb
int MAGIC_string_MRVL; // weak
UART_cmd_struct uart_cmd_buffer_ram;
_DWORD dword_48070000[1024]; // idb
_DWORD QSPIreg_serial_interface_Control; // idb
__int16 QSPIreg_serial_interface_CONFIG; // weak
_UNKNOWN QSPIreg_serial_interface_Data_OUT; // weak
int QSPIreg_serial_interface_Data_IN_0; // idb
_UNKNOWN QSPIreg_serial_interface_instruction; // weak
_UNKNOWN QSPIreg_serial_interface_Address; // weak
_UNKNOWN unk_4A070018; // weak
_UNKNOWN QSPIreg_serial_interface_header_count; // weak
_UNKNOWN QSPIreg_serial_interface_Data_in_Count; // weak
_UNKNOWN QSPIreg_serial_interface_CONFIG2; // weak
int dword_4A080000; // weak
_UNKNOWN unk_4A080004; // weak
_UNKNOWN QSPIreg_serial_interface_Data_IN; // weak
_UNKNOWN unk_4A080020; // weak
_UNKNOWN unk_4A08002C; // weak
_UNKNOWN unk_4A080048; // weak
_UNKNOWN unk_4A08004C; // weak
_UNKNOWN unk_4A080068; // weak
_UNKNOWN unk_4A080090; // weak


//----- (000000A8) --------------------------------------------------------
void UART_init(unsigned __int16 baudrade, int portNo, unsigned int UART_GPIO)
{
  char port_num; // zf@1
  signed int UARTno_REG; // r0@4

  port_num = portNo == 0;
  if ( port_num )                               // Port 1
  {
    if ( UART_GPIO >= 6 )
      UART_GPIO = 0;
    unk_4A080020 &= 0xFFFF7FFF;
    pin_mux_UART(portNo, UART_GPIO);
    UARTno_REG = 0x48010000;
  }
  else                                          // Port 0
  {
    if ( UART_GPIO >= 3 )
      UART_GPIO = 0;
    unk_4A080020 &= 0xFFFFBFFF;
    pin_mux_UART(portNo, UART_GPIO);
    UARTno_REG = 0x48020000;
  }
  UART1_Register_address = (_DWORD *)UARTno_REG;
  *(_DWORD *)(UARTno_REG + 0x88) = 7;
  *(_DWORD *)(UARTno_REG + 0xC) |= 0x80u;
  *(_DWORD *)(UARTno_REG + 0xC) |= 3u;
  *(_DWORD *)(UARTno_REG + 4) = *(_DWORD *)(UARTno_REG + 4) & 0xFFFFFF00 | (baudrade >> 8);
  *(_DWORD *)UARTno_REG = (unsigned __int8)baudrade;
  *(_DWORD *)(UARTno_REG + 8) = 7;
  *(_DWORD *)(UARTno_REG + 0xC) &= 0xFFFFFF7F;
}

//----- (00000112) --------------------------------------------------------
__int8 UART_read_byte_0()
{
  _DWORD *UART_reg; // r0@1

  UART_reg = UART1_Register_address;
  if ( UART1_Register_address[5] & 0x9E )
    UART1_Register_address[2] |= 2u;
  while ( !(UART_reg[5] << 31) )
    ;
  return *UART_reg;
}

//----- (00000132) --------------------------------------------------------
__int8 UART_read_byte()
{
  return *UART1_Register_address;
}

//----- (0000013C) --------------------------------------------------------
int UART_something()
{
  return UART1_Register_address[5] & 1;
}

//----- (00000148) --------------------------------------------------------
int UART_something_0()
{
  if ( UART1_Register_address[5] & 0x9E )
    UART1_Register_address[2] |= 2u;
  do
  {
    if ( UART1_Register_address[5] << 31 )
      return (unsigned __int8)*UART1_Register_address;
    current_SYStick = NVIC_get_current_SYStick();
  }
  while ( NVIC_read_COUNTFLAG_and_check_if_timeout_enabled() != 1 );
  return 0;
}

//----- (00000182) --------------------------------------------------------
char __fastcall UART_read_bytes(_BYTE *buffer, unsigned int max_length)
{
  unsigned int bytes_to_read_count; // r0@1
  unsigned int current_byte_count; // r2@1
  unsigned int bytes_to_read; // r3@1
  int v7; // r2@3

  LOBYTE(bytes_to_read_count) = UART_read_byte_0();
  bytes_to_read = bytes_to_read_count;
  if ( bytes_to_read_count > max_length )
    bytes_to_read = max_length;
  while ( current_byte_count <= bytes_to_read )
  {
    LOBYTE(bytes_to_read_count) = UART_read_byte_0();
    buffer[v7] = bytes_to_read_count;
    current_byte_count = (unsigned __int8)(v7 + 1);
  }
  *buffer = bytes_to_read;
  return bytes_to_read_count;
}

//----- (000001AA) --------------------------------------------------------
void UART_send_byte(int byte)
{
  _DWORD *UART1_Register_address; // r1@1

  UART1_Register_address = ::UART1_Register_address;
  if ( ::UART1_Register_address[5] & 0x3E )
    ::UART1_Register_address[2] |= 4u;
  while ( !(UART1_Register_address[5] & 0x40) )
    ;
  *UART1_Register_address = byte;
}

//----- (000001C8) --------------------------------------------------------
void UART_send_bytes(_BYTE *byte_buffer, int length)
{
  int current_byte; // t1@2

  while ( length )
  {
    current_byte = *byte_buffer++;
    UART_send_byte(current_byte);
  }
}

//----- (000001E4) --------------------------------------------------------
signed int __fastcall UART_wait_for_input(int a1, int a2, int timeout)
{
  signed int v6; // r4@1
  int v7; // r0@3
  signed int result; // r0@6

  v6 = 0;
  pin_mux_UART(a1, a2);
  UART_send_byte('#');
  set_timeout_pre(timeout, 31999);
  while ( !NVIC_read_COUNTFLAG_and_check_if_timeout_enabled() )
  {
    if ( UART_something() )
    {
      LOBYTE(v7) = UART_read_byte();
      if ( v7 == '#' )
      {
        v6 = 1;
        break;
      }
    }
  }
  disable_timeout();
  if ( v6 )
  {
    result = 1;
  }
  else
  {
    pin_mux_something_1(a1, a2);
    result = 0;
  }
  return result;
}

//----- (00000238) --------------------------------------------------------
signed int __fastcall UART_init_wait_for_input(unsigned __int16 baudrate)
{
  unsigned int v2; // r4@1
  unsigned int v3; // r4@4

  UART_init(baudrate, 1, 0);
  v2 = 0;
  while ( !UART_wait_for_input(1, v2, 30) )
  {
    v2 = (unsigned __int8)(v2 + 1);
    if ( v2 >= 3 )
    {
      UART_init(baudrate, 0, 0);
      v3 = 0;
      while ( !UART_wait_for_input(0, v3, 30) )
      {
        v3 = (unsigned __int8)(v3 + 1);
        if ( v3 >= 6 )
          return 0;
      }
      return 1;
    }
  }
  return 1;
}

//----- (00000298) --------------------------------------------------------
void DSB_ISB()
{
  __dsb();
  __isb();
}

//----- (000002A2) --------------------------------------------------------
void __cdecl set_timeout(int time)
{
  __disable_irq();
  vE000E010 &= 0xFFFFFFFE;
  vE000E014 = time;
  vE000E018 = 0;
  vE000E010 |= 1u;
  __enable_irq();
}

//----- (000002C2) --------------------------------------------------------
void set_timeout_pre(int a1, int time)
{
  is_timeout_enabled = a1;
  set_timeout(time);
}

//----- (000002CA) --------------------------------------------------------
void __fastcall set_timeoutPRE(int enabled, int time)
{
  is_timeout_enabled = enabled;
  unk_2012500C = 0;
  unk_20125010 = time;
  set_timeout(time);
}

//----- (000002DA) --------------------------------------------------------
bool is_timer_ended()
{
  bool result; // r0@4

  result = 0;
  if ( is_timeout_enabled )
  {
    if ( vE000E010 & 0x10000 )
    {
      if ( ++unk_2012500C >= is_timeout_enabled )
        result = 1;
    }
  }
  return result;
}

//----- (000002FC) --------------------------------------------------------
void disable_timeout()
{
  is_timeout_enabled = 0;
  __disable_irq();
  vE000E010 &= 0xFFFFFFFE;
  __enable_irq();
}

//----- (00000314) --------------------------------------------------------
int __cdecl NVIC_get_current_SYStick()
{
  return vE000E018 & 0xFFFFFF;
}

//----- (00000320) --------------------------------------------------------
signed int __cdecl NVIC_read_COUNTFLAG_and_check_if_timeout_enabled()
{
  signed int result; // r0@4

  if ( vE000E010 & 0x10000 && is_timeout_enabled )
    --is_timeout_enabled;
  result = 1;
  if ( is_timeout_enabled )
    result = 0;
  return result;
}

//----- (00000340) --------------------------------------------------------
void __cdecl delay_SYStick(int time)
{
  int v1; // r3@1

  v1 = time;
  if ( time )
  {
    while ( v1 )
    {
      is_timeout_enabled = 1;
      set_timeout(31999);
      while ( !(vE000E010 & 0x10000) )
        ;
      disable_timeout();
    }
  }
}

//----- (00000372) --------------------------------------------------------
void __noreturn Chip_RESET(int a1)
{
  signed int reset_value; // r0@2

  if ( a1 )
    reset_value = 0x5FA0004;
  else
    reset_value = 0x5FA0001;
  vE000ED0C = reset_value;
  while ( 1 )
    ;
}

//----- (00000390) --------------------------------------------------------
void QSPI_software_reset()
{
  QSPIreg_serial_interface_CONFIG2 |= 1u;
  QSPIreg_serial_interface_CONFIG2 &= 0xFFFFFFFE;
}

//----- (000003A4) --------------------------------------------------------
void QSPI_something_4()
{
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG |= 0x200u;
  while ( QSPIreg_serial_interface_CONFIG & 0x200 )
    ;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (000003B6) --------------------------------------------------------
int QSPI_something()
{
  int v0; // r2@1
  unsigned int v1; // r0@1
  int result; // r0@2

  QSPIreg_serial_interface_instruction = 0;
  QSPIreg_serial_interface_header_count &= 0xFFFFFFFC;
  QSPIreg_serial_interface_Address = 0;
  QSPIreg_serial_interface_header_count &= 0xFFFFFF8F;
  QSPIreg_serial_interface_header_count &= 0xFFFFCFFF;
  QSPIreg_serial_interface_Data_in_Count = 0;
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG = *dword_20125014[0];
  QSPIreg_serial_interface_CONFIG2 = dword_20125014[0][1];
  QSPI_something_4();
  v1 = *(_DWORD *)(v0 + 4) & 0xFFFFFFE0;
  if ( QSPIreg_serial_interface_Data_IN << 31 )
    result = v1 + 1;
  else
    result = v1 + 2;
  *(_DWORD *)(v0 + 4) = result;
  return result;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (00000402) --------------------------------------------------------
void QSPI_init()
{
  int *v0; // r2@1
  int v1; // r0@1

  dword_20125014[0] = dword_20125014 + 4;
  QSPI_software_reset();
  v1 = *v0;
  *(_DWORD *)v1 = *(_DWORD *)&QSPIreg_serial_interface_CONFIG;
  *(_DWORD *)(v1 + 4) = QSPIreg_serial_interface_CONFIG2;
  QSPI_something();
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (00000422) --------------------------------------------------------
void QSPI_config(int a1, char a2, int a3)
{
  unsigned int v3; // r0@5

  QSPIreg_serial_interface_Control |= 1u;
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG &= 0xFFFFEFFF;
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG &= 0xFFFFF3FF;
  if ( a1 == 2 )
  {
    if ( a3 )
    {
      if ( a3 != 1 )
        goto LABEL_8;
      v3 = *(_DWORD *)&QSPIreg_serial_interface_CONFIG & 0xFFFFEFFF;
    }
    else
    {
      v3 = *(_DWORD *)&QSPIreg_serial_interface_CONFIG | 0x1000;
    }
    *(_DWORD *)&QSPIreg_serial_interface_CONFIG = (v3 & 0xFFFFF3FF) + 2048;
  }
LABEL_8:
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG = *(_DWORD *)&QSPIreg_serial_interface_CONFIG & 0xFFFFFFDF | 32 * (a2 & 1);
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG = *(_DWORD *)&QSPIreg_serial_interface_CONFIG & 0xFFFFDFFF | ((a3 & 1) << 13);
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG |= 0x8000u;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (00000480) --------------------------------------------------------
unsigned int __fastcall QSPI_something_0(int a1)
{
  unsigned int result; // r0@6

  if ( a1 << 31 )
  {
    if ( a1 << 30 )
    {
      while ( !(QSPIreg_serial_interface_Control & 0x40) )
        ;
    }
    *(_DWORD *)&QSPIreg_serial_interface_CONFIG |= 0x4000u;
  }
  while ( QSPIreg_serial_interface_CONFIG & 0x8000 )
    ;
  result = QSPIreg_serial_interface_Control & 0xFFFFFFFE;
  QSPIreg_serial_interface_Control &= 0xFFFFFFFE;
  return result;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (000004A8) --------------------------------------------------------
void QSPI_write_byte(int result)
{
  while ( QSPIreg_serial_interface_Control & 0x80 )
    ;
  QSPIreg_serial_interface_Data_OUT = result;
}

//----- (000004B4) --------------------------------------------------------
__int8 QSPI_read_byte()
{
  while ( QSPIreg_serial_interface_Control & 0x10 )
    ;
  return QSPIreg_serial_interface_Data_IN_0;
}

//----- (000004CC) --------------------------------------------------------
void PINMUX(int result, unsigned int count, int a3)
{
  unsigned int i; // r3@1
  char v4; // r4@2

  for ( i = 0; i < count; i = (unsigned __int8)(i + 1) )
  {
    v4 = 0;
    if ( !a3 )
      v4 = *(_BYTE *)(result + 2 * i + 1);
    dword_48070000[*(_BYTE *)(result + 2 * i)] = dword_48070000[*(_BYTE *)(result + 2 * i)] & 0xFFFFFFF0 | v4 & 0xF;
  }
}

//----- (000004FA) --------------------------------------------------------
void pin_mux_something(int a1, char a2)
{
  dword_48070000[a1] = dword_48070000[a1] & 0xFFFFFFF0 | a2 & 0xF;
}

//----- (0000050A) --------------------------------------------------------
void __fastcall pin_mux_UART(int port_num, int a2)
{
  int *v2; // r0@2

  if ( port_num )
    v2 = dword_EF0;
  else
    v2 = &dword_EF0[3];
  PINMUX(v2[a2], 2u, 0);
}
// EF0: using guessed type int dword_EF0[5];

//----- (0000051E) --------------------------------------------------------
void __fastcall pin_mux_something_1(int a1, int a2)
{
  int *v2; // r0@2
  int v3; // r0@4
  int v4; // r3@4
  int v5; // r3@4

  if ( a1 )
    v2 = dword_EF0;
  else
    v2 = &dword_EF0[3];
  v3 = v2[a2];
  v4 = *(_BYTE *)(v3 + 2);
  pin_mux_something(*(_BYTE *)v3, 0);
  pin_mux_something(v5, 0);
}
// EF0: using guessed type int dword_EF0[5];

//----- (0000054C) --------------------------------------------------------
void QSPI_send_command(int cmd, char a2, int a3)
{
  QSPI_something();
  QSPIreg_serial_interface_instruction = cmd;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFFFC) + 1;
  QSPIreg_serial_interface_header_count = QSPIreg_serial_interface_header_count & 0xFFFFCFFF | ((a2 & 3) << 12);
  QSPI_config(0, 0, 1);
  if ( a3 )
    QSPIreg_serial_interface_Data_OUT = 2;
  while ( !(QSPIreg_serial_interface_Control & 2) )
    ;
  QSPI_something_0(3);
}

//----- (00000594) --------------------------------------------------------
void QSPI_sleep_or_wakeup(int sleep)
{
  int cmd; // r3@1

  cmd = 0xAB;
  if ( sleep )
    cmd = 0xB9;
  QSPI_send_command(cmd, 0, 0);
}

//----- (000005AA) --------------------------------------------------------
__int8 QSPI_read_status_register(signed int statusIdx)
{
  int v2; // r4@1
  int status; // r0@3

  QSPI_something();
  QSPIreg_serial_interface_instruction = 5;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFFFC) + 1;
  QSPIreg_serial_interface_Data_in_Count = 0;
  QSPI_config(0, 0, 0);
  LOBYTE(v2) = 0;
  while ( 1 )
  {
    while ( QSPIreg_serial_interface_Control & 0x10 )
      ;
    LOBYTE(status) = QSPI_read_byte();
    if ( statusIdx == 2 )
      break;
    if ( statusIdx == 1 )
      goto LABEL_8;
LABEL_11:
    if ( !(QSPIreg_serial_interface_CONFIG & 0x8000) )
      goto LABEL_12;
  }
  if ( !(status & 2) )
  {
    v2 = (unsigned __int8)(v2 + 1);
    if ( v2 == 5 )
    {
      LOBYTE(v2) = 1;
      goto LABEL_12;
    }
    goto LABEL_11;
  }
  statusIdx = 1;
LABEL_8:
  if ( status << 31 )
    goto LABEL_11;
  LOBYTE(v2) = 0;
LABEL_12:
  QSPI_something_0(1);
  return v2;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (00000610) --------------------------------------------------------
__int8 QSPI_something_2()
{
  QSPI_something();
  QSPIreg_serial_interface_instruction = 6;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFFFC) + 1;
  QSPI_config(0, 0, 1);
  while ( !(QSPIreg_serial_interface_Control & 2) )
    ;
  QSPI_something_0(3);
  return QSPI_read_status_register(2);
}

//----- (00000646) --------------------------------------------------------
__int8 QSPI_something_3()
{
  int v0; // r0@1
  __int8 result; // r0@2

  LOBYTE(v0) = QSPI_something_2();
  if ( v0 )
  {
    result = 1;
  }
  else
  {
    QSPI_send_command(1, 2, 0);
    result = QSPI_read_status_register(1);
  }
  return result;
}

//----- (00000666) --------------------------------------------------------
void QSPI_chip_erase()
{
  int v0; // r0@1

  QSPI_something_3();
  LOBYTE(v0) = QSPI_something_2();
  if ( !v0 )
  {
    QSPI_send_command(0xC7, 0, 0);
    QSPI_read_status_register(1);
  }
}

//----- (0000068A) --------------------------------------------------------
void QSPI_set_address(int address, char a2)
{
  QSPI_something();
  QSPIreg_serial_interface_instruction = 2;
  if ( QSPI_state == 2 )
    QSPIreg_serial_interface_instruction = 50;
  QSPIreg_serial_interface_Address = address;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFF8F) + 48;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFFFC) + 1;
  QSPI_config(QSPI_state, a2, 1);
}

//----- (000006C8) --------------------------------------------------------
void QSPI_something_1()
{
  while ( !(QSPIreg_serial_interface_Control & 0x40) )
    ;
  *(_DWORD *)&QSPIreg_serial_interface_CONFIG |= 0x4000u;
  while ( QSPIreg_serial_interface_CONFIG & 0x8000 )
    ;
  QSPIreg_serial_interface_Control &= 0xFFFFFFFE;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (000006E8) --------------------------------------------------------
unsigned int __fastcall QSPI_write_bytes(int address, int buffer, unsigned int length)
{
  unsigned int i; // r4@2
  unsigned int result; // r0@3

  if ( length )
  {
    QSPI_something_2();
    QSPI_set_address(address, 1);
    for ( i = 0; i < length; i += 4 )
      QSPI_write_byte(*(_BYTE *)(buffer + i) | (*(_DWORD *)(buffer + i + 1) << 8));
    QSPI_something_1();
    QSPI_read_status_register(1);
    result = length;
  }
  else
  {
    result = 0;
  }
  return result;
}

//----- (0000072C) --------------------------------------------------------
void __fastcall QSPI_prepare_read_bytes(int address, char config, int length)
{
  QSPI_something();
  if ( QSPI_state == 2 )
    QSPI_send_command(0xA3, 3, 0);
  QSPIreg_serial_interface_instruction = 3;
  if ( QSPI_state == 2 )
  {
    QSPI_something();
    QSPIreg_serial_interface_instruction = 0xEB;
    QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFCFF) + 256;
    unk_4A070018 &= 0xFFFF0000;
    QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFCFFF) + 0x2000;
  }
  QSPIreg_serial_interface_Address = address;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFF8F) + 48;
  QSPIreg_serial_interface_header_count = (QSPIreg_serial_interface_header_count & 0xFFFFFFFC) + 1;
  QSPIreg_serial_interface_Data_in_Count = length;
  QSPIreg_serial_interface_Control |= 1u;
  if ( QSPI_state == 2 )
  {
    *(_DWORD *)&QSPIreg_serial_interface_CONFIG |= 0x1000u;
    *(_DWORD *)&QSPIreg_serial_interface_CONFIG = (*(_DWORD *)&QSPIreg_serial_interface_CONFIG & 0xFFFFF3FF) + 2048;
  }
  QSPI_config(QSPI_state, config, 0);
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (000007C6) --------------------------------------------------------
int __fastcall QSPI_read_bytes(int address, int data_buffer, int length, int crc_mode, int with_timeout)
{
  unsigned int i; // r4@2
  int result; // r0@3
  int data_in; // r6@8

  if ( length )
  {
    QSPI_prepare_read_bytes(address, 1, length);
    for ( i = 0; i < length; i += 4 )
    {
      while ( QSPIreg_serial_interface_Control & 0x10 )
      {
        if ( with_timeout && NVIC_read_COUNTFLAG_and_check_if_timeout_enabled() )
          return 0;
      }
      data_in = QSPIreg_serial_interface_Data_IN_0;
      if ( crc_mode )
        CRC_FeedData(QSPIreg_serial_interface_Data_IN_0);
      *(_DWORD *)(data_buffer + i) = data_in;
    }
    while ( QSPIreg_serial_interface_CONFIG & 0x8000 )
    {
      if ( with_timeout && NVIC_read_COUNTFLAG_and_check_if_timeout_enabled() )
        return 0;
    }
    QSPIreg_serial_interface_Control &= 0xFFFFFFFE;
    result = length;
  }
  else
  {
    result = 0;
  }
  return result;
}
// 4A070004: using guessed type __int16 QSPIreg_serial_interface_CONFIG;

//----- (00000836) --------------------------------------------------------
void QSPI_set_state(unsigned int QSPI_state)
{
  ::QSPI_state = 0;
  if ( QSPI_state < 3 )
  {
    QSPI_software_reset();
    ::QSPI_state = QSPI_state;
    if ( QSPI_state == 2 )
    {
      QSPI_something_2();
      QSPI_send_command(1, 0, 1);
      QSPI_read_status_register(1);
    }
  }
}

//----- (00000870) --------------------------------------------------------
void __cdecl CRC_init(int length, char crc_mode)
{
  v46000010 &= 0xFFFFFFFE;
  v46000008 = 0xFFFFFFFF;
  v46000014 = length;
  v46000010 = v46000010 & 0xFFFFFFF1 | 2 * (crc_mode & 7);
  v46000010 |= 1u;
}

//----- (00000896) --------------------------------------------------------
void CRC_FeedData(int result)
{
  v46000018 = result;
}

//----- (0000089E) --------------------------------------------------------
int __cdecl Get_CRC_result()
{
  int result; // r0@2

  while ( !(v46000004 << 31) )
    ;
  result = v4600001C;
  v46000008 = -1;
  return result;
}

//----- (000008B2) --------------------------------------------------------
void __cdecl Init_NVIC_interrupt_and_QSPI()
{
  __disable_irq();
  vE000E018 = 0;
  vE000E010 = 4;
  QSPI_init();
  QSPI_set_state(0);
  DSB_ISB();
}

//----- (000008D4) --------------------------------------------------------
void NVIC_disable_and_clear_interrupt()
{
  vE000E180 = 0xFFFFFFFF;
  vE000E280 = 0xFFFFFFFF;
  __enable_irq();
}

//----- (000008E8) --------------------------------------------------------
void mem_set(_BYTE *buffer, char set_to, unsigned int len)
{
  char v3; // cf@3

  while ( 1 )
  {
    v3 = len-- >= 1;
    if ( !v3 )
      break;
    *buffer++ = set_to;
  }
}

//----- (000008F4) --------------------------------------------------------
void __fastcall delay(int time)
{
  set_timeout_pre(time, 31999);
  while ( !NVIC_read_COUNTFLAG_and_check_if_timeout_enabled() )
    ;
  disable_timeout();
}

//----- (00000910) --------------------------------------------------------
int __fastcall RUN_given_address(int a1)
{
  return ((int (*)(void))(a1 | 1))();
}

//----- (00000916) --------------------------------------------------------
signed int __fastcall Some_delay_request(int a1, int time, unsigned int a3)
{
  signed int return_1; // r6@1
  unsigned int v6; // r4@1
  int v7; // r0@3
  unsigned int v8; // r0@7
  char v9; // cf@8

  return_1 = 1;
  LOBYTE(v6) = 0;
  set_timeoutPRE(time, 31999);
  while ( 1 )
  {
    v7 = a1 ? (unk_4A080004 >> 9) & 1 : unk_4A08002C & 1;
    if ( v7 )
    {
      v6 = (unsigned __int8)(v6 + 1);
      if ( v6 >= a3 )
        break;
    }
    v8 = 2000;
    do
      v9 = v8-- >= 1;
    while ( v9 );
    if ( is_timer_ended() == 1 )
    {
      return_1 = 0;
      break;
    }
  }
  disable_timeout();
  return return_1;
}

//----- (0000096A) --------------------------------------------------------
int QSPI_something_5()
{
  int result; // r0@1

  result = QSPIreg_serial_interface_Data_IN << 31;
  if ( QSPIreg_serial_interface_Data_IN << 31 )
  {
    result = Some_delay_request(0, 8, 1u);
    if ( result )
    {
      QSPIreg_serial_interface_Data_IN &= 0xFFFFFFFE;
      result = QSPI_something();
    }
  }
  return result;
}

//----- (00000994) --------------------------------------------------------
void sub_994()
{
  unsigned int v0; // r2@1
  int v1; // r1@1
  unsigned int v2; // r0@6

  LOBYTE(v0) = 0;
  LOBYTE(v1) = 0;
  do
  {
    if ( v48000004 << 31 )
    {
      v1 = (unsigned __int8)(v1 + 1);
      if ( v1 == 2 )
        goto LABEL_10;
    }
    else
    {
      v1 = 0;
    }
    LOBYTE(v2) = 0;
    do
      v2 = (unsigned __int8)(v2 + 1);
    while ( v2 < 0x1E );
    v0 = (unsigned __int8)(v0 + 1);
  }
  while ( v0 < 0xA );
  if ( v1 != 2 )
    return;
LABEL_10:
  if ( v48000004 << 31 )
    unk_4A080090 |= 1u;
}

//----- (000009D6) --------------------------------------------------------
void sub_9D6()
{
  unk_4A080020 &= 0xFFFBFFFF;
  unk_4A080020 &= 0xFFFFFFFD;
  unk_4A080020 &= 0xFFFFFBFF;
  unk_4A080020 &= 0xFFFFFFFB;
  unk_4A080020 &= 0xFFFFFFBF;
  unk_4A080020 &= 0xFFF7FFFF;
  unk_4A080020 &= 0xFFFFFFF7;
}

//----- (00000A12) --------------------------------------------------------
void UART_send_buffer_plus_MAIN_state(_BYTE *byte_buffer, int length)
{
  UART_send_bytes(byte_buffer, length);
  UART_send_byte((unsigned __int8)(MAIN_state_status + '0'));
}

//----- (00000A28) --------------------------------------------------------
void __noreturn MAIN_loading()
{
  unsigned int retry_delay; // r5@9
  bool v1; // r6@10
  signed int uart_port_number; // r6@20
  int UART_GPIO; // r7@20
  int security_mode; // r0@26
  int CRC_enabled; // r6@35

  unk_4A080048 = (unk_4A080048 & 0xFFFFFFC0) + 10;
  unk_4A08004C = unk_4A08004C & 0xFFFC01FF | 0x3C800;
  if ( (dword_4A080000 & 3) == 2 )
  {
    ((void (__cdecl *)(_DWORD))(unk_20124000 | 1))(unk_20124000 | 1);
  }
  else if ( !(dword_4A080000 & 3) )
  {
    mem_set((_BYTE *)0x130000, 0, 0x1000u);
  }
  sub_9D6();
  sub_994();
  unk_4A080068 |= 8u;
  v48000200 = 0x2EF501;
  Init_NVIC_interrupt_and_QSPI();
  NVIC_disable_and_clear_interrupt();
  MAIN_state_status = 0;
  if ( !Some_delay_request(1, 32, 2u) )
    MAIN_state_status = 1;
  QSPI_sleep_or_wakeup(0);
  if ( !MAIN_state_status )
  {
    retry_delay = 2;
    while ( 1 )
    {
      set_timeout_pre(1, 0x1F3FC);
      v1 = QSPI_read_bytes(0, 0x20125030, 32, 0, 1) != 32;// READ Firmware header from Flash
      disable_timeout();
      if ( !v1 )
        break;
      MAIN_state_status = 2;
      delay_SYStick(retry_delay);
      retry_delay = 2 * retry_delay & 0xFF;
      if ( retry_delay > 8 )
        goto LABEL_14;
    }
    MAIN_state_status = 0;
  }
LABEL_14:
  if ( MAGIC_string_MRVL == 0xFFFFFFFF || MAGIC_string_MRVL == 'MRVL' )
  {
    if ( !MAIN_state_status )
      goto LABEL_19;
  }
  else
  {
    MAIN_state_status = 5;
  }
  FIRMWARE_HEADER = 0xFFFFFFFF;
  *(_DWORD *)&CONFIG_2 = 0xFFFFFFFF;
  PASSWORD = 0xFFFFFFFF;
LABEL_19:
  if ( *(_DWORD *)&CONFIG_2 == 0xFFFFFFFF )     // User_default_settings
  {
    baudrate = 0x11;
    HEADER_count_of_wrong_pass_trys = 3;
    uart_port_number = 1;
    UART_GPIO = 0;
    enable_custom_boot_delay = 8;
  }
  else
  {
    baudrate = ~baudrate_0;
    uart_port_number = (unsigned __int8)CONFIG_1 >> 8;
    UART_GPIO = (CONFIG_1 >> 13) & 0xF;
    timeout_delay = (CONFIG_1 >> 9) & 0xF;
    CRC_check = CONFIG_2 & 7;
    HEADER_count_of_wrong_pass_trys = (unsigned __int8)CONFIG_2 >> 6;
    if ( (unsigned __int8)CONFIG_2 >> 6 )
      HEADER_count_of_wrong_pass_trys = 1 << ((unsigned __int8)CONFIG_2 >> 6);
    QSPI_set_state((*(_DWORD *)&CONFIG_2 >> 3) & 3);
    enable_custom_boot_delay = 8 * ((unsigned __int16)CONFIG_2 >> 14);
    if ( !((CONFIG_1 >> 7) & 1) )
    {
      v48000100 = v48000100 & 0xFFFFF80F | 16 * (CONFIG_1 & 0x7F);
      v48000100 |= 4u;
LABEL_26:
      security_mode = PASSWORD + 1;
      if ( PASSWORD != 0xFFFFFFFF )
        security_mode = 1;
      security_enabled = security_mode;
      if ( !security_mode )
        PINMUX((int)&unk_F2C, 5u, 0);           // enable SWD
      if ( FIRMWARE_HEADER == 0xFFFFFFFF )
      {
        if ( UART_init_wait_for_input(baudrate) != 1 )
          UART_init(baudrate, uart_port_number, UART_GPIO);
      }
      else
      {
        UART_init(baudrate, uart_port_number, UART_GPIO);
        UART_send_byte(':');
      }
      UART_cmd_handler(0);
      UART_send_bytes("Boot\r\n", 6);
      if ( CRC_check >= 4u )
      {
        CRC_enabled = 0;
      }
      else
      {
        CRC_init(IMAGE_LENGTH + 11, CRC_check);
        CRC_FeedData(IMAGE_LENGTH);
        CRC_FeedData(LOADING_POINT);
        CRC_FeedData(ENTRY_POINT);
        CRC_enabled = 1;
      }
      if ( QSPI_read_bytes(32, LOADING_POINT, IMAGE_LENGTH, CRC_enabled, 0) == IMAGE_LENGTH )
      {
        if ( CRC_enabled && Get_CRC_result() != FIRMWARE_HEADER )
        {
          MAIN_state_status = 3;
        }
        else if ( !MAIN_state_status )
        {
          ((void (*)(void))(ENTRY_POINT | 1))();// Jump into Firmware
        }
      }
      else
      {
        MAIN_state_status = 2;
      }
      UART_send_buffer_plus_MAIN_state("ERR", 3);
      if ( MAIN_state_status )
        UART_cmd_handler(1);
      while ( 1 )
        ;
    }
  }
  QSPI_something_5();
  goto LABEL_26;
}
// 20125024: using guessed type char timeout_delay;
// 20125025: using guessed type char HEADER_count_of_wrong_pass_trys;
// 20125027: using guessed type char security_enabled;
// 2012502C: using guessed type int enable_custom_boot_delay;
// 20125030: using guessed type int FIRMWARE_HEADER;
// 2012503C: using guessed type __int16 CONFIG_2;
// 20125040: using guessed type int PASSWORD;
// 2012504C: using guessed type int MAGIC_string_MRVL;
// 4A080000: using guessed type int dword_4A080000;

//----- (00000C8C) --------------------------------------------------------
int __fastcall Memory_read_or_write(int mode, int address, int *buffer, int length)
{
  int length_1; // r0@1
  int *v6; // r1@1
  int v7; // r3@5
  char v8; // zf@4
  int v9; // r3@8

  length_1 = length;
  v6 = (int *)(address & 0xFFFFFFFC);
  if ( mode == 3 )                              // Write RAM from UART
  {
    while ( 1 )
    {
      v8 = length_1 == 0;
      length_1 = (unsigned __int8)(length_1 - 1);
      if ( v8 )
        break;
      v7 = *buffer;
      ++buffer;
      *v6 = v7;
      ++v6;
    }
  }
  else if ( mode == 2 )                         // Read memory to UART
  {
    while ( 1 )
    {
      v8 = length_1 == 0;
      length_1 = (unsigned __int8)(length_1 - 1);
      if ( v8 )
        break;
      v9 = *v6;
      ++v6;
      *buffer = v9;
      ++buffer;
    }
  }
  return length_1;
}

//----- (00000CC0) --------------------------------------------------------
unsigned int __fastcall QSPI_read_or_write(int mode, int address, int buffer, int length_1, char *a5)
{
  int v7; // r0@1
  int length; // r2@1
  char v9; // r1@5

  v7 = 0;
  length = 4 * length_1;
  if ( mode == 9 )
  {
    v7 = QSPI_write_bytes(address, buffer, length);
  }
  else if ( mode == 4 )
  {
    v7 = QSPI_read_bytes(address, buffer, length, 0, 0);
    v9 = *a5;
    if ( v7 )
    {
      *a5 = v9 + v7;
    }
    else
    {
      *a5 = v9 + 2;
      *(_BYTE *)buffer = 0xADu;
      *(_BYTE *)(buffer + 1) = 0xDEu;
    }
  }
  return ((unsigned int)(v7 + 3) >> 2) & 0xFF;
}

//----- (00000D0C) --------------------------------------------------------
void UART_cmd_handler(int mode)
{
  int v1; // r0@5
  int v2; // r1@6
  int v3; // r4@7
  UART_cmd_struct *uart_buffer; // r5@8
  int UART_cmd; // r4@12
  signed int check_bit; // r6@12
  unsigned int current_wrong_pass_trys; // r7@12
  signed int toogle_check_bit; // r0@14
  int uart_cmd; // r0@22
  char *buffer; // r2@22
  int v11; // r0@27
  __int8 uart_length; // [sp+4h] [bp-24h]@3

  if ( mode
    || FIRMWARE_HEADER == 0xFFFFFFFF
    || ((uart_length = dword_4A080000 & 3, !(dword_4A080000 & 3)) || (dword_4A080000 & 3) != 3)
    && ((v1 = enable_custom_boot_delay) == 0 ? (v2 = 639980, v1 = (unsigned __int8)timeout_delay + 1) : (v2 = 4095872),
        set_timeout_pre(v1, v2),
        v3 = UART_something_0(),
        disable_timeout(),
        v3) )
  {
    QSPI_set_state(0);
    for ( uart_buffer = &uart_cmd_buffer_ram;
          (_DWORD)uart_buffer << 30;
          uart_buffer = (UART_cmd_struct *)((char *)uart_buffer + 1) )
    {
      ;
    }
    UART_cmd = (int)&uart_buffer->cmd;
    UART_send_buffer_plus_MAIN_state(&word_F3F, 2);// Send OK
    check_bit = 0;
    LOBYTE(current_wrong_pass_trys) = 0;
    while ( 1 )
    {
      do
      {
        uart_length = 3;
        UART_read_bytes(uart_buffer, 128u);
      }
      while ( (((unsigned int)uart_buffer->check >> 6) & 1) == check_bit );
      toogle_check_bit = 1;
      if ( check_bit )
        toogle_check_bit = 0;
      check_bit = toogle_check_bit;
      if ( security_enabled && PASSWORD != uart_buffer->password_or_answer_buffer )
      {
        if ( HEADER_count_of_wrong_pass_trys )
        {
          current_wrong_pass_trys = (unsigned __int8)(current_wrong_pass_trys + 1);
          if ( current_wrong_pass_trys >= (unsigned __int8)HEADER_count_of_wrong_pass_trys )
          {
            UART_send_buffer_plus_MAIN_state("flasherase", 10);
            QSPI_chip_erase();
            UART_send_buffer_plus_MAIN_state("reset", 5);
            Chip_RESET(0);
          }
        }
      }
      else
      {
        uart_cmd = *(_BYTE *)UART_cmd;
        buffer = (char *)&uart_buffer->request_data;
        switch ( uart_cmd )
        {
          case 2:                               // WRITE RAM
            buffer = (char *)&uart_buffer->password_or_answer_buffer;
            uart_length += 4 * uart_buffer->length_data;
            goto LABEL_24;
          case 3:                               // READM RAM or ROM
LABEL_24:
            Memory_read_or_write(*(_BYTE *)UART_cmd, uart_buffer->address, (int *)buffer, uart_buffer->length_data);
            break;
          case 4:                               // QSPI Read data
            uart_buffer->length_data = QSPI_read_or_write(
                                         uart_cmd,
                                         uart_buffer->address,
                                         (int)&uart_buffer->password_or_answer_buffer,
                                         uart_buffer->length_data,
                                         &uart_length);
            break;
          case 10:                              // QSPI send command
            v11 = uart_buffer->address;
            QSPI_send_command((unsigned __int8)uart_buffer->address, SBYTE1(v11), 0);
            QSPI_read_status_register(1);
            break;
          case 5:                               // RUN entry point
            RUN_given_address(uart_buffer->address);
            break;
          case 7:                               // Reset
            UART_send_buffer_plus_MAIN_state("reset", 5);
            delay(5);
            Chip_RESET((unsigned __int8)uart_buffer->address);
            return;
          case 1:                               // Enable_disable SWD
            PINMUX((int)&unk_F2C, 5u, (unsigned __int8)uart_buffer->address);
            break;
          default:
            break;
        }
        uart_buffer->check |= 0x80u;
        uart_buffer->length_cmd = uart_length;
        UART_send_bytes(uart_buffer, (unsigned __int8)(uart_length + 1));
      }
    }
  }
}
// 20125024: using guessed type char timeout_delay;
// 20125025: using guessed type char HEADER_count_of_wrong_pass_trys;
// 20125027: using guessed type char security_enabled;
// 2012502C: using guessed type int enable_custom_boot_delay;
// 20125030: using guessed type int FIRMWARE_HEADER;
// 20125040: using guessed type int PASSWORD;
// 4A080000: using guessed type int dword_4A080000;

//----- (00000EC8) --------------------------------------------------------
signed int get_201250D4()
{
  return 0x201250D4;
}

//----- (00000ED0) --------------------------------------------------------
_DWORD *__fastcall sub_ED0(int a1, int a2, int a3, int a4)
{
  int v4; // r4@0

  *(_DWORD *)(a3 + a4) = v4;
  return sub_ED4();
}

//----- (00000ED4) --------------------------------------------------------
_DWORD *sub_ED4()
{
  _DWORD *result; // r0@1

  result = (_DWORD *)get_201250D4();
  *result = 0;
  return result;
}

// ALL OK, 64 function(s) have been successfully decompiled
