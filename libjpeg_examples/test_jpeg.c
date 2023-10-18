//==================================== INCLUDES ====================================//
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <time.h>

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
#define INPUT_FILE "Mona_Lisa_1447px.jpg"
#define OUTPUT_FILE "output.jpg"
#define COL_TYPE_RGB 3
#define COL_TYPE_RGBA 4

//==================================== VARIABLES ====================================//
FILE *infile;
JSAMPROW ROW_POINTERS_INPUT;

FILE *outfile;
JSAMPROW ROW_POINTERS_OUTPUT;

int nmb_seeds = 5000;

//==================================== FUNCTIONS ====================================//
void change_colors(JSAMPLE *image_data, int width, int height) {

    for (int y = 0 ; y < height ; y++) {
        for (int x = 0 ; x < width ; x++) {
        
            int offset = (y * width + x) * COL_TYPE_RGB;
            image_data[offset] = image_data[offset];        
            image_data[offset + 1] = image_data[offset+1];  
            image_data[offset + 2] = image_data[offset+1];   
        }
    }
}

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

PSeed* place_Seed(JSAMPLE *image_data , int nmb_seeds , int width , int height){

    PSeed* seeds = (PSeed*)malloc(sizeof(PSeed) * nmb_seeds);
    PSeed ptr_seed_i = NULL;
    CVector v_seed_i = new_CVector();
    Color_RGBA seed_color = get_null_color();

    int x_seed_i = 0;
    int y_seed_i = 0;

    for (int i = 0 ; i < nmb_seeds ; i++){
        
        ptr_seed_i = new_Seed();
        seed_color = get_null_color();

        x_seed_i = rand()%width;
        y_seed_i = rand()%height;
        v_seed_i = update_CVector(v_seed_i , x_seed_i , y_seed_i , 0);

        int offset = (y_seed_i * width + x_seed_i) * COL_TYPE_RGB;
        seed_color = get_color(image_data[offset] , image_data[offset+1] , image_data[offset+2] , 0);

        (ptr_seed_i -> c_vector) = v_seed_i;
        (ptr_seed_i -> color) = seed_color;

        seeds[i] = ptr_seed_i;
    }

    return seeds;
}

float compute_distance(CVector v1 , CVector v2){
    return( ((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) );
}

void voronizing_file(JSAMPLE *image_data_out , PSeed* seeds , int width , int height){

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

            for (int i = 0 ; i < nmb_seeds ; i++){
                distance = compute_distance((seeds[i] -> c_vector) , current_pixel);

                if (distance < dist_min){
                    dist_min = distance;
                    pixel_seed = seeds[i];
                }
            }

            image_data_out[offset] = (pixel_seed -> color).red;  
            image_data_out[offset + 1] = (pixel_seed -> color).green;  
            image_data_out[offset + 2] = (pixel_seed -> color).blue; 
        }
    }
}

//==================================== MAIN ====================================//
int main() {
    
    srand(time(NULL));
    
    PSeed* seeds = NULL;

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    infile = fopen(INPUT_FILE, "rb");
    if (!infile) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier d'entree.\n");
        return EXIT_FAILURE;
    }

    // Error libjpeg
    cinfo.err = jpeg_std_error(&jerr);

    // Créer la structure de décompression
    jpeg_create_decompress(&cinfo);

    // Spécifier la source du fichier JPEG
    jpeg_stdio_src(&cinfo, infile);

    // Lire les paramètres du fichier JPEG
    jpeg_read_header(&cinfo, TRUE);

    // Commencer la décompression
    jpeg_start_decompress(&cinfo);

    // Récupérer la largeur et la hauteur de l'image
    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int num_channels = cinfo.output_components;

    // Allouer de la mémoire pour stocker les données de l'image
    unsigned char *image_data = (unsigned char *)malloc(width * height * num_channels);

    // Boucle pour lire chaque ligne de l'image
    while (cinfo.output_scanline < cinfo.output_height) {
        ROW_POINTERS_INPUT = &image_data[cinfo.output_scanline * width * num_channels];
        jpeg_read_scanlines(&cinfo, &ROW_POINTERS_INPUT, 1);
    }

    // Terminer la décompression
    jpeg_finish_decompress(&cinfo);

    // Fermer le fichier d'entrée
    fclose(infile);

    seeds = place_Seed(image_data , nmb_seeds , width , height);

    time_t begin = time(NULL);
    voronizing_file(image_data , seeds , width , height);
    time_t end = time(NULL);

    unsigned long secondes = (unsigned long) difftime(end , begin);
    printf( "Finished in %ld sec\n", secondes ); 

    // Ouvrir le fichier de sortie
    outfile = fopen(OUTPUT_FILE, "wb");
    if (!outfile) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de sortie.\n");
        return EXIT_FAILURE;
    }

    // Créer la structure de compression
    struct jpeg_compress_struct cinfo_out;
    struct jpeg_error_mgr jerr_out;

    cinfo_out.err = jpeg_std_error(&jerr_out);
    
    jpeg_create_compress(&cinfo_out);

    // Spécifier la destination du fichier JPEG de sortie
    jpeg_stdio_dest(&cinfo_out, outfile);

    // Configurer les paramètres de compression
    cinfo_out.image_width = width;
    cinfo_out.image_height = height;
    cinfo_out.input_components = num_channels;
    cinfo_out.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo_out);
    jpeg_set_quality(&cinfo_out, 75, TRUE); 

    // Commencer la compression
    jpeg_start_compress(&cinfo_out, TRUE);

    // Boucle pour écrire chaque ligne de l'image dans le fichier de sortie
    while (cinfo_out.next_scanline < cinfo_out.image_height) {
        ROW_POINTERS_OUTPUT = &image_data[cinfo_out.next_scanline * width * num_channels];
        jpeg_write_scanlines(&cinfo_out, &ROW_POINTERS_OUTPUT , 1);
    }

    // Terminer la compression
    jpeg_finish_compress(&cinfo_out);

    // Fermer le fichier de sortie
    fclose(outfile);

    // Libérer la mémoire
    free(image_data);

    // Libérer les structures de libjpeg
    jpeg_destroy_compress(&cinfo_out);
    jpeg_destroy_decompress(&cinfo);

    return EXIT_SUCCESS;
}