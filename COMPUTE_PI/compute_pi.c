#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int is_in_circle(double rayon , double x , double y){

    int ok = 0;

    if(x*x + y*y <= rayon * rayon){
        ok = 1;
    }

    return ok;
}

int main(){

    int total_points = 200000;
    
    double rayon = 1;
    double points_in  = 0.0;
    double points_out  = 0.0;

    srand(time(NULL));
    
    for (int i = 0 ; i < total_points ; i++){
        double x = (((double)rand()/(double)(RAND_MAX)) * rayon)-rayon;
        double y = (((double)rand()/(double)(RAND_MAX)) * rayon)-rayon;

        if(is_in_circle(rayon , x , y) == 1){
            points_in += 1;
        }
        else{
            points_out += 1;
        }
    }

    double pi = ((double)points_in / (double)total_points)*4.0;
    printf("Approximation of pi : %lf",pi);

    return(0);
}