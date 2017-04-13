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

#ifdef WIN32
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

	return ret;
}


/*******************************************************************************
    END OF FILE
*******************************************************************************/
