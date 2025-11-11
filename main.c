#define DEBUG_MODE 0

#include <stdio.h>
#include "bitmap.h"

void invert_bitmap_colors(bitmap *bmp);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Use: %s [input.bmp] [output.bmp]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	const char *input_filename = argv[1];
	const char *output_filename = argv[2];

	bitmap input_bmp = {0};

	if (bitmap_read_file(input_filename, &input_bmp) != 1)
	{
		fprintf(stderr, "Erro ao ler a imagem!\n");
		exit(EXIT_FAILURE);
	}

#if DEBUG_MODE == 1
	printf(" ~ [DEBUG MODE] ~\n");
	printf("=============================\n");

	printf("Width: %d\nHeight: %d\n", bitmap_get_width(&input_bmp), bitmap_get_height(&input_bmp));

	printf("Compression type: %d\n", (int)bitmap_get_compression_type(&input_bmp));

	printf("Header size: %u\n", input_bmp.info.bmp_dib_header_size);
	printf("Width: %d\n", input_bmp.info.bmp_image_width);
	printf("Height: %d\n", input_bmp.info.bmp_image_height);
	printf("Bits per pixel: %d\n", input_bmp.info.bmp_image_bits_per_pixel);

	printf("=============================\n");
#endif

	invert_bitmap_colors(&input_bmp);

	if (bitmap_write_file(output_filename, &input_bmp) != 1)
	{
		fprintf(stderr, "Erro ao salvar a imagem!\n");
		exit(EXIT_FAILURE);
	}

	printf("Imagem salva com sucesso!\n");
	return EXIT_SUCCESS;
}

void invert_bitmap_colors(bitmap *bmp)
{
	if (!bmp || !bmp->pixels)
		return;

	int bytes_per_pixel = bitmap_get_bits_per_pixel(bmp) / 8;
	if (bytes_per_pixel < 3)
		return;

	uint32_t total_bytes = bmp->info.bmp_image_bytes_size;

	for (uint32_t i = 0; i < total_bytes; i += bytes_per_pixel)
	{
		bmp->pixels[i] = 255 - bmp->pixels[i];
		bmp->pixels[i + 1] = 255 - bmp->pixels[i + 1];
		bmp->pixels[i + 2] = 255 - bmp->pixels[i + 2];
	}
}