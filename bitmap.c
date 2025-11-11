#include "bitmap.h"

int bitmap_read_file(const char *filename, bitmap *bmp)
{
	if (!filename || !bmp)
	{
		return 0;
	}

	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return 0;

	fread(&bmp->header, sizeof(bitmap_header), 1, fp);
	fread(&bmp->info, sizeof(bitmap_dib_header), 1, fp);

	bmp->pixels = (unsigned char *)calloc(sizeof(unsigned char), bmp->info.bmp_image_bytes_size);
	if (!bmp->pixels)
	{
		fclose(fp);
		return 0;
	}

	if (bmp->info.bmp_image_bytes_size == 0)
	{
		bmp->info.bmp_image_bytes_size =
			(bmp->info.bmp_image_width * bmp->info.bmp_image_height *
			 (bmp->info.bmp_image_bits_per_pixel / 8));
	}

	fseek(fp, bmp->header.bmp_bytes_offset, SEEK_SET);
	fread(bmp->pixels, 1, bmp->info.bmp_image_bytes_size, fp);

	if (!bmp->pixels)
	{
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}

int bitmap_write_file(const char *filename, bitmap *bmp)
{
	if (!filename || !bmp || !bmp->pixels)
		return 0;

	FILE *fp = fopen(filename, "wb");
	if (!fp)
		return 0;

	fwrite(&bmp->header, sizeof(bitmap_header), 1, fp);
	fwrite(&bmp->info, sizeof(bitmap_dib_header), 1, fp);
	fseek(fp, bmp->header.bmp_bytes_offset, SEEK_SET);
	fwrite(bmp->pixels, 1, bmp->info.bmp_image_bytes_size, fp);

	fclose(fp);
	return 1;
}

int32_t bitmap_get_width(bitmap *bmp)
{
	if (!bmp)
		return 0;
	return bmp->info.bmp_image_width;
}

int32_t bitmap_get_height(bitmap *bmp)
{
	if (!bmp)
		return 0;
	return bmp->info.bmp_image_height;
}

uint16_t bitmap_get_bits_per_pixel(bitmap *bmp)
{
	if (!bmp)
		return 0;
	return bmp->info.bmp_image_bits_per_pixel;
}

bitmap_compression bitmap_get_compression_type(bitmap *bmp)
{
	if (!bmp)
		return BI_UNKNOWN;
	return bmp->info.bmp_image_compression_type;
}

void bitmap_free(bitmap *bmp)
{
	if (bmp && bmp->pixels)
		free(bmp->pixels);
}