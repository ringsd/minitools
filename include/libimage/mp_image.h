/*******************************************************************************

    File: mp_image.h
    
    Description: 
    
    TIME LIST:
    CREATE By Ringsd   2012/9/01 15:34:47

*******************************************************************************/

#ifndef _mp_image_h_
#define _mp_image_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "mp_image_if.h"

#define MP_IMAGE_FLAG_OFFSET	0
typedef enum MP_IMAGE_FLAG_TAG{
	MP_IMAGE_FLAG_NONE	= 0,
	MP_IMAGE_FLAG_READ	= 1,
	MP_IMAGE_FLAG_WRITE = 2,
	MP_IMAGE_FLAG_MASK  = 3,
}MP_IMAGE_FLAG;

#define MP_IMAGE_COLOR_MODE_OFFSET	3
typedef enum MP_IMAGE_COLOR_MODE_TAG{
	MP_IMAGE_COLOR_MODE_ARGB = 0, //32bit alpha(8bit) red(8bit) green(8bit) blue(8bit)
	MP_IMAGE_COLOR_MODE_XRGB,//32bit alpha(?) red(8bit) green(8bit) blue(8bit)
	MP_IMAGE_COLOR_MODE_565,//16bit red(5bit) green(6bit) blue(5bit)
	MP_IMAGE_COLOR_MODE_555,//16bit red(5bit) green(5bit) blue(5bit)
	MP_IMAGE_COLOR_MODE_MASK = 7,
}MP_IMAGE_COLOR_MODE;

typedef enum MP_IMAGE_TYPE_TAG{
	MP_IMAGE_TYPE_UNKNOWN = 0,
	MP_IMAGE_TYPE_PNG,
	MP_IMAGE_TYPE_JPEG,
	MP_IMAGE_TYPE_BMP,
	MP_IMAGE_TYPE_MAX,
}MP_IMAGE_TYPE;

typedef struct mp_image mp_image;

/*******************************************************************************
        COMMAND For The libs
*******************************************************************************/

#define MP_IMAGE_SET_SIZE           0x0001
#define MP_IMAGE_SET_IN_COLOR       0x0002
#define MP_IMAGE_SET_OUT_COLOR      0x0003


/*******************************************************************************
        Common interface for all image
*******************************************************************************/

MP_IMAGE_TYPE mp_image_check_type( mp_image_if* stream );

//argb order
//alpha value 0xFF transparent is 0%, 0x00 transparent is 100%

mp_image* mp_image_open( mp_image_if* file, MP_IMAGE_TYPE image_type, MP_IMAGE_COLOR_MODE color_mode, MP_IMAGE_FLAG flag );

int mp_image_size( mp_image* image, int* width, int* height );

int mp_image_read( mp_image* image, void* buf, int width, int height );

int mp_image_readline( mp_image* image, void* buf, int scanline );

//support only png
int mp_image_write( mp_image* image, void* buf, int width, int height );

int mp_image_writeline(mp_image* image, void* buf, int scanline);

int mp_image_ctl( mp_image* image, int cmd, int iparam, int wparam );

void mp_image_close( mp_image* image );


/*******************************************************************************
        Only for jpeg
*******************************************************************************/


/*******************************************************************************
        Only for png
*******************************************************************************/


/*******************************************************************************
        Only for bmp
*******************************************************************************/



#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
    END OF FILE
*******************************************************************************/
