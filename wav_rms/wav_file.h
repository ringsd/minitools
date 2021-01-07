/*******************************************************************************
	Copyright SmartAction Tech. 2014.
	All Rights Reserved.
	
	File: wav_file.h

	Description:

	TIME LIST:
	CREATE By Ringsd   2014/9/19 10:44:56

*******************************************************************************/

#ifndef _wav_file_h_
#define _wav_file_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FMT  0x20746d66
#define ID_DATA 0x61746164

struct riff_wave_header {
    uint32_t riff_id;
    uint32_t riff_sz;
    uint32_t wave_id;
};

struct chunk_header {
    uint32_t id;
    uint32_t sz;
};

struct chunk_fmt {
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
	END OF FILE
*******************************************************************************/
