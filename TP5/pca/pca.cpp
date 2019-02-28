#include <iostream>
#include <Eigen/Eigenvalues>

#include "ioEigen.hpp"

using namespace Eigen;


void hints(void){

  MatrixXd M;
  
  // compute the column wize mean of a data matrix
  VectorXd mean =  M.colwise().sum() / (double) M.rows(); 
  
  // some hints to center some data (with the exterior product)
  std::cout << VectorXd::Ones(M.rows())*mean.transpose() << std::endl;

  // compute some eigen vectors
  SelfAdjointEigenSolver<MatrixXd> eigensolver(M);
  std::cout << "\neigenvectors of M \n" << eigensolver.eigenvectors().rowwise().reverse() << std::endl;
  std::cout << "\neigenvalues of M : " << eigensolver.eigenvalues().colwise().reverse().transpose() << std::endl;
  
  // extract some rows or columns from a matrix
  std::cout << M.leftCols(3) << std::endl; 
  std::cout << M.topRows(3) << std::endl; 
	
}



int main(int argc, char **argv)
{
  if(argc != 2){
    std::cerr << "usage : " << argv[0] << " data.mat" << std::endl;
    exit(0);
  }
  
  // load the data
  MatrixXd A;
  MatrixXd centeredA;
  MatrixXd normalizedA;

  loadMatrix(A,argv[1]);
  std::cout << "A\n" << A << std::endl;

  // mean of the data
  VectorXd mean =  A.colwise().sum() / (double) A.rows(); //vecteur moyen

  // center the data
  centeredA = A - VectorXd::Ones(A.rows())*mean.transpose();
  std::cout << "centuredA\n" << centeredA << std::endl;

  // normalize the data
  MatrixXd scale = MatrixXd::Zero(A.cols(), A.cols());
  scale.diagonal() = centeredA.cwiseAbs().colwise().sum()/(double)centeredA.rows();

  scale = scale.inverse();
  normalizedA = centeredA * scale;

  std::cout << "normalizedA\n" << normalizedA << std::endl;

  // build the covariance matrix 
  MatrixXd cov = (normalizedA.transpose()*normalizedA)/(normalizedA.rows()-1);
  std::cout << "Matrice de covariance\n" << cov << std::endl;

  // compute the eigen vectors
  SelfAdjointEigenSolver<MatrixXd> eigensolver(cov);
  std::cout << "\neigenvectors of cov \n" << eigensolver.eigenvectors().rowwise().reverse() << std::endl;
  std::cout << "\neigenvalues of cov : " << eigensolver.eigenvalues().colwise().reverse().transpose() << std::endl;

  // keep only n dimensions
  int dimension = 3;

  MatrixXd T =eigensolver.eigenvectors().rowwise().reverse().leftCols(dimension);
  MatrixXd finalA = normalizedA * T;
  std::cout << "Matrice finale\n" << finalA << std::endl;

  //test
  VectorXd x (A.cols());
  x << 0,3,4,10,1;
  VectorXd xProj = (T.transpose()*scale*(x-mean)).transpose();
  VectorXd distance = (finalA-VectorXd::Ones(finalA.rows())*xProj.transpose()).rowwise().norm();
  std::cout << "Matrice distance\n" << distance << std::endl;


  
  // project the data
  // ...
  
  // project a new vector (remind to center and scale this vector)
  // ...

  return 0;
}
