#include"Matrix.h"

//=============== Allocate and Initialize a matrix ===============//
Matrix create_matrice(int nmb_col , int nmb_lig , char* name){

    Matrix m;

    m.name = name;

    float** matrix;
    float* vector;
    
    matrix = malloc(nmb_col * sizeof(float*));
	
	if(matrix == NULL){
		exit(1);
	}
	
	for(int i = 0 ; i < nmb_col ; i++){
	
		vector = malloc(nmb_lig * sizeof(float));
		
		if(vector == NULL){
			exit(1);
		}
		
		for(int j = 0 ; j < nmb_lig ; j++){
			vector[j] = 0;
		}
		
		matrix[i] = vector;
	}

    m.tab = matrix;

    m.nmb_col = nmb_col;
    m.nmb_lig = nmb_lig;

    return m;
}

//=============== Fill the matrix with the inputs values ===============//
void fill_matrice(Matrix m){
    
    printf("Remplir la matrice %s : \n", m.name);

    // j := columns 
    // i := rows
    for (int i = 0 ; i < m.nmb_lig ; i++){
        for (int j = 0 ; j < m.nmb_col ; j++){
            float m_ij = 0;

            printf("Saisir la valeur du coefficiant %d,%d (colonne,ligne) : " , j , i);
            scanf("%f" , &m_ij);
            
            m.tab[j][i] = m_ij;
        }
    }
}

//=============== Display a matrix ===============//
void print_matrice(Matrix m){

    for (int i = 0 ; i < m.nmb_lig ; i++){
        for (int j = 0 ; j < m.nmb_col ; j++){
            printf("%f " , m.tab[j][i]);
        }
        printf("\n");
    } 
    printf("\n");
}

//=============== Get the identity matrix of a certain dimension ===============//
Matrix get_identity(int dim){
   
    Matrix In = create_matrice(dim , dim , "");

    for (int i = 0 ; i < In.nmb_lig ; i++){
        for (int j = 0 ; j < In.nmb_col ; j++){
            if (i == j){
                In.tab[j][i] = 1;
            }
        }
    } 
    return In; 
}

//=============== Get a matix full of zero ===============//
Matrix null_matrix(int col , int row){

    Matrix null_matrix = create_matrice(col , row , "");

    for (int i = 0 ; i < null_matrix.nmb_lig ; i++){
        for (int j = 0 ; j < null_matrix.nmb_col ; j++){

            null_matrix.tab[j][i] = 0;
        }
    }
    return null_matrix;
}

//=============== Check if a matrix is null, if it is full of zero ===============//
bool is_null(Matrix m){

    for (int i = 0 ; i < m.nmb_lig ; i++){
        for (int j = 0 ; j < m.nmb_col ; j++){
            if (m.tab[j][i] != 0){
                return false;   
            }
        }
    } 
    return true;
}

//=============== Check if a matrix is a square matrix ===============//
bool is_square_matrix(Matrix m){
    if (m.nmb_lig == m.nmb_col){
        return true;
    }
    else{
        return false;
    }
}

//=============== Compute the trace of a square matrix ===============//
float trace(Matrix m){

    if (is_square_matrix(m)){
    
        float trace;

        for (int i = 0 ; i < m.nmb_lig ; i++){
            trace += m.tab[i][i];
        }
        
        return trace;
    }
    else{
        return NAN;
    } 
}

//=============== Compute the sum of two matrix ===============//
Matrix add(Matrix m1 , Matrix m2){
    
    Matrix m;

    if(m1.nmb_col != m2.nmb_col || m1.nmb_lig != m2.nmb_lig){
        printf("Les deux matrices doivent avoir les memes dimensions \n");
        exit(1);
    }
    else{
        
        m = create_matrice(m1.nmb_col , m1.nmb_lig , NULL);

        for (int i = 0 ; i < m1.nmb_lig ; i++){
            for (int j = 0 ; j < m1.nmb_col ; j++){
                m.tab[j][i] = m1.tab[j][i] + m2.tab[j][i] ;
            }
        }
    }
    return m; 
}

//=============== Compute the product of two matrice : m1 * m2 != m2 * m1 ===============//
Matrix mult(Matrix m1 , Matrix m2){

    Matrix m3;

    if(m1.nmb_col != m2.nmb_lig){
        printf("Le nombre de colonne de la premiere matrice doit etre egal aux nombre de lignes de la seconde matrice \n");
        exit(1);
    }
    else{

        m3 = create_matrice(m2.nmb_col , m1.nmb_lig , NULL);

        for (int i = 0 ; i < m1.nmb_lig ; i++){
            for (int j = 0 ; j < m2.nmb_col ; j++){
                float c_ij = 0;
                for (int k = 0 ; k < m1.nmb_col ; k++){
                    c_ij += m1.tab[k][i] * m2.tab[j][k];
                }
                m3.tab[j][i] = c_ij;
            }
        }
    }
    return m3;
}

//=============== Compute the product between a scaler and a matrix ===============//
Matrix mult_by_scalar(Matrix m1 , float r){

    Matrix m_ = create_matrice(m1.nmb_col , m1.nmb_lig , NULL);

    for (int i = 0 ; i < m_.nmb_lig ; i++){
        for (int j = 0 ; j < m_.nmb_col ; j++){
            m_.tab[j][i] = r * m1.tab[j][i];
        }
    }
    return m_;
}

//=============== Get the vectors of the standard basis ===============//
Matrix get_standard_basis_vector(int index , int dim){
    
    Matrix e_i = create_matrice(1 , dim , "");

    for (int i = 0 ; i < dim ; i++){
        if (i == index-1){
            e_i.tab[0][i] = 1;
        }
        else{
            e_i.tab[0][i] = 0;
        }
    }
    return e_i;
}

//=============== Compute the euclidian norm of a vector ===============//
float euclidian_norm(Matrix v){
    if(v.nmb_col == 1){

        float sum = 0;
        float v_norm;

        for (int i = 0 ; i < v.nmb_lig ; i++){
            sum += pow(fabs(v.tab[0][i]) , 2); 
        }
    
        v_norm = sqrt(sum);

        return v_norm;
    }
}

//=============== Compute the determinant of a square matrix ===============//
float det(Matrix m){

    float determinant = 0;

    if(!is_square_matrix(m)){
        printf("Le determinant d'une matrice non carré n'existe pas !\n");
        exit(1);
    }
    else if(m.nmb_col == 2 || m.nmb_lig == 2){
        determinant = m.tab[0][0] * m.tab[1][1] - m.tab[0][1] * m.tab[1][0]; 
        return determinant; 
    }
    else{

        for(int i = 0 ; i < m.nmb_col ; i++){

            Matrix m_ = create_matrice(m.nmb_col-1 , m.nmb_col-1 , NULL);
            
            int x = 0;
            int y = 0;

            for (int j = 1 ; j < m.nmb_lig ; j++){
                for (int k = 0 ; k < m.nmb_col ; k++){
                    if(i != k){
                        m_.tab[y][x] = m.tab[k][j];
                        y++;
                    }
                }
                y = 0;
                x++;
            }
            determinant += (pow((-1) , (i)) * m.tab[i][0]) * det(m_);
        }
        return determinant;
    }
}

//=============== Compute the commatrice of a square matrix ===============//
Matrix com(Matrix m){
    
    Matrix com_m = create_matrice(m.nmb_col , m.nmb_lig , NULL);

    if(!is_square_matrix(m)){
        printf("La commatrice d'une matrice non carré n'existe pas !\n");
        exit(1);
    }
    else if(m.nmb_col == 2 && m.nmb_lig == 2){
        for(int i = 0 ; i < m.nmb_col ; i++){
            for(int j = 0 ; j < m.nmb_col ; j++){
                com_m.tab[j][i] = m.tab[(m.nmb_col-1)-j][(m.nmb_col-1)-i];
            }
        }
        return com_m;
    }
    else{
        for(int i = 0 ; i < m.nmb_col ; i++){
            for(int p = 0 ; p < m.nmb_col ; p++){

                Matrix m_ = create_matrice(m.nmb_col-1 , m.nmb_lig-1 , NULL);
                
                int x = 0;
                int y = 0;
                
                for (int j = 0 ; j < m.nmb_col ; j++){
                    for (int k = 0 ; k < m.nmb_col ; k++){
                        if(k != p && j != i){

                            if(x == m_.nmb_col-1 && y == m_.nmb_col-1){
                                m_.tab[y][x] = m.tab[k][j];
                                x = 0;
                                y = 0;
                            }
                            else if(x == 0 && y == 0){
                                m_.tab[y][x] = m.tab[k][j]; 
                                y++;
                            }
                            else if(x < m_.nmb_col-1  && y == m_.nmb_col-1){
                                m_.tab[y][x] = m.tab[k][j]; 
                                x++;
                                y = 0;
                            }
                            else if((x == m_.nmb_col-1 && y < m_.nmb_col-1)){
                                m_.tab[y][x] = m.tab[k][j]; 
                                y++;
                            }
                        }
                    }
                }
                com_m.tab[p][i] = pow((-1) , (i+p)) * det(m_);
            }
        }
    }
    return(com_m);
}

//=============== Compute the transpose of a square matrix ===============//
Matrix transpose(Matrix m){

    Matrix m_ = create_matrice(m.nmb_lig , m.nmb_col , NULL);

    for (int i = 0 ; i < m.nmb_col ; i++){
        for (int j = 0 ; j < m.nmb_lig ; j++){
            m_.tab[j][i] = m.tab[i][j];
        }
    }
    return m_;
}

//=============== Compute the inverse of a square matrix ===============//
Matrix inverse(Matrix m , int* inversible){

    if(!is_square_matrix(m)){
        printf("La matrice n'est pas inversible \n\n");
        exit(1);
    }

    float det_m = (det(m));

    if(det_m != 0){
        float r = (1/(det_m));
        *inversible = true;
        Matrix m_ = mult_by_scalar(transpose(com(m)) , r);
        return m_;
    }
    else if(det_m == 0){
        *inversible = false;
        printf("La matrice n'est pas inversible \n\n");

    }
}

//=============== Get the columns vectors of a matrix ===============//
Matrix* get_column_vectors_from(Matrix m){

    Matrix* column_vectors = malloc(m.nmb_col * sizeof(Matrix));
    
    for (int i = 0 ; i < m.nmb_col ; i++){

        Matrix v_i = create_matrice(1 , m.nmb_lig , "");

        for (int j = 0 ; j < m.nmb_lig ; j++){
            v_i.tab[0][j] = m.tab[i][j];
        }
        column_vectors[i] = v_i;
    }
    return column_vectors;
}

//=============== Get the rows vectors of a matrix ===============//
Matrix* get_row_vectors_from(Matrix m){

    Matrix* row_vectors = malloc(m.nmb_lig * sizeof(Matrix));
    
    for (int i = 0 ; i < m.nmb_lig ; i++){

        Matrix v_i = create_matrice(m.nmb_col , 1 , "");

        for (int j = 0 ; j < m.nmb_col ; j++){
            v_i.tab[j][0] = m.tab[j][i];
        }
        row_vectors[i] = v_i;
    }
    return row_vectors;
}

//=============== Check if a matrix is traingular ===============//
bool is_upper_triangular(Matrix m , float* e){
    
    bool upper;

    if (is_square_matrix(m)){
    
        if (e == NULL){

            for (int i = 0 ; i < m.nmb_lig ; i++){
                for (int j = 0 ; j < m.nmb_col ; j++){
                    
                    if (i > j && m.tab[j][i] != 0){
                        upper = false;   
                        return upper;
                    }  
                }
            }
            upper = true; 
            return upper;
        }
        else{
            for (int i = 0 ; i < m.nmb_lig ; i++){
                for (int j = 0 ; j < m.nmb_col ; j++){
                    
                    if (i > j &&  (m.tab[j][i] > *e || m.tab[j][i] < -*e )){
                        upper = false;   
                        return upper;
                    }  
                }
            }
            upper = true; 
            return upper;  
        } 
    }
    else{
        printf("Une matrice non carré ne peut pas etre triangulaire\n");
        exit(1);
    }
    
}
bool is_lower_triangular(Matrix m , float* e){
    
    bool lower;

    if (is_square_matrix(m)){

        if (e == NULL){
        
            for (int i = 0 ; i < m.nmb_lig ; i++){
                for (int j = 0 ; j < m.nmb_col ; j++){
                    
                    if (i < j && m.tab[j][i] != 0){
                        lower = false;   
                        return lower;
                    }  
                }
            }
            lower = true; 
            return lower;
        }
        else{
            for (int i = 0 ; i < m.nmb_lig ; i++){
                for (int j = 0 ; j < m.nmb_col ; j++){
                    
                    if (i < j &&  (m.tab[j][i] > *e || m.tab[j][i] < -*e )){
                        lower = false;   
                        return lower;
                    }  
                }
            }
            lower = true; 
            return lower;  
        } 
    }
    else{
        printf("Une matrice non carré ne peut pas etre triangulaire\n");
        exit(1);
    }
}

//=============== Check if a matrix is diagonal ===============//
bool is_diagonal(Matrix m){
    
    bool diagonal;

    if (is_square_matrix(m)){
        for (int i = 0 ; i < m.nmb_lig ; i++){
            for (int j = 0 ; j < m.nmb_col ; j++){
                
                if ((i < j && m.tab[j][i] != 0) || (i > j && m.tab[j][i] != 0)){
                    diagonal = false;   
                    return diagonal;
                }  
            }
        }
        diagonal = true; 
        return diagonal;
    }
    else{
        printf("Une matrice non carré ne peut pas etre diagonale\n");
        exit(1);
    }
    
}

//=============== Check if a matrix is symetrical ===============//
bool is_symetrical(Matrix m){

    bool symetrical;

    if (is_square_matrix(m)){
        
        for (int i = 0 ; i < m.nmb_lig ; i++){
            for (int j = 0 ; j < m.nmb_col ; j++){
                
                if (m.tab[j][i] == m.tab[i][j]){
                    symetrical = false;   
                    return symetrical;
                }  
            }
        }

        symetrical = true;
        return symetrical;
    }
    else{
        printf("Une matrice non carré ne peut pas etre symetrique\n");
        exit(1);
    }
}

//=============== Get is diagonal element of a square matrix ===============//
float* get_diagonal(Matrix m){

    if (is_square_matrix(m)){
    
        float* diagonal_element = malloc(m.nmb_lig * sizeof(float));

        for (int i = 0 ; i < m.nmb_lig ; i++){
            diagonal_element[i] = m.tab[i][i];
        }
        return diagonal_element;
    }
    else{
        printf("Une matrice non carré ne ppossede pas de diagonal\n");
        return NULL;
    }
}

//=============== Compute the minor matrix from a specific index of the matrix ===============//
Matrix minor_matrix(Matrix m , int col_index , int row_index){
    
    if (col_index < 0 || col_index > m.nmb_col ||
        row_index < 0 || row_index > m.nmb_lig){
        printf("Incorrect index\n");
        exit(1);
    }
    else{

        Matrix minor = create_matrice(m.nmb_col-1 , m.nmb_lig-1 , "");

        int i_ = 0;
        int j_ = 0;

        for (int i = 0 ; i < m.nmb_lig ; i++){
            for (int j = 0 ; j < m.nmb_col ; j++){
                
                if (i != row_index && j != col_index){
                    minor.tab[j_][i_] = m.tab[j][i];
                    if (j_ == minor.nmb_col-1){
                        i_++;
                        j_ = 0;
                    }
                    else{
                        j_++;
                    }
                }  
            }
        }
        return minor;
    }
}

//=============== Different function for resolve linear system ===============//
int search_pivot(Matrix v){

    if (v.nmb_col == 1){

        float max = - __FLT_MAX__;
        int row_index = 0;

        for (int i = 0 ; i < v.nmb_lig ; i++){
            if (fabs(v.tab[0][i]) > max){
                max = fabs(v.tab[0][i]);
                row_index = i;
            }
        }
        return row_index;
    }
    else{
        printf("Un pivot se recherche dans une matrice colonne \n");
        exit(1);
    }
}
Matrix swap_rows(Matrix m , int old_row_index , int new_row_index){

    if (old_row_index < 0 || old_row_index > m.nmb_lig ||
        new_row_index < 0 || new_row_index > m.nmb_lig){
        printf("Incorrect index\n");
        exit(1);
    }
    else{
        Matrix current_row = create_matrice(m.nmb_col , 1 , "");
        Matrix temp_row = create_matrice(m.nmb_col , 1 , "");

        for (int i = 0 ; i < m.nmb_col ; i++){
            current_row.tab[i][0] = m.tab[i][old_row_index];
            temp_row.tab[i][0] = m.tab[i][new_row_index];
        }

        for (int j = 0 ; j < m.nmb_col ; j++){
            m.tab[j][new_row_index] = current_row.tab[j][0];
        }

        for (int k = 0 ; k < m.nmb_col ; k++){
            m.tab[k][old_row_index] = temp_row.tab[k][0];
        }

        return m;    
    }
}
Matrix mult_row_by_scalar(Matrix m , int row_index , float scalar){

    if (row_index < 0 || row_index > m.nmb_lig || scalar == 0){
        printf("Incorrect index\n");
        exit(1);
    }
    else{

        for (int i = 0 ; i < m.nmb_col ; i++){
            m.tab[i][row_index] *= scalar; 
        }
    
        return m;
    }
}
Matrix add_linear_combination(Matrix m , int receiver_row_index , int adding_row_index , float scalar){

    if (receiver_row_index < 0 || receiver_row_index > m.nmb_lig || 
        adding_row_index < 0 || receiver_row_index > m.nmb_lig){
        printf("Incorrect index\n");
        exit(1);
    }
    else{
    
        for (int i = 0 ; i < m.nmb_col ; i++){
            m.tab[i][receiver_row_index] += (scalar * m.tab[i][adding_row_index]) ; 
        }
        return m;
    }   
}
Matrix gauss_jordan(Matrix m){

    int last_pivot_index = 0;
    int current_pivot_index = 0;

    float pivot;

    Matrix* column_vectors = get_column_vectors_from(m);
    Matrix m_ = m;
    Matrix before_minor = m;
    Matrix v_i;

    // printf("m_ = \n");
    // print_matrice(m_);
    // printf("\n");

    for (int j = 0 ; j < m.nmb_col-1 ; j++){
        
        // printf("//===== %d ITERATIONS =====//\n\n" , j);
        
        before_minor = m_;
        v_i = column_vectors[0],

        current_pivot_index = search_pivot(v_i);
        pivot = v_i.tab[0][current_pivot_index];
        
        current_pivot_index += j;

        // printf("k = %d\n", current_pivot_index);
        // printf("r = %d\n", last_pivot_index);
        // printf("j = %d\n", j);
        // printf("Pivot = %f\n", pivot);

        if (pivot != 0){

            float ratio = 1 / pivot;
            m_ = mult_row_by_scalar(m_ , current_pivot_index , ratio);

            if (current_pivot_index != last_pivot_index){
                m_ = swap_rows(m_ , current_pivot_index , last_pivot_index);
            }

            for (int i = 0 ; i < m_.nmb_lig ; i++){
                if (i != last_pivot_index){
                    m_ = add_linear_combination(m_ , i , last_pivot_index , -m_.tab[j][i]);   
                }
            }

            last_pivot_index += 1;
        }
        
        // printf("m_ = \n");
        // print_matrice(m_);

        if (j != m.nmb_lig){
            for (int i = 0 ; i <= j ; i++){
                before_minor = minor_matrix(before_minor , 0 , 0);
            }
        }

        // printf("before_minor = \n");
        // print_matrice(before_minor);

        column_vectors = NULL;
        column_vectors = get_column_vectors_from(before_minor);
    }

    // printf("\n\nFIN : m_ = \n");
    // print_matrice(m_);

    return m_;
}
Matrix resolve_linear_system(Matrix A , Matrix B){

    if (B.nmb_col == 1 && B.nmb_lig == A.nmb_lig){
    
        Matrix X = create_matrice(1 , A.nmb_lig , "");
        Matrix AB = create_matrice(A.nmb_col+1 , A.nmb_lig , "");
        Matrix resolve;

        for (int i = 0 ; i < A.nmb_lig ; i++){
            for (int j = 0 ; j < A.nmb_col ; j++){
                AB.tab[j][i] = A.tab[j][i];
            }
        }
        for (int k = 0 ; k < B.nmb_lig ; k++){
            AB.tab[A.nmb_col][k] = B.tab[0][k]; 
        }   
        
        // printf("AB = \n");
        // print_matrice(AB);
        // printf("\n");

        resolve = gauss_jordan(AB);
        // printf("resolve = \n");
        // print_matrice(resolve);
        // printf("\n");

        X = get_column_vectors_from(resolve)[A.nmb_col];

        return X;
    }
    else{
        printf("Le systeme n'est pas correct\n");
        exit(1);
    }
}

//=============== Make an Householder matrix with a default matrix ===============//
Matrix make_householder_matrix(Matrix m , int diff){

    if (diff > 0){
    
        Matrix householder_matrix = null_matrix(m.nmb_col + diff , m.nmb_lig + diff);
        for (int i = 0 ; i < diff ; i++){
            householder_matrix.tab[i][i] = 1;
        }

        for (int i = diff ; i < householder_matrix.nmb_lig ; i++){
            for (int j = diff ; j < householder_matrix.nmb_col ; j++){
                householder_matrix.tab[j][i] = m.tab[j-diff][i-diff];
            }
        }

        return householder_matrix;
    }
    else{
        return m;
    }
} 

//=============== Compute the QR decomposition of a matrix  ===============//
void QR_decomposition(Matrix m , Matrix* Q , Matrix* R){

    Matrix* column_vectors;
    
    Matrix R_;
    Matrix Q_ = get_identity(m.nmb_lig);
    Matrix Q_i;
    Matrix m_;
    Matrix e1;
    Matrix x;
    Matrix u;
    Matrix v;
    Matrix product;
 
    float a;

    m_ = m;

    for (int i = 0 ; i < m.nmb_lig-1 ; i++){

        Matrix In = get_identity(m_.nmb_lig);

        column_vectors = get_column_vectors_from(m_);
        
        x = column_vectors[0];
        e1 = get_standard_basis_vector(1 , m_.nmb_lig);
        a = euclidian_norm(x);
        u = add(x , mult_by_scalar(e1 , -a));

        if(!is_null(u)){
            
            float r = (float)(1/euclidian_norm(u));
            v = mult_by_scalar(u , r);

            product = mult(v , transpose(v));
            Q_i = add(In , mult_by_scalar(product , -2)); 

            int diff = m.nmb_lig - Q_i.nmb_lig;

            Matrix new_Q_i = make_householder_matrix(Q_i , diff);

            Q_ = mult(Q_ , new_Q_i); 
            R_ = mult(transpose(Q_) , m);

            m_ = minor_matrix(R_ , 0 , 0);
            
        }
        else{

            Q_i = In; 

            int diff = m.nmb_lig - Q_i.nmb_lig;

            Matrix new_Q_i = make_householder_matrix(Q_i , diff);

            Q_ = mult(Q_ , new_Q_i); 
            R_ = mult(transpose(Q_) , m);

            m_ = minor_matrix(R_ , 0 , 0);
        }
    }

    *R = R_;
    *Q = Q_;
}

//=============== Compute the eigen values of a matrix ===============//
float* eigenvalues(Matrix m){

    if (is_square_matrix(m)){

        int i = 0;

        float* eigen_values = malloc(m.nmb_lig * sizeof(float)); 

        float e = 0.05;

        Matrix m0 = m;
        Matrix m_i = m0;
        Matrix Q_i;
        Matrix R_i;

        do{

            QR_decomposition(m_i , &Q_i , &R_i);

            m_i = mult(R_i , Q_i);
            i++;

            // printf("m_i = \n");
            // print_matrice(m_i);

        } while (!is_upper_triangular(m_i , &e));

        eigen_values = get_diagonal(m_i);

        return eigen_values;  
    }
    else{
        printf("Une matrice non carré ne possede pas de valeurs propres\n");
        return NULL;
    }
}

//=============== Compute the eigen vectors of a matrix ===============//
Matrix* eigenvectors(Matrix m){

    if (is_square_matrix(m)){
        
        int k = 0;

        float* eigen_values = eigenvalues(m);
        float lambda_i; 
        float previous_lambda = 0;
        float e = 0.1;
        float ratio;

        Matrix* eigenvectors = malloc(m.nmb_lig * sizeof(Matrix));
        Matrix x0 = create_matrice(1 , m.nmb_lig , "");
        Matrix x = x0;
        
        Matrix A;
        Matrix B;

        Matrix product;

        for (int i = 0; i < m.nmb_lig; i++){
            x0.tab[0][i] = rand()%10;
        }
        // printf("x0 = \n");
        // print_matrice(x0);

        // printf("lambda_i = %f \n\n", lambda_i);

        for (int i = 0 ; i < m.nmb_lig ; i++){
            
            lambda_i = eigen_values[i];
            x = x0;
            previous_lambda = 0;

            // printf("lambda_i = %f\n", lambda_i); 

            while ( k < 50 && fabs(lambda_i - previous_lambda) > e){

                previous_lambda = lambda_i;
                
                A = add(m  , mult_by_scalar(get_identity(m.nmb_lig) , -lambda_i));

                ratio = (float)(1/euclidian_norm(x));
                B = mult_by_scalar(x , ratio);

                x = resolve_linear_system(A , B);

                // printf("X = \n");
                // print_matrice(x);

                // printf("B = \n");
                // print_matrice(B);

                product = mult(transpose(x) , B);
                // printf("product = \n");
                // print_matrice(product);

                lambda_i = (1/product.tab[0][0]);
                // printf("lambda_i = %f\n", lambda_i);

                k++;
            }
            k = 0; 
            eigenvectors[i] = x; 
            // printf("lambda_i = %f\n\n", lambda_i); 
        }
        return eigenvectors;
    }
    else{
        printf("Une matrice non carré ne possede pas d'élément propres !\n");
        exit(1);
    }
}

