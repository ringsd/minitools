/*******************************************************************************
    Copyright Ringsd. 2020.
    All Rights Reserved.
    
    File: fs_2_h_patch.c

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
	puts("	-m select output module, link sc66, x1000 etc.");
	puts("	-v version");
	puts("	Copyright (C) 2021-2021 By:" USER_NAME " Version:" VERSION);
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

static void fs_2_h_patch_x1000(const char* in_path, const char* out_path)
{
    char buffer[1024];
    unsigned int checksum = 0;
    FILE* fp_r = fopen(in_path, "r");
    FILE* fp_r2 = fopen("_fs.h", "r");
    FILE* fp_w = fopen(out_path, "w");
    if (fp_r)
    {
        while (fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp_r))
        {
            if (strstr(buffer, "//CheckSum"))
            {
                sscanf(buffer, "//CheckSum: %x", &checksum);
                break;
            }
            if (strstr(buffer, "//UserCode"))
            {
                sscanf(buffer, "//UserCode: %x", &checksum);
                break;
            }
        }
        fclose(fp_r);
    }

    if (fp_r2 && fp_w)
    {
        while (fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp_r2))
        {
            if (strstr(buffer, "static unsigned char FS_chksum[2] = { 0xFF, 0xFF }; "))
            {
                sprintf(buffer, "static unsigned char FS_chksum[2] = { 0x%02x, 0x%02x };\n", (checksum >> 8) & 0xFF, (checksum >> 0) & 0xFF);
                fprintf(fp_w, "%s", buffer);
            }
            else
            {
                fprintf(fp_w, "%s", buffer);
            }
        }
        fclose(fp_r);
        printf("Done\n");
    }

    if (fp_r2)
    {
        fclose(fp_r2);
    }

    if(fp_w)
    {
        fclose(fp_w);
    }
}

static void fs_2_h_patch_sc66(const char* in_path, const char* out_path)
{
	char out_bin_path[1024];
	char buffer[1024];
	unsigned int checksum = 0;
	FILE* fp_r = fopen(in_path, "r");
	FILE* fp_r2 = fopen("_fs.h", "r");
	FILE* fp_w = fopen(out_path, "w");
	FILE* fp_w_bin;

	strcpy(out_bin_path, out_path);
	strcat(out_bin_path, ".bin");

	fp_w_bin = fopen(out_bin_path, "wb");
	if (fp_r)
	{
		while (fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp_r))
		{
			if (strstr(buffer, "//CheckSum"))
			{
				sscanf(buffer, "//CheckSum: %x", &checksum);
				break;
			}
			if (strstr(buffer, "//UserCode"))
			{
				sscanf(buffer, "//UserCode: %x", &checksum);
				break;
			}
		}
		fclose(fp_r);
	}

	if (fp_r2 && fp_w && fp_w_bin)
	{
		unsigned int fw_length = 0;
		unsigned char bin_buffer[16];
		int count = 0;

		bin_buffer[0] = (checksum >> 8) & 0xFF;
		bin_buffer[1] = (checksum >> 0) & 0xFF;
		fwrite(bin_buffer, 2, 1, fp_w_bin);
		fwrite(&fw_length, 4, 1, fp_w_bin);

		while (fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), fp_r2))
		{
			if (strstr(buffer, "static unsigned char FS_chksum[2] = { 0xFF, 0xFF }; "))
			{
				sprintf(buffer, "unsigned char FS_chksum[2] = { 0x%02x, 0x%02x };\n", (checksum >> 8) & 0xFF, (checksum >> 0) & 0xFF);
				fprintf(fp_w, "%s", buffer);
			}
			else if (strstr(buffer, "static unsigned char FS_data[][256] = {"))
			{
				sprintf(buffer, "unsigned char FS_data[][256] = {\n");
				fprintf(fp_w, "%s", buffer);
			}
			else
			{
				fprintf(fp_w, "%s", buffer);
				if (strncmp(buffer, "0x", 2) == 0)
				{
					int i = 0;
					char *input_buffer = buffer;
					for(i=0; i<16;i ++)
					{
						unsigned int temp;
						sscanf(input_buffer, "0x%02x,", &temp);
						input_buffer += 5;
						bin_buffer[i] = (unsigned char)temp;
						fw_length++;
					}

					fwrite(bin_buffer, 1, 16, fp_w_bin);
				}
			}
		}

		fprintf(fp_w, "\n");
		fprintf(fp_w, "int hbc3000_get_fw_pages(void)\n");
		fprintf(fp_w, "{\n");
		fprintf(fp_w, "    return sizeof(FS_data) / sizeof(FS_data[0]);\n");
		fprintf(fp_w, "}\n");

		fseek(fp_w_bin, 2, SEEK_SET);
		fwrite(&fw_length, 4, 1, fp_w_bin);

		fclose(fp_r);
		printf("%d Done\n", fw_length);
	}

	if (fp_r2)
	{
		fclose(fp_r2);
	}

	if (fp_w)
	{
		fclose(fp_w);
	}

	if (fp_w_bin)
	{
		fclose(fp_w_bin);
	}
}

int main(int argc, const char* argv[])
{
	int 	ret = 0;
    int     md5 = 0;

	char** 	pp = NULL;
	char	in_path[512] = "inf.txt";
	char	out_path[512] = "_fs_patch.h";
	char	module[512] = "x1000";

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
		else if (strcmp(*pp, "-m") == 0)
		{
			pp++;
			if (*pp) strcpy(module, *pp);
			else break;
		}
	}

	if (strcmp(module, "sc66") == 0)
	{
		fs_2_h_patch_sc66(in_path, out_path);
	}
	else
	{
		fs_2_h_patch_x1000(in_path, out_path);
	}

	return ret;
}


/*******************************************************************************
	END OF FILE
*******************************************************************************/
