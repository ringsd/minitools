/*******************************************************************************
    Copyright SmartAction Tech. 2017.
    All Rights Reserved.

    File: dither565.c

    Description:

    TIME LIST:
    CREATE By Ringsd   2017/04/13 15:12:44

*******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <libimage/mp_image_if.h>
#include <libimage/mp_image.h>
#include <libimage/dither/mp_dither.h>

void* lg_malloc(int size)
{
    return malloc(size);
}

void lg_free(void* p)
{
    free(p);
}

#ifdef WIN32
#define inline __inline
#pragma warning(disable:4996)
#define MAX_PATH _MAX_PATH
#else
#define MAX_PATH 260
#endif

#define REBUILD_UPDATE  "v0.1"
#define USER_NAME       "Ringsd"

static void help(void)
{
	puts("Using:");
	puts("	-i input file name");
	puts("	-o output file name");
    puts("	-v version");
	puts("	Copyright (C) 2017-2017 By:" USER_NAME " Version:" REBUILD_UPDATE);
}

static void decode_image(void)
{
    mp_image_if file;
    mp_image_if file_new;
    mp_image* image;
    mp_image* image_new;

    file.open = fopen;
    file.close = fclose;
    file.read = fread;
    file.write = fwrite;
    file.seek = fseek;
    file.tell = ftell;
    file.param1 = "test.png";
    file.param2 = "rb";

    file.open = fopen;
    file.close = fclose;
    file.read = fread;
    file.write = fwrite;
    file.seek = fseek;
    file.tell = ftell;
    file.param1 = "test_new.png";
    file.param2 = "wb";

    image_new = mp_image_open(&file, MP_IMAGE_TYPE_PNG, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_WRITE);
    image = mp_image_open(&file, MP_IMAGE_TYPE_UNKNOWN, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_READ);
    if (image)
    {
        int width, height;
        unsigned char* src;
        unsigned char* dst;
        int i = 0;
        struct mp_dither* dither;

        mp_image_size(image, &width, &height);

        dither = mp_dither_create(MP_DITHER_XRGB8888, MP_DITHER_8888_RGB565, width, height);

        src = malloc(width * 4);
        dst = malloc(width * height * 4);
        for (i = 0; i <height; i++)
        {
            mp_image_readline(image, src, i);
            mp_dither_row(dither, src, dst);
        }

        mp_dither_destory(dither);
        mp_image_close(image);
    }

    return;
}

int main(int argc, const char* argv[])
{
	int 	ret = 0;

	char** 	pp = NULL;
	char	in_path[512] = "dither.png";
	char	out_path[512] = "dither_565.png";

	if( 0 && argc == 1 )
	{
		help();
		return 0;
	}

#if 0//def WIN32
	//support window to drag
	pp = (char**)(argv + 1);
	if (*pp[0] != '-')
	{
		strcpy(in_path, *pp);
		strcpy(out_path, in_path);
	}
#endif

	for (pp = (char**)(argv + 1); *pp; pp++)
	{
		if (strcmp(*pp, "-o") == 0)
        {
            pp ++;
            if( *pp ) strcpy(out_path, *pp);
            else break;
        }
		else if (strcmp(*pp, "-i") == 0)
        {
            pp ++;
            if( *pp ) strcpy(in_path, *pp);
            else break;
        }
		else if (strcmp(*pp, "-v") == 0)
		{
			help();
			return 0;
		}
	}

    //dither565(in_path, out_path);

    decode_image();

	return ret;
}


/*******************************************************************************
    END OF FILE
*******************************************************************************/
