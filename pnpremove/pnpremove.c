/*******************************************************************************
    Copyright Ringsd. 2020.
    All Rights Reserved.
    
    File: pnpremove.c

    Description:

    TIME LIST:
    CREATE By Ringsd   2020/07/30 10:19:15

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

#define VERSION         "v0.1"
#define USER_NAME       "Ringsd"

static void help(void)
{
	puts("Using:");
	puts("	-i input file name");
	puts("	-o output file name");
    puts("	-x exclude file name");
    puts("	-v version");
	puts("	Copyright (C) 2017-2017 By:" USER_NAME " Version:" VERSION);
}

#define MAX_BUFFER_SIZE		1024

#define MAX_NAME_LENGTH     128
#define MAX_ITEM_COUNT      10

char* trim(char* str)
{
    char *str_org, *str_last, *str_cur;
    if (str == NULL)
        return NULL;
    str_org = str;
    str_cur = str;
    //found the front space and \t
    for (; *str_cur == ' ' || *str_cur == '\t'; ++str_cur);

    for (str_last = str_cur; *str_cur != '\0'; )
    {
        if (*str_cur != ' ' && *str_cur != '\t')
        {
            str_last = str;
        }
        *str++ = *str_cur++;
    }
    *++str_last = '\0';
    return str_org;
}

static void pnpremove(const char* in_path, const char* out_path)
{
    char buffer[2][1024];
    FILE* fp_r = fopen(in_path, "r");
    FILE* fp_w = fopen(out_path, "w");
    if (fp_r)
    {
        while (fgets(buffer[1], sizeof(buffer[0]) / sizeof(buffer[0][0]), fp_r))
        {
            if (strstr(buffer[1], "VID_0A12&PID_4010"))
            {
                if (strstr(buffer[0], "INF"))
                {
                    char cmd[1024];
                    sprintf(cmd, "Pnputil.exe -f -d %s", &buffer[0][11]);
                    if (fp_w)
                    {
                        fprintf(fp_w, "%s\n", cmd);
                    }
                }
            }
            strcpy(buffer[0], buffer[1]);
        }
        fclose(fp_r);
    }

    if(fp_w)
    {
        fclose(fp_w);
    }
}

int main(int argc, const char* argv[])
{
	int 	ret = 0;
    int     md5 = 0;

	char** 	pp = NULL;
	char	in_path[512] = "inf.txt";
	char	out_path[512] = "remove_inf.bat";

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

    pnpremove(in_path, out_path);

	return ret;
}


/*******************************************************************************
	END OF FILE
*******************************************************************************/
