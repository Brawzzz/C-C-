//==================================== INCLUDES ====================================//
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <png.h>

//==================================== STRUCTURES ====================================//
typedef struct{
    float x;
    float y;
    float z;
}CVector;

typedef CVector* PCVector;

typedef struct{
    int red;
    int green;
    int blue;
    int alpha;
}Color_RGBA;

typedef struct{
    CVector c_vector;
    Color_RGBA color;
}Seed;

typedef Seed* PSeed;

//==================================== CONSTANTS ====================================//
#define COL_TYPE_RGB 3
#define COL_TYPE_RGBA 4
#define PNG_DEBUG 3

const char* PNG_EXTENSION = "png";
const int NMB_SEED = 100;

//==================================== VARIABLES ====================================//
PSeed* seeds = NULL;

//========================== PNG VARIABLES ==========================//
int number_of_passes;
int number_of_passes_output;

int width;
int height;
int width_output;
int height_output;

png_byte color_type;
png_byte bit_depth;

png_byte color_type_output;
png_byte bit_depth_output;

png_structp PNG_PTR;
png_infop INFO_PTR;
png_bytep *ROW_POINTERS_INPUT_PNG;

png_structp PNG_PTR_OUTPUT;
png_infop INFO_PTR_OUTPUT;
png_bytep *ROW_POINTERS_OUTPUT_PNG;

//==================================== FUNCTIONS ====================================//
void abort_(const char *s, ...){
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

//========================== VECTORS FUNCTIONS ==========================//
CVector new_CVector(){
    CVector v;

    v.x = 0.f;
    v.y = 0.f;
    v.z = 0.f;

    return v;
}

CVector update_CVector(CVector v , float x , float y , float z){

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

float compute_distance(CVector v1 , CVector v2){
    return( ((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) );
}

//========================== COLORS FUNCTIONS ==========================//
Color_RGBA get_null_color(){

    Color_RGBA color;

    color.red = 0;
    color.green = 0;
    color.blue = 0;
    color.alpha = 0;

    return color;
}

Color_RGBA get_color(int red , int green , int blue , int alpha){

    Color_RGBA color;

    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;

    return color;
}

//========================== PNG FUNCTIONS ==========================//
void read_png_file(const char *file_name , int* width , int* height , png_byte* color_type , png_byte* bit_depth , int* number_of_passes){

    int png_size = 8;
    char header[png_size];

    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        abort_("[read_png_file] File %s could not be opened for reading", file_name);
    }

    fread(header, 1, png_size, fp);
    if (png_sig_cmp(header, 0, png_size)){
        abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
    }

    PNG_PTR = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!PNG_PTR){
        abort_("[read_png_file] png_create_read_struct failed");
    }

    INFO_PTR = png_create_info_struct(PNG_PTR);
    if (!INFO_PTR){
        abort_("[read_png_file] png_create_info_struct failed");
    }

    if (setjmp(png_jmpbuf(PNG_PTR))){
        abort_("[read_png_file] Error during init_io");
    }

    png_init_io(PNG_PTR, fp);
    png_set_sig_bytes(PNG_PTR, 8);

    png_read_info(PNG_PTR, INFO_PTR);

    *width = png_get_image_width(PNG_PTR, INFO_PTR);
    *height = png_get_image_height(PNG_PTR, INFO_PTR);
    *color_type = png_get_color_type(PNG_PTR, INFO_PTR);
    *bit_depth = png_get_bit_depth(PNG_PTR, INFO_PTR);

    *number_of_passes = png_set_interlace_handling(PNG_PTR);
    png_read_update_info(PNG_PTR, INFO_PTR);

    if (setjmp(png_jmpbuf(PNG_PTR))){
        abort_("[read_png_file] Error during read_image");
    }

    ROW_POINTERS_INPUT_PNG = (png_bytep *)malloc(sizeof(png_bytep) * (*height));
    for (int y = 0 ; y < (*height) ; y++){
        ROW_POINTERS_INPUT_PNG[y] = (png_byte *)malloc(png_get_rowbytes(PNG_PTR, INFO_PTR));
    }
    png_read_image(PNG_PTR, ROW_POINTERS_INPUT_PNG);

    fclose(fp);
}

void write_png_file(const char *file_name , int width_output , int height_output , png_byte bit_depth_output , png_byte color_type_output){

    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        abort_("[write_png_file] File %s could not be opened for writing", file_name);
    }

    PNG_PTR_OUTPUT = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!PNG_PTR_OUTPUT){
        abort_("[write_png_file] png_create_write_struct failed");
    }

    INFO_PTR_OUTPUT = png_create_info_struct(PNG_PTR_OUTPUT);
    if (!INFO_PTR_OUTPUT){
        abort_("[write_png_file] png_create_info_struct failed");
    }

    if (setjmp(png_jmpbuf(PNG_PTR_OUTPUT))){
        abort_("[write_png_file] Error during init_io");
    }
    png_init_io(PNG_PTR_OUTPUT, fp);

    if (setjmp(png_jmpbuf(PNG_PTR_OUTPUT))){
        abort_("[write_png_file] Error during writing header");
    }

    png_set_IHDR(PNG_PTR_OUTPUT , INFO_PTR_OUTPUT , width_output , height_output , bit_depth_output , 
                color_type_output , PNG_INTERLACE_NONE , PNG_COMPRESSION_TYPE_BASE , PNG_FILTER_TYPE_BASE);
    png_write_info(PNG_PTR_OUTPUT, INFO_PTR_OUTPUT);

    if (setjmp(png_jmpbuf(PNG_PTR_OUTPUT))){
        abort_("[write_png_file] Error during writing bytes");
    }
    png_write_image(PNG_PTR_OUTPUT, ROW_POINTERS_OUTPUT_PNG);

    if (setjmp(png_jmpbuf(PNG_PTR_OUTPUT))){
        abort_("[write_png_file] Error during end of write");
    }
    png_write_end(PNG_PTR_OUTPUT, NULL);

    for (int y = 0 ; y < height_output ; y++){
        free(ROW_POINTERS_OUTPUT_PNG[y]);
    }
    free(ROW_POINTERS_OUTPUT_PNG);
    fclose(fp);
}

png_bytep *allocates_image_memory(int width, int height){
    png_bytep *row_pointers_output;

    row_pointers_output = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0 ; y < height ; y++){
        row_pointers_output[y] = (png_byte *)malloc(sizeof(png_byte) * sizeof(int) * width);
    }

    return row_pointers_output;
}

//========================== SEEDS FUNCTIONS ==========================//
PSeed new_Seed(){

    PSeed s = (PSeed)malloc(sizeof(Seed));
    s -> c_vector = new_CVector();
    s -> color = get_null_color();

    return s;
}

PSeed update_Seed(CVector v , Color_RGBA color){

    PSeed s = new_Seed();
    s -> c_vector = v;
    s -> color = color;

    return s;
}

PSeed* place_Seed_PNG(png_bytep *ROW_POINTERS_INPUT_PNG , const int NMB_SEED , int width , int height){

    PSeed* seeds = (PSeed*)malloc(sizeof(PSeed) * NMB_SEED);
    PSeed ptr_seed_i = NULL;
    CVector v_seed_i = new_CVector();

    int x_seed_i = 0;
    int y_seed_i = 0;

    png_byte* row = NULL;
    png_byte* ptr = NULL;

    for (int i = 0 ; i < NMB_SEED ; i++){
        
    }

    return seeds;
}

//========================== VORONIZING FUNCTIONS ==========================//
void voronizing_file(png_bytep *ROW_POINTERS_OUTPUT_PNG , PSeed* seeds , int NMB_SEED , int width , int height){

    float dist_min = __FLT_MAX__;
    float distance = 0;

    CVector current_pixel = new_CVector();
    PSeed pixel_seed = new_Seed();

    for (int y = 0 ; y < height ; y++){
        for (int x = 0 ; x < width ; x++){

            int offset = (y * width + x) * COL_TYPE_RGB;

            current_pixel = update_CVector(current_pixel , x , y , 0);
            pixel_seed = new_Seed();
            
            dist_min = __FLT_MAX__;
            distance = 0;

            for (int i = 0 ; i < NMB_SEED ; i++){
                distance = compute_distance((seeds[i] -> c_vector) , current_pixel);

                if (distance < dist_min){
                    dist_min = distance;
                    pixel_seed = seeds[i];
                }
            }

            png_byte *row = ROW_POINTERS_OUTPUT_PNG[y];
            png_byte *ptr = &(row[x * 4]);

            ptr[0] = (pixel_seed -> color).red;
            ptr[1] = (pixel_seed -> color).green;
            ptr[2] = (pixel_seed -> color).blue;
            ptr[3] = (pixel_seed -> color).alpha;
        }
    }
}

//==================================== MAIN ====================================//
int main(int argc, char const *argv[]){
    
    srand(time(NULL));

    if (argc != 3){
        printf("To few file argument");
        exit(1);
    }
    else{
        
        const char* input_file_name = argv[1];
        const char* output_file_name = argv[2];

        const char* input_file_extension = get_file_extension(input_file_name);
        const char* output_file_extension = get_file_extension(output_file_name);

        int cmp_file = strcmp(input_file_extension , output_file_extension);
        int cmp_png = strcmp(input_file_extension , PNG_EXTENSION);

        if (cmp_file != 0){
            printf("The input file and the output file have not the same extension !\n");
            return EXIT_FAILURE;
        }

        if (cmp_png == 0){
            printf("input_file_name : %s , output_file_name : %s\n\n", input_file_name , output_file_name);

            read_png_file(input_file_name , &width , &height , &color_type , &bit_depth , &number_of_passes);

            width_output = width;
            height_output = height;
            color_type_output = PNG_COLOR_TYPE_RGBA;
            bit_depth_output = 8;
            number_of_passes_output = 2;

            ROW_POINTERS_OUTPUT_PNG = allocates_image_memory(width_output, height_output);

            printf("Computing voronoi ... ");
            time_t begin = time(NULL);
            voronizing_file(ROW_POINTERS_OUTPUT_PNG ,  seeds , NMB_SEED , width , height);
            time_t end = time(NULL);
            unsigned long seconds = (unsigned long) difftime(end , begin);
            printf( "Finished in %ld seconds\n\n", seconds );

            printf("Writing the voronizing picture ... ");
            write_png_file(output_file_name , width_output , height_output , bit_depth_output , color_type_output);   
            printf("DONE !\n\n");

            return EXIT_SUCCESS;
        }
        else{ 
            printf("Extensions not reconized\n");
            return EXIT_FAILURE;
        }
    }
}