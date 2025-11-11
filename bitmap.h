#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum __bitmap_compression_t__
{
	BI_RGB = (uint32_t)0, /* No compression. */
	BI_RLE8 = (uint32_t)1,
	BI_RLE4 = (uint32_t)2,
	BI_BITFIELDS = (uint32_t)3,
	BI_JPEG = (uint32_t)6,			  /* JPEG compression. */
	BI_PNG = (uint32_t)7,			  /* PNG compression. */
	BI_UNKNOWN = (uint32_t)UINT32_MAX /* Unknown compression. */
} bitmap_compression;

#pragma pack(push, 1)
typedef struct __bitmap_header_t__
{
	uint16_t bmp_signature;	   /* HEX: 0x424D -> BM */
	uint32_t bmp_file_size;	   /* Total Bitmap file size. */
	uint32_t bmp_reserved;	   /* Reserved bytes. */
	uint32_t bmp_bytes_offset; /* Offset to image data. */
} bitmap_header;

typedef struct __bitmap_dib_header_t__
{
	uint32_t bmp_dib_header_size;				   /* Size of current header. */
	int32_t bmp_image_width;					   /* Image width. */
	int32_t bmp_image_height;					   /* Image height. */
	uint16_t bmp_image_color_plane;				   /* Aways 1. */
	uint16_t bmp_image_bits_per_pixel;			   /* Image Bits size foreach Pixel. */
	bitmap_compression bmp_image_compression_type; /* Image compression method. */
	uint32_t bmp_image_bytes_size;				   /* Image size (Bytes). */
	int32_t bmp_image_x_pels_per_meter;			   /* Image horizontal resolution. */
	int32_t bmp_image_y_pels_per_meter;			   /* Image vertical resolution. */
	uint32_t bmp_image_color_used;				   /* Number of colors in the image. */
	uint32_t bmp_image_color_important;			   /* Number of important colors in the image. */
} bitmap_dib_header;

#pragma pack(pop)

typedef struct __bitmap_t
{
	bitmap_header header;
	bitmap_dib_header info;
	unsigned char *pixels;
} bitmap;

int bitmap_read_file(const char *filename, bitmap *bmp);
int bitmap_write_file(const char *filename, bitmap *bmp);

int32_t bitmap_get_width(bitmap *bmp);
int32_t bitmap_get_height(bitmap *bmp);

uint16_t bitmap_get_bits_per_pixel(bitmap *bmp);

bitmap_compression bitmap_get_compression_type(bitmap *bmp);

void bitmap_free(bitmap *bmp);

#endif