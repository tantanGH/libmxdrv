#ifndef __H_MXDRV__

#include <stdint.h>
#include <stddef.h>

#define MXDRV_EYE_CATCH             "EX16mxdrv206"
#define MXDRV_EYE_CATCH_LEN         (12)

#define MXDRV_STATUS_PLAYING        (0x0000)
#define MXDRV_STATUS_STOPPED        (0x0001)
#define MXDRV_STATUS_PAUSED         (0xFF00)
#define MXDRV_STATUS_FADEOUT_END    (0xFF01)

int32_t mxdrv_load_mml(const uint8_t* mml_data, size_t mml_len, const uint8_t* data_title, int16_t use_pdx);
int32_t mxdrv_load_pcm(const uint8_t* pcm_data, size_t pcm_len, const uint8_t* pcm_name);
int32_t mxdrv_m_play();
int32_t mxdrv_m_end();
int32_t mxdrv_m_stop();
int32_t mxdrv_m_cont();
uint8_t* mxdrv_mml_name();
uint8_t* mxdrv_pcm_name();
int32_t mxdrv_m_fadeout(uint16_t speed);
int32_t mxdrv_m_stat();
int32_t mxdrv_m_stat2();
int32_t mxdrv_isavailable();

#endif