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

static void decode_image( const char* in_file, const char* out_file )
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
    file.param1 = in_file;
    file.param2 = "rb";

    file_new.open = fopen;
    file_new.close = fclose;
    file_new.read = fread;
    file_new.write = fwrite;
    file_new.seek = fseek;
    file_new.tell = ftell;
    file_new.param1 = out_file;
    file_new.param2 = "wb";

    image = mp_image_open(&file, MP_IMAGE_TYPE_UNKNOWN, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_READ);
    image_new = mp_image_open(&file_new, MP_IMAGE_TYPE_PNG, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_WRITE);
    if (image)
    {
        int width, height;
        unsigned char* src;
        unsigned char* dst;
        int i = 0;
        struct mp_dither* dither;

        mp_image_size(image, &width, &height);

        dither = mp_dither_create(MP_DITHER_XRGB8888, MP_DITHER_8888_RGB565, width, height);

        mp_image_ctl(image_new, MP_IMAGE_SET_SIZE, width, height);

        src = malloc(width * 4);
        dst = malloc(width * 4);
        for (i = 0; i <height; i++)
        {
            int j;
            mp_image_readline(image, src, i);
            mp_dither_row(dither, src, dst);

            //swap the r & b
            for (j = 0; j < width; j++)
            {
                unsigned char c;
                c = dst[j * 4 + 0];
                dst[j * 4 + 0] = dst[j * 4 + 2];
                dst[j * 4 + 2] = c;
            }

            mp_image_writeline(image_new, dst, i);
        }

        mp_dither_destory(dither);
        mp_image_close(image);
        mp_image_close(image_new);
    }

    return;
}

int main(int argc, const char* argv[])
{
	int 	ret = 0;

	char** 	pp = NULL;
	char	in_path[512] = "dither.png";
	char	out_path[512] = "dither_565.png";

	if( argc == 1 )
	{
		help();
		return 0;
	}

    pp = (char**)(argv + 1);
    if (*pp[0] == '-')
    {
        for (pp = (char**)(argv + 1); *pp; pp++)
        {
            if (strcmp(*pp, "-o") == 0)
            {
                pp++;
                if (*pp) strcpy(out_path, *pp);
                else break;
            }
            else if (strcmp(*pp, "-i") == 0)
            {
                pp++;
                if (*pp) strcpy(in_path, *pp);
                else break;
            }
            else if (strcmp(*pp, "-v") == 0)
            {
                help();
                return 0;
            }
        }

        decode_image(in_path, out_path);
    }
    else
    {
        //support window to drag
        int i = 0;
        for (i = 1; i <argc; i++)
        {
            pp = (char**)(argv + i);
            if (*pp[0] != '-')
            {
                char* s;
                memset(in_path, 0, sizeof(in_path));
                memset(out_path, 0, sizeof(out_path));
                strcpy(in_path, *pp);
                s = strrchr(*pp, '.');
                if (s)
                {
                    strncpy(out_path, *pp, s - *pp);
                    strcat(out_path, "_565");
                    strcat(out_path, s);
                }
                else
                {
                    strcpy(out_path, *pp);
                    strcat(out_path, "_565");
                }
                decode_image(in_path, out_path);
            }
        }
    }

	return ret;
}


/*******************************************************************************
    END OF FILE
*******************************************************************************/
