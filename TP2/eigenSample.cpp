#include <iostream>
#include <Eigen/Dense>
#include <ctime>
int main()
{
	
  
  Eigen::VectorXd v1(5);
  v1 << 1, 2, 3, 4, 5;
  std::cout << "v1 : " << v1.transpose() << std::endl << std::endl;

  Eigen::Vector4f v2 = Eigen::Vector4f::Zero();
  std::cout << "v2 : " << v2.transpose() << std::endl << std::endl;

  v2 = Eigen::Vector4f::Ones();
  std::cout << "v2 : " << v2.transpose() << std::endl << std::endl;

  Eigen::Vector4f v3 = Eigen::Vector4f::Random();
  std::cout << "v3 : " << v3.transpose() << std::endl << std::endl;
  v3 = v3 + v2;
  std::cout << "v3 : " << v3.transpose() << std::endl << std::endl;

  Eigen::MatrixXd A = Eigen::MatrixXd::Random(3,4);	
  std::cout << "A :\n" << A << std::endl << std::endl;

  Eigen::Matrix4d B = Eigen::Matrix4d::Random(4,4);	
  std::cout << "B :\n" << B << std::endl << std::endl;

  Eigen::MatrixXd C(3,4);
  
  clock_t begin = clock();
  C=A*B;
  clock_t end = clock();
  double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  

  std::cout << "temps calcul du produit matriciel: " <<tempsCalc <<"s " << std::endl;
  std::cout << "A + 2*A :\n" << A + 2*A << std::endl << std::endl;
  std::cout << "A * B :\n" << A * B << std::endl << std::endl;

  return 0;
}



// g++ -Wall -I ~/eigen/  eigenSample.cpp 