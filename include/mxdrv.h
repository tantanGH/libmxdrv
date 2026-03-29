#ifndef __H_MXDRV__

#include <stdint.h>
#include <stddef.h>

#define MXDRV_EYE_CATCH             "EX16mxdrv206"
#define MXDRV_EYE_CATCH_LEN         (12)

#define MXDRV_STATUS_PLAYING        (0x0000)
#define MXDRV_STATUS_STOPPED        (0x0001)
#define MXDRV_STATUS_PAUSED         (0xFF00)
#define MXDRV_STATUS_FADEOUT_END    (0xFF01)

uint32_t mxdrv_load_mml(uint8_t* mml_data, size_t mml_len, uint8_t* data_title, int16_t use_pdx);
uint32_t mxdrv_load_pcm(uint8_t* pcm_data, size_t pcm_len, uint8_t* pcm_name);
uint32_t mxdrv_m_play();
uint32_t mxdrv_m_end();
uint32_t mxdrv_m_stop();
uint32_t mxdrv_m_cont();
uint8_t* mxdrv_mml_name();
uint8_t* mxdrv_pcm_name();
uint32_t mxdrv_m_fadeout(uint16_t speed);
uint16_t mxdrv_m_stat();
uint16_t mxdrv_m_stat2();
int16_t mxdrv_isavailable();

#endif