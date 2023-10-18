#include"Matrix.h"

int main(){
    Matrix m1 = create_matrice(3 , 3 , "M1");
    Matrix m2 = create_matrice(1 , 4 , "M2");
    Matrix m3 = create_matrice(2 , 2 , "M3");

    Matrix Q;
    Matrix R;

    // m1.tab[0][0] = 0.f;
    // m1.tab[1][0] = -1.f;
    // m1.tab[2][0] = 0.f;
    // m1.tab[0][1] = -1.f;
    // m1.tab[1][1] = 0.f;
    // m1.tab[2][1] = 1.f;
    // m1.tab[0][2] = 1.f;
    // m1.tab[1][2] = 1.f;
    // m1.tab[2][2] = 1.f;

    m1.tab[0][0] = 1.f;
    m1.tab[1][0] = -1.f;
    m1.tab[2][0] = 2.f;
    m1.tab[0][1] = 3.f;
    m1.tab[1][1] = 2.f;
    m1.tab[2][1] = 1.f;
    m1.tab[0][2] = 2.f;
    m1.tab[1][2] = -3.f;
    m1.tab[2][2] = -2.f;

    m2.tab[0][0] = 3;
    m2.tab[0][1] = -6;
    m2.tab[0][2] = 0;
    m2.tab[0][3] = 1;

    m3.tab[0][0] = 0;
    m3.tab[1][0] = 1;
    m3.tab[0][1] = 1;
    m3.tab[1][1] = 0;

    // printf("\nM3 = \n");
    // print_matrice(m3);
    // printf("\n");

    // Matrix m4 = resolve_linear_system(m3 , m2);

    printf("\n\n");

    // Matrix m4 = resolve_linear_system(m3 , m2);
    // printf("\nM4 = \n");
    // print_matrice(m4);
    // printf("\n");

    // int i = 0;

    // float e = 0.004;

    // Matrix m0 = m1;
    // Matrix m_i = m0;
    // Matrix Q_i;
    // Matrix R_i;

    // do{

    //     QR_decomposition(m_i , &Q_i , &R_i);

    //     m_i = mult(R_i , Q_i);
    //     i++;
    
    // } while (!is_upper_triangular(m_i , &e));

    // QR_decomposition(m1 , &Q , &R);

    // printf("M1 = Q * R avec \n");

    // Matrix e2 = get_standard_basis_vector(2 , 3);

    // printf("Q = \n");
    // print_matrice(Q_i);

    // printf("R = \n");
    // print_matrice(R_i);

    // printf("v1 = \n");
    // print_matrice(mult(Q_i , e2));
    
    // printf("Vérification : Q * R = \n");
    // print_matrice(mult(Q , R));
    
    printf("M3 = \n");
    print_matrice(m3);
    printf("\n");

    Matrix* eigen_vetors = eigenvectors(m3);
    float* eigen_values = eigenvalues(m3);

    for (int i = 0 ; i < m3.nmb_lig ; i++){
        printf("Valeur propre : %f \n", eigen_values[i]);
        printf("Vecteur propre : \n");
        print_matrice(eigen_vetors[i]);
        printf("\n");
    }
    
    return(0);
}