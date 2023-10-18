#include <iostream>

class Complex {

    private:
        float real;
        float img;

    public:
        void set() {
            this->real = 0.f;
            this->img = 0.f;
        }

        void set(float real, float img) {
            this->real = real;
            this->img = img;
        }

        void print() {

            if (this->img < 0) {
                if (this->img == 1) {
                    std::cout << this->real;
                    std::cout << " - ";
                    std::cout << "i";
                    return;
                }

                std::cout << this->real;
                std::cout << " - ";
                std::cout << -this->img;
                std::cout << "i";
                return;
            }
            
            if (this->img == 1) {
                std::cout << this->real;
                std::cout << " + ";
                std::cout << "i";
                return;
            }
            std::cout << this->real;
            std::cout << " + ";
            std::cout << this->img;
            std::cout << "i";
        }

        float mod() {
            float mod_2 = this->real * this->real + this->img * this->img;
            return sqrt(mod_2);
        }

        Complex add(Complex z) {

            Complex z_sum;

            z_sum.real = this->real + z.real;
            z_sum.img = this->img + z.img;
               
            return z_sum;
        }

        Complex sub(Complex z) {

            Complex z_sub;

            z_sub.real = this->real - z.real;
            z_sub.img = this->img - z.img;

            return z_sub;
        }

        Complex mult(float k) {

            Complex z_product;

            z_product.real = this->real * k;
            z_product.img = this->img * k;

            return z_product;
        }

        Complex mult(Complex z) {

            Complex z_product;

            z_product.real = (this->real * z.real) - (this->img * z.img);
            z_product.img = (this->real * z.img) + (this->img * z.real);

            return z_product;
        }

        Complex div(float k) {

            Complex z_div;

            float ratio = 1.f / k;

            z_div = this->mult(ratio);

            return z_div;
        }

        Complex div(Complex z) {

            Complex z_div;
            Complex product;

            float ratio = 0.f;
            
            product = this->mult(z.conjugate());
            ratio = 1.0 / (z.mod() * z.mod());

            z_div = product.mult(ratio);

            return z_div;
        }

        Complex conjugate() {

            Complex z_conjugate;

            z_conjugate.real = this->real;
            z_conjugate.img = -this->img;

            return z_conjugate;
        }

        Complex opposite() {

            Complex z_opposite;

            z_opposite.real = -this->real;
            z_opposite.img = -this->img;

            return z_opposite;
        }
};

int main(){

    Complex z1, z2, z3;

    float k = 2.f;

    z1.set(3 , 2);
    z1.print();

    std::cout << "\n";

    z2.set(1, 5);
    z2.print();

    std::cout << "\n";

    z3 = z1.div(z2);
    z3.print();

    return 0;
}