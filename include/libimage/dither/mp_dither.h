/*******************************************************************************
	Copyright Ringsd. 2016.
	All Rights Reserved.
	
	File: mp_dither.h

	Description:

	TIME LIST:
	CREATE By Ringsd   2016/1/23 04:03:48

*******************************************************************************/

#ifndef _mp_dither_h_
#define _mp_dither_h_

#ifdef __cplusplus
extern "C" {
#endif

#define MP_DITHER_XRGB8888      1
#define MP_DITHER_8888_RGB565	2
#define MP_DITHER_RGB565        3
#define MP_DITHER_RGB555        4
#define MP_DITHER_RGB666        5

typedef struct mp_dither mp_dither;

int mp_dither_row( struct mp_dither* dither, const mpu8* in_ptr, mpu8* out_ptr );

int mp_dither_all( struct mp_dither* dither, const mpu8* in_buf, mpu8* out_buf );

struct mp_dither* mp_dither_create( int in_format, int out_format, int width, int height );

void mp_dither_destory( struct mp_dither* dither );

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
	END OF FILE
*******************************************************************************/
