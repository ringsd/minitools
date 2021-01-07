// GenWav.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "wav_file.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp = NULL;
	struct riff_wave_header	riff_wave_header;
	struct chunk_header chunk_header;
	struct chunk_fmt chunk_fmt;
	int ret = 0;
	unsigned int riff_size = 0;
	unsigned int data_left, data_right = 0;
	int seconds = 0;
	int i = 0;

	ret = fopen_s( &fp, "generate.wav", "wb" );
	if ( ret )
	{
		goto err;
	}

	//riff wave header
	riff_wave_header.riff_id = ID_RIFF;
	riff_wave_header.riff_sz = 0;
	riff_wave_header.wave_id = ID_WAVE;
	riff_size = 4;
	fwrite( &riff_wave_header, sizeof(riff_wave_header), 1, fp );

	//chunk fmt
	chunk_header.id = ID_FMT;
	chunk_header.sz = sizeof(chunk_fmt);
	fwrite( &chunk_header, sizeof(chunk_header), 1, fp );
	riff_size += sizeof(chunk_header);

	chunk_fmt.audio_format = 1;//pcm == 1
	chunk_fmt.num_channels = 2;
	chunk_fmt.sample_rate = 44100;
	chunk_fmt.bits_per_sample = 32;
	chunk_fmt.byte_rate = chunk_fmt.sample_rate * chunk_fmt.num_channels * chunk_fmt.bits_per_sample / 8; //  == SampleRate * NumChannels * BitsPerSample/8
	chunk_fmt.block_align = chunk_fmt.num_channels * chunk_fmt.bits_per_sample / 8; //  == NumChannels * BitsPerSample/8
	fwrite( &chunk_fmt, sizeof(chunk_fmt), 1, fp );
	riff_size += chunk_header.sz;

	//chunk data
	seconds = 10;

	chunk_header.id = ID_DATA;
	chunk_header.sz = chunk_fmt.bits_per_sample * chunk_fmt.num_channels / 8 * seconds * chunk_fmt.sample_rate;
	fwrite( &chunk_header, sizeof(chunk_header), 1, fp );
	riff_size += sizeof(chunk_header);

	data_left = 0;
	data_right = 0;
	for ( i=0; i<(int)chunk_fmt.sample_rate * chunk_fmt.num_channels * seconds; i++ )
	{
		if( i%768 == 0 )
		{
			if ( data_left == 0x00000000 )
			{
				data_left = 0xFFFFFFFF;
			}
			else
			{
				data_left = 0x00000000;
			}
		}
		if ( i%2==0 )
		{
			fwrite( &data_left, sizeof(data_left), 1, fp );
		}
		else
		{
			fwrite( &data_left, sizeof(data_left), 1, fp );
		}
	}
	riff_size += chunk_header.sz;

	fseek( fp, 0, SEEK_SET );
	riff_wave_header.riff_sz = riff_size;
	fwrite( &riff_wave_header, sizeof(riff_wave_header), 1, fp );

	fclose(fp);

	return 0;
err:
	return -1;
}

