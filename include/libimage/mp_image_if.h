/*******************************************************************************

    File: mp_image_if.h
    
    Description: 
    
    TIME LIST:
    CREATE By Ringsd   2012/9/02 03:37:06

*******************************************************************************/

#ifndef _mp_image_if_h_
#define _mp_image_if_h_

#ifdef __cplusplus
extern "C" {
#endif

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

//image interface
typedef struct tag_mp_image_if{
	//the file operation param
	void*	param1;//	the param for the open
	void*	param2;//	the param for the open
	void*	handle;//	for the operation function use
	//the file operation function
	//	[1:0]the operation style, read a image or write to a image
	//  [4:2]the color type
	unsigned int flag;
	void* (*open) ( const void* param1, const void* param2 );
	int   (*tell) ( void *handle );
	int   (*seek) ( void* handle, long offset, int fromwhere );
	int   (*read) ( void* buffer, int size, int count, void *handle );
	int   (*write)( void* buffer, int size, int count, void *handle );
	void  (*close)( void* handle );
}mp_image_if;

typedef unsigned int	mpu32;
typedef unsigned short	mpu16;
typedef unsigned char	mpu8;

typedef	int				mps32;
typedef short			mps16;
typedef char			mps8;

#define ERR_CODE_STR	printf

int mp_image_if_open( mp_image_if* stream );

int mp_image_if_tell( mp_image_if* stream );

int mp_image_if_seek( mp_image_if* stream, long offset, int fromwhere );

int mp_image_if_read( void* buffer, int size, int count, mp_image_if* stream );

int mp_image_if_write( void* buffer, int size, int count, mp_image_if* stream );

void mp_image_if_close( mp_image_if* stream );

void* mp_image_malloc( int size );

void mp_image_free( void* ptr );

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
    END OF FILE
*******************************************************************************/
