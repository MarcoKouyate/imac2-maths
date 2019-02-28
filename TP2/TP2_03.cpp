#include <iostream>
#include <Eigen/Dense>
#include <ctime>

float dotProduct(const Eigen::VectorXf &v1, const Eigen::VectorXf &v2) {
	float sum = 0.0f;

	for(unsigned int i=0;i<v1.size();i++){
		sum+=v1[i]*v2[i];
	}
	return sum;
}

int main()
{
	const unsigned int dimension = 5;
	Eigen::VectorXf v1 = Eigen::VectorXf::Random(dimension);
	Eigen::VectorXf v2 = Eigen::VectorXf::Random(dimension);
 	
	std::cout << "Le produit scalaire par fonction donne " << dotProduct(v1, v2) << std::endl;
	std::cout << "Le produit scalaire par Eigen donne " << v1.dot(v2) << std::endl;


  return 0;
}



// g++ -Wall -I /usr/include/eigen3/  eigenSample.cpp -o eigenSample-build
