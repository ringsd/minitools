/*******************************************************************************
    Copyright Ringsd. 2017.
    All Rights Reserved.
    
    File: bin2c.c

    Description:

    TIME LIST:
    CREATE By Ringsd   2017/02/25 10:19:34

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#define inline __inline
#pragma warning(disable:4996)
#endif

#define USER_NAME       "Ringsd"

static void help(void)
{
	puts("Using:");
	puts("	-i input file name");
	puts("	-o output file name");
	puts("	Copyright (C) 2014-2023 " USER_NAME);
}

static int filter_scale(char* in_path, char* out_path, double scale)
{
	int		ret = 0;
	FILE	*fin = NULL;
	FILE	*fout = NULL;
	int		coef = 0;
	int		read_byte = 0;

	fin = fopen(in_path, "rb");
	if( fin == NULL )
	{
		ret = -1;
		goto err1;
	}

	fout = fopen(out_path, "wb");
	if( fout == NULL )
	{
		ret = -2;
		goto err2;
	}

	while (read_byte = fread(&coef, 4, 1, fin))
	{
		coef = (int)(coef * scale);
		fwrite(&coef, 4, 1, fout);
	}

	fclose( fout );
err2:	
	fclose(fin);
err1:
	return ret;
}

int main(int argc, const char* argv[])
{
	int 	ret = 0;

	char** 	pp = NULL;
	char	in_path[512] = "xxx.flt";
	char	out_path[512] = "xxx.scale.flt";
	double  scale = 1.0;

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
		else if (strcmp(*pp, "-scale") == 0)
		{
			pp++;
			if (*pp) scale = atof(*pp);
			else break;
		}
		else if (strcmp(*pp, "-v") == 0)
		{
			help();
			return 0;
		}
	}

	filter_scale(in_path, out_path, scale);

	return ret;
}


/*******************************************************************************
	END OF FILE
*******************************************************************************/
