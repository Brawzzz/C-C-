#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues> 
 
using Eigen::MatrixXd;
using Eigen::MatrixBase;

using namespace std;
using namespace Eigen;

int main(){

  MatrixXd m(3,3);
  m(0,0) = 12;
  m(1,0) = 6;
  m(2,0) = -4;
  m(0,1) = -51;
  m(1,1) = 167;
  m(2,1) = 24;
  m(0,2) = 4;
  m(1,2) = -68;
  m(2,2) = -41;

  std::cout << m << std::endl;

  EigenSolver<MatrixXd> eigen_solver(m);
  
  cout << "The eigen values of m are :" << endl << eigen_solver.eigenvalues() << endl;
  cout << "The eigen vectors of m are :" << endl << eigen_solver.eigenvectors() << endl;

}