/*******************************************************************************
    Copyright Ringsd. 2020.
    All Rights Reserved.

    File: orc_sudoku.c

    Description:

    TIME LIST:
    CREATE By Ringsd   2020/2/9 下午9:20:47

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

static void gray_image(const char* in_file, const char* out_file)
{
	mp_image_if file;
	mp_image_if file_new;
	mp_image* image;
	mp_image* image_new;

	file.open = fopen;
	file.close = fclose;
	file.read = (int(*) (void* buffer, int size, int count, void *handle))fread;
	file.write = (int(*)(void* buffer, int size, int count, void *handle))fwrite;
	file.seek = fseek;
	file.tell = ftell;
	file.param1 = (void*)in_file;
	file.param2 = "rb";

	memcpy(&file_new, &file, sizeof(mp_image_if) );
	file_new.param1 = (void*)out_file;
	file_new.param2 = "wb";

	image = mp_image_open(&file, MP_IMAGE_TYPE_UNKNOWN, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_READ);
	image_new = mp_image_open(&file_new, MP_IMAGE_TYPE_PNG, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_WRITE);
	if (image)
	{
		int width, height;
		unsigned char* src;
		unsigned char* dst;
		int i = 0;
		int gray_count[256];
		int gray_max = 0;

		memset(gray_count, 0, sizeof(gray_count));

		mp_image_size(image, &width, &height);

		mp_image_ctl(image_new, MP_IMAGE_SET_SIZE, width, height);

		src = malloc(width * 4);
		dst = malloc(width * 4);
		for (i = 0; i < height; i++)
		{
			int j;
			mp_image_readline(image, src, i);

			//swap the r & b
			for (j = 0; j < width; j++)
			{
				unsigned char r = src[j * 4 + 0];
				unsigned char g = src[j * 4 + 1];
				unsigned char b = src[j * 4 + 2];

				//平均值法
				unsigned char gray = (r + g + b) / 3;

				//最大值法
				//unsigned char gray = max(max(r, g), b);

				//加权平均法
				//unsigned char gray = 0.3 * r + 0.59 * g + 0.11 * b;

				gray_count[gray] ++;
				gray_max = max(gray_max, gray_count[gray]);

				dst[j * 4 + 0] = gray;
				dst[j * 4 + 1] = gray;
				dst[j * 4 + 2] = gray;
				dst[j * 4 + 3] = src[j * 4 + 3];//alpha
			}

			mp_image_writeline(image_new, dst, i);
		}

#if 0
		{
			mp_image_if file_gray;
			mp_image* image_gray;
			int gray_color[256];
			file_gray.open = fopen;
			file_gray.close = fclose;
			file_gray.read = fread;
			file_gray.write = fwrite;
			file_gray.seek = fseek;
			file_gray.tell = ftell;
			file_gray.param1 = "..\\test\\gray.png";
			file_gray.param2 = "wb";
			image_gray = mp_image_open(&file_gray, MP_IMAGE_TYPE_PNG, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_WRITE);

			mp_image_ctl(image_gray, MP_IMAGE_SET_SIZE, 256, 256);

			for (i = 0; i < 256; i++)
			{
				int min_val = min(255, gray_count[i] * 256 / gray_max);
				gray_count[i] = min_val;
			}

			for (i = 0; i < 256; i++)
			{
				int j = 0;
				for (j = 0; j < 256; j++)
				{
					if (gray_count[j] >= 255 - i)
						gray_color[j] = 0xFFFF0000;
					else
						gray_color[j] = 0xFFFFFFFF;
				}
				mp_image_writeline(image_gray, gray_color, i);
			}
			mp_image_close(image_gray);
		}
#endif

		mp_image_close(image);
		mp_image_close(image_new);
	}

	return;
}


static void binarization_image(const char* in_file, const char* out_file)
{
	mp_image_if file;
	mp_image_if file_new;
	mp_image* image;
	mp_image* image_new;

	file.open = fopen;
	file.close = fclose;
	file.read = (int(*) (void* buffer, int size, int count, void *handle))fread;
	file.write = (int(*)(void* buffer, int size, int count, void *handle))fwrite;
	file.seek = fseek;
	file.tell = ftell;
	file.param1 = (void*)in_file;
	file.param2 = "rb";

	memcpy(&file_new, &file, sizeof(mp_image_if));
	file_new.param1 = (void*)out_file;
	file_new.param2 = "wb";

	image = mp_image_open(&file, MP_IMAGE_TYPE_UNKNOWN, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_READ);
	image_new = mp_image_open(&file_new, MP_IMAGE_TYPE_PNG, MP_IMAGE_COLOR_MODE_ARGB, MP_IMAGE_FLAG_WRITE);
	if (image)
	{
		int width, height;
		unsigned char* src;
		unsigned char* dst;
		int i = 0;
		int gray_count[256];
		int gray_max = 0;

		memset(gray_count, 0, sizeof(gray_count));

		mp_image_size(image, &width, &height);

		mp_image_ctl(image_new, MP_IMAGE_SET_SIZE, width, height);

		src = malloc(width * 4);
		dst = malloc(width * 4);
		for (i = 0; i < height; i++)
		{
			int j;
			mp_image_readline(image, src, i);

			//swap the r & b
			for (j = 0; j < width; j++)
			{
				unsigned char gray = src[j * 4 + 0];

				if (gray < 128) gray = 0;
				else gray = 255;

				dst[j * 4 + 0] = gray;
				dst[j * 4 + 1] = gray;
				dst[j * 4 + 2] = gray;
				dst[j * 4 + 3] = src[j * 4 + 3];//alpha
			}

			mp_image_writeline(image_new, dst, i);
		}
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
	char	gray_path[512] = "dither_gray.png";
	char	binarization_path[512] = "dither_binarization.png";

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
			if (strcmp(*pp, "-i") == 0)
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
                memset(gray_path, 0, sizeof(gray_path));
				memset(binarization_path, 0, sizeof(binarization_path));
				strcpy(in_path, *pp);
                s = strrchr(*pp, '.');
                if (s)
                {
                    strncpy(gray_path, *pp, s - *pp);
                    strcat(gray_path, "_gray");
                    strcat(gray_path, s);

					strncpy(binarization_path, *pp, s - *pp);
					strcat(binarization_path, "_bina");
					strcat(binarization_path, s);

					gray_image(in_path, gray_path);
					binarization_image(gray_path, binarization_path);
				}
            }
        }
    }

	return ret;
}


//fixed the new visual studio modify the stdio error
#if _MSC_VER >= 1900

#include "stdio.h" 
_ACRTIMP_ALT FILE * __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C" {
#endif 
FILE* __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}

FILE _iob[3];

#undef __mb_cur_max
int __mb_cur_max(void)
{
	return ___mb_cur_max_func();
}

#if 0
#undef _pctype
const unsigned short* _pctype(void)
{
	return __pctype_func();
}
#endif

#undef _sys_nerr
int * _sys_nerr(void)
{
	return	__sys_nerr();
}

#ifdef __cplusplus 
}
#endif 

#endif /* _MSC_VER>=1900 */


/*******************************************************************************
    END OF FILE
*******************************************************************************/
