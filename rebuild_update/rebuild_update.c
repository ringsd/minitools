/*******************************************************************************
    Copyright Ringsd. 2017.
    All Rights Reserved.
    
    File: rebuild_update.c

    Description:

    TIME LIST:
    CREATE By Ringsd   2017/02/25 10:19:15

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

#define MAX_BUFFER_SIZE		1024

#define MAX_NAME_LENGTH     128
#define MAX_ITEM_COUNT      10

enum{
    CFG_NAME = 0,
    CFG_FILE_PATH,
    CFG_MD5,
    CFG_FULL_UPGRADE,
};

struct cfg_match_s{
    int index;
    char* key;
};

struct cfg_item_s{
    char key[MAX_NAME_LENGTH];
    char value[MAX_NAME_LENGTH];
};

struct update_item_s{
    char name[MAX_NAME_LENGTH];
    int cfg_item_count;
    struct cfg_item_s   cfg_item[MAX_ITEM_COUNT];
};

struct update_file_s{
    char name[MAX_NAME_LENGTH];
    int update_item_count;
    struct update_item_s   update_item[MAX_ITEM_COUNT];
};

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

static struct cfg_item_s* find_cfg_item(struct update_item_s* update_item, char* key)
{
    int i = 0;
    for (i = 0; i <update_item->cfg_item_count; i++)
    {
        if (strcmp(key, update_item->cfg_item[i].key) == 0)
        {
            return &update_item->cfg_item[i];
        }
    }
    return NULL;
}

extern
void
md5sum(FILE *fd, char *name, int hex, char* md5str);

static int rebuild_update(char* in_path, char* out_path)
{
	int		i, ret = 0;
    char    buf[MAX_BUFFER_SIZE];
    struct update_file_s* update_file = NULL;
    struct update_item_s* update_item = NULL;
    struct cfg_item_s* cfg_item = NULL;
    FILE* fout;
    FILE* fin = fopen(in_path, "r");
    if( fin == NULL )
    {
        ret = -1;
        goto err1;
    }
    
    update_file = (struct update_file_s*)malloc(sizeof(struct update_file_s));
    if( update_file == NULL )
    {
        ret = -2;
        goto err2;
    }
    memset(update_file, 0, sizeof(struct update_file_s));

    while( fgets(buf, MAX_BUFFER_SIZE-1, fin) )
    {
        int len = 0;
        printf( "%s \n", buf );

        trim(buf);
        len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n')
        {
            buf[len-1] = '\0';
        }

        len = strlen(buf);
        if (len <= 0) continue;


        if( buf[0] == '}' )
        {
            update_item = NULL;
        }
        else if (buf[len-1] == '{')
        {
            update_item = &update_file->update_item[update_file->update_item_count];
            sscanf( buf, "%[^=]", update_item->name );
            update_file->update_item_count ++;
            if( update_file->update_item_count >= MAX_ITEM_COUNT )
            {
                break;
            }
        }
        else
        {
            if (update_item)
            {
                int update_count = update_file->update_item_count;
                int cfg_count = update_item->cfg_item_count;
                struct cfg_item_s* cfg_item = &update_item->cfg_item[cfg_count];
                sscanf(buf, "%[^=]=%s", cfg_item->key, cfg_item->value);
                update_item->cfg_item_count++;
                if (update_item->cfg_item_count >= MAX_ITEM_COUNT)
                {
                    break;
                }
            }
        }
    }

    fclose( fin );
    
    for (i = 0; i<update_file->update_item_count; i++)
    {
        struct cfg_item_s* cfg_item;
        char md5_sum[128];
        char path[MAX_PATH];
        char* pindex = NULL;
        FILE* fp = NULL;

        update_item = &update_file->update_item[i];
        cfg_item = find_cfg_item(update_item, "file_path");

        strcpy(path, in_path);
        pindex = strrchr(path, '\\');
        if(pindex)
        {
            *pindex = 0;
        }
        else
        {
            pindex = strrchr(path, '/');
            if (pindex)
            {
                *pindex = 0;
            }
            else
            {
                memset(path, 0, sizeof(path));
            }
        }

        strcat(path, strrchr(cfg_item->value, '/') + 1);

        fp = fopen(path, "rb");
        if (fp)
        {
            md5sum(fp, path, 1, md5_sum);

            cfg_item = find_cfg_item(update_item, "md5");
            strcpy(cfg_item->value, md5_sum);
            fclose( fp );
        }
    }

    fout = fopen(out_path, "wb");
    if (fout)
    {
        for (i = 0; i < update_file->update_item_count; i++)
        {
            struct cfg_item_s* cfg_item;
            int j = 0;

            update_item = &update_file->update_item[i];
            fprintf(fout, "%s={\n", update_item->name);
            for (j = 0; j<update_item->cfg_item_count; j++)
            {
                cfg_item = &update_item->cfg_item[j];
                fprintf(fout, "        %s=%s\n", cfg_item->key, cfg_item->value);
            }
            fprintf(fout, "}\n\n");
        }
        fclose(fout);
    }

    return ret;
    
err2:
	fclose(fin);
err1:
	return ret;
}

int main(int argc, const char* argv[])
{
	int 	ret = 0;

	char** 	pp = NULL;
	char	in_path[512] = "update.txt";
	char	out_path[512] = "update.txt";

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

    rebuild_update(in_path, out_path);

	return ret;
}


/*******************************************************************************
	END OF FILE
*******************************************************************************/
