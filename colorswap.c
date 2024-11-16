// jpeg colorswap program

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
//#include <libjpeg.h>
#include "/usr/local/opt/jpeg/include/jpeglib.h"

// ./colorswap [-t tolerance#] *.jpeg (filename)

// RGB data
typedef struct RGB_s {
	uint8_t r, g, b;
}RGB;

//------Functions-------
// Options
void select_rgb_search(void);
void select_rgb_swap(void);

// Read jpeg into array

// Get current pixel color in array
RGB* get_curr_color(uint8_t *array, unsigned long byte_idx);

// Compare with target color
bool compare(RGB *to_match, RGB *to_swap, int tolerance);

// Change color if match

// Set custom RGB, returns RGB*

int
main(int argc, char *argv[]) {	
	RGB red;
	red.r = 255; red.g = 0; red.b = 0;
	RGB orange;
	orange.r = 255; orange.g = 127; orange.b = 0;
	RGB yellow;
	yellow.r = 255; yellow.g = 255; yellow.b = 0;
	RGB green;
	green.r = 0; green.g = 255; green.b = 0;
	RGB blue;
	blue.r = 0; blue.g = 0; blue.b = 255;
	RGB purple;
	purple.r = 148; purple.g = 0; purple.b = 211;

	// Buffer accepted RGB values to match colors with more or less pixels
	int tolerance = 30;
	int opt;
	size_t i;
	uint8_t *jpeg_byte_array = NULL;
	FILE *infile = NULL;
	int width, height, num_data_values;
	size_t bytes_uncompressed;

	struct jpeg_decompress_struct compression_info;
	struct jpeg_error_mgr jpeg_error;
	
	while((opt = getopt(argc, argv, "t:h")) != EOF) {
		switch(opt) {
			case 't':
				for(i = 0; i < strlen(optarg); ++i) {
					if(!isdigit(optarg[i])) return EXIT_FAILURE;	
				}
				tolerance = atoi(optarg);
				break;
			case 'h':
				printf("Usage: %s [-t tolerance# (default 30)] [-h help]\n", argv[0]);
				break;
			default:
				// Only accepts 1 file (LAST ARG)
				if(optind < argc) {
					if((infile = fopen(argv[optind], "rb")) == NULL) {
						fprintf(stderr, "ERROR: Cannot open %s\n", argv[optind]);
						return EXIT_FAILURE;
					}
					else {
						break;
					}
				}
				fprintf(stderr, "ERROR: Missing file argument\n");
				return EXIT_FAILURE;
		}
	}
	
	compression_info.err = jpeg_std_error(&jpeg_error);
	jpeg_create_decompress(&compression_info);
	jpeg_stdio_src(&compression_info, infile);
	jpeg_read_header(&compression_info, TRUE);
	
	// In pixels (functions return int)
	width = compression_info.image_width;
	height = compression_info.image_height;

	// Number of data values per pixel for most jpeg is 3 aka(R,G,B)... return error if anything else.
	if((num_data_values = compression_info.num_components) != 3) {
		fprintf(stderr, "ERROR: jpeg file is not RGB!\n");
		return EXIT_FAILURE;
	}

	// Total bytes of uncompressed file
	// size_t: 8 bytes > int: 4 bytes (NO INT OVERFLOW!)
	bytes_uncompressed = (size_t)width * height * num_data_values;
	
	jpeg_byte_array = (uint8_t*)malloc(bytes_uncompressed);	
	memset(jpeg_byte_array, 0, bytes_uncompressed);

	if(jpeg_byte_array) free(jpeg_byte_array);	
	
	return EXIT_SUCCESS;
}

void select_rgb_search(void) {
	printf("\njpeg color swap program\n");
	printf("Select a color to find in image file:\n");
	printf("-------------------------------------\n");
	printf("(1) Red\n");
	printf("(2) Orange\n");
	printf("(3) Yellow\n");
	printf("(4) Green\n");
	printf("(5) Blue\n");
	printf("(6) Purple\n");
	printf("(7) Custom RGB value(#,#,#)\n");
	printf("-------------------------------------\n");
	printf("Enter an option number: ");
}

void select_rgb_swap(void) {
	printf("\nSelect a color to swap in:\n");
	printf("-------------------------------------\n");
	printf("(1) Red\n");
	printf("(2) Orange\n");
	printf("(3) Yellow\n");
	printf("(4) Green\n");
	printf("(5) Blue\n");
	printf("(6) Purple\n");
	printf("(7) Custom RGB value(#,#,#)\n");
	printf("-------------------------------------\n");
	printf("Enter an option number: ");
}
