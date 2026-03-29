#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <x68k/dos.h>
#include <x68k/iocs.h>
#include "mxdrv.h"

// workaround for m68k newlib memcpy bug
static inline void safe_memcpy(void *dst, const void *src, size_t len) {
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (len > 0) {
        size_t chunk = len > 0x8000 ? 0x8000 : len;
        memcpy(d, s, chunk);
        d += chunk;
        s += chunk;
        len -= chunk;
    }
}

// $02 LOADMML
uint32_t mxdrv_load_mml(const uint8_t* mml_data, size_t mml_len, const uint8_t* data_title, int16_t use_pdx) {

  // scratchpad
  uint8_t* buffer = malloc(mml_len + 270);
  if (buffer == NULL) return 0x8000000;

  // 8 bytes header
  uint16_t* header = (uint16_t*)buffer;
  header[0] = 0;                        // use mml
  header[1] = use_pdx ? 0 : 0xffff;     // use pdx?  yes:0000 no:ffff
  header[2] = 270;                      // offset to mml
  header[3] = 8;                        // offset to data title

  // data title
  strncpy(buffer + 8, data_title, 270 - 8);
 
  // mml data
  safe_memcpy(buffer + 270, mml_data, mml_len);

	register uint32_t reg_d0 asm ("d0") = 0x02;    // LOADMML
  register uint32_t reg_d1 asm ("d1") = mml_len + 270;
  register uint32_t reg_a1 asm ("a1") = (uint32_t)buffer;

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // output (&input) operand
    : "r"   (reg_d1),   // input operand
      "r"   (reg_a1)    // input operand
    :                   // clobbered register
  );

  free(buffer);

  return reg_d0;
}

// $03 LOADPCM
uint32_t mxdrv_load_pcm(const uint8_t* pcm_data, size_t pcm_len, const uint8_t* pcm_name) {

  // already loaded in the driver?
  uint8_t* current_pcm_name = mxdrv_pcm_name();
  if (current_pcm_name != NULL && strcasecmp(current_pcm_name, pcm_name) == 0) {
    //printf("already loaded.\n");
    return 0;
  }

  // scratchpad
  uint8_t* buffer = malloc(pcm_len + 270);
  if (buffer == NULL) return 0x8000000;

  // 8 bytes header
  uint16_t* header = (uint16_t*)buffer;
  header[0] = 0;                        // use mml
  header[1] = 0;                        // use pdx
  header[2] = 270;                      // offset to pcm
  header[3] = 8;                        // offset to data title

  // pdx name
  strncpy(buffer + 8, pcm_name, 270 - 8);

  // pcm data
  safe_memcpy(buffer + 270, pcm_data, pcm_len);

	register uint32_t reg_d0 asm ("d0") = 0x03;    // LOADPCM
  register uint32_t reg_d1 asm ("d1") = pcm_len + 270;
  register uint32_t reg_a1 asm ("a1") = (uint32_t)buffer;

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // output (&input) operand
    : "r"   (reg_d1),   // input operand
      "r"   (reg_a1)    // input operand
    :                   // clobbered register
  );

  free(buffer);

  return reg_d0;
}

// $04 M_PLAY
uint32_t mxdrv_m_play() {
	
  register uint32_t reg_d0 asm ("d0") = 0x04;    // M_PLAY

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r" (reg_d0)     // output (&input) operand
    :                   // input operand
    :                   // clobbered register
  );

  return reg_d0;
}

// $05 M_END
uint32_t mxdrv_m_end() {
	
  register uint32_t reg_d0 asm ("d0") = 0x05;    // M_END

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r" (reg_d0)     // output (&input) operand
    :                   // input operand
    :                   // clobbered register
  );

  return reg_d0;
}

// $06 M_STOP
uint32_t mxdrv_m_stop() {

	register uint32_t reg_d0 asm ("d0") = 0x06;    // M_STOP

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r" (reg_d0)     // output (&input) operand
    :                   // input operand
    :                   // clobbered register
  );

  return reg_d0;
}

// $07 M_CONT
uint32_t mxdrv_m_cont() {

	register uint32_t reg_d0 asm ("d0") = 0x07;    // M_CONT

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r" (reg_d0)     // output (&input) operand
    :                   // input operand
    :                   // clobbered register
  );

  return reg_d0;
}

// $08 MMLNAME
uint8_t* mxdrv_mml_name() {

	register uint32_t reg_d0 asm ("d0") = 0x08;    // MMLNAME
  register uint32_t reg_d1 asm ("d1") = 0;

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // output (&input) operand
    : "r"   (reg_d1)    // input operand
    :                   // clobbered register
  );

  return (uint8_t*)reg_d0;
}

// $09 PCMNAME
uint8_t* mxdrv_pcm_name() {

	register uint32_t reg_d0 asm ("d0") = 0x09;    // PCMNAME
  register uint32_t reg_d1 asm ("d1") = 0;

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // output (&input) operand
    : "r"   (reg_d1)    // input operand
    :                   // clobbered register
  );

  return (uint8_t*)reg_d0;
}

// $0C M_FADEOUT
uint32_t mxdrv_m_fadeout(uint16_t speed) {

	register uint32_t reg_d0 asm ("d0") = 0x0C;    // M_FADEOUT
  register uint32_t reg_d1 asm ("d1") = speed;

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // output (&input) operand
    : "r"   (reg_d1)    // input operand
    :                   // clobbered register
  );

  return reg_d0;
}

// $12 M_STAT
uint16_t mxdrv_m_stat() {

	register uint32_t reg_d0 asm ("d0") = 0x12;    // M_STAT

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // input & output operand
    :                   // input operand
    :                   // clobbered register
  );

  return reg_d0 & 0xFFFF;
}

// $14 M_STAT2
uint16_t mxdrv_m_stat2() {

	register uint32_t reg_d0 asm ("d0") = 0x14;    // M_STAT2

  asm volatile (
    "trap #4\n"         // trap #4
    : "+r"  (reg_d0)    // input & output operand
    :                   // input operand
    :                   // clobbered register
  );

  return reg_d0 & 0xFFFF;
}

// mxdrv keep check with trap#4 vector
int16_t mxdrv_isavailable() {

//  uint32_t eye_catch_addr = B_LPEEK((uint32_t*)0x0090) - 12;
  uint32_t eye_catch_addr = (uint32_t)_dos_intvcg(0x24) - 12;

  uint8_t eye_catch[12];
  for (int16_t i = 0; i < 12; i++) {
    eye_catch[i] = _iocs_b_bpeek((uint8_t*)(eye_catch_addr + i));
  }

  return (memcmp(eye_catch, "EX16mxdrv206", 12) == 0) ? 1 : 0;
}