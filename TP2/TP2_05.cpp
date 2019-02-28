#include <iostream>
#include <Eigen/Dense>
#include <ctime>
#include <cassert>


Eigen::MatrixXf matrixProduct(const Eigen::MatrixXf &m1, const Eigen::MatrixXf &m2) {
	assert(m1.cols() == m2.rows() && "error");
	Eigen::MatrixXf result = Eigen::MatrixXf::Zero(m1.rows(),m2.cols());
	for (unsigned int i = 0 ; i< result.rows();i++){
		for(unsigned int j= 0 ; j <result.cols();j++){
			for(unsigned int k=0; k<m1.cols();k++){
				result(i,j)+= m1(i,k)*m2(k,j); 
			}
		}
	}
	return result;
}

Eigen::MatrixXf strassenProduct(const Eigen::MatrixXf &m1, const Eigen::MatrixXf &m2) { 

	if (m1.rows() < 128 ){
		return m1 * m2;
	}

	const unsigned int rows = m1.rows()/2;
	const unsigned int cols = m1.cols()/2;

	Eigen::MatrixXf mA = m1.topLeftCorner(rows, cols);
	Eigen::MatrixXf mB = m1.topRightCorner(rows, cols);
	Eigen::MatrixXf mC = m1.bottomLeftCorner(rows,cols);
	Eigen::MatrixXf mD = m1.bottomRightCorner(rows, cols);
	Eigen::MatrixXf mE = m2.topLeftCorner(rows, cols);
	Eigen::MatrixXf mF = m2.topRightCorner(rows, cols);
	Eigen::MatrixXf mG = m2.bottomLeftCorner(rows,cols);
	Eigen::MatrixXf mH = m2.bottomRightCorner(rows, cols);

	Eigen::MatrixXf P1 = strassenProduct(     mA ,(mF-mH) );
	Eigen::MatrixXf P2 = strassenProduct( (mA+mB), mH     );
	Eigen::MatrixXf P3 = strassenProduct( (mC+mD), mE     );
	Eigen::MatrixXf P4 = strassenProduct(      mD,(mG-mE) );
	Eigen::MatrixXf P5 = strassenProduct( (mA+mD),(mE+mH) );
	Eigen::MatrixXf P6 = strassenProduct( (mB-mD),(mG+mH) );
	Eigen::MatrixXf P7 = strassenProduct( (mA-mC),(mE+mF) );

	Eigen::MatrixXf matrixResult (m1.rows(),m1.cols());
	matrixResult.topLeftCorner(rows,cols) = P5 + P4 - P2 + P6;
	matrixResult.topRightCorner(rows,cols) = P1 + P2;
	matrixResult.bottomLeftCorner(rows,cols)= P3 + P4;
	matrixResult.bottomLeftCorner(rows,cols) = P1 + P5 - P3 - P7;



	return matrixResult;
}

int main()
{
	const unsigned int dimension = 2048;
	Eigen::MatrixXf m1 = Eigen::MatrixXf::Random(dimension,dimension);
  	Eigen::MatrixXf m2 = Eigen::MatrixXf::Random(dimension,dimension);	
  	Eigen::MatrixXf result1 = Eigen::MatrixXf::Zero(dimension,dimension);
  	Eigen::MatrixXf result2 = Eigen::MatrixXf::Zero(dimension,dimension);
  	Eigen::MatrixXf result3 = Eigen::MatrixXf::Zero(dimension,dimension);


	clock_t begin = clock();
	//result1 = matrixProduct(m1, m2);
	clock_t end = clock();
	double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	  

	std::cout << "temps calcul du produit matriciel par boucle for: " <<tempsCalc <<"s " << std::endl;

	//std::cout << "Le produit matriciel par fonction donne : \n" << result1 << std::endl;

	begin = clock();
	result2 = m1 * m2;
	end = clock();
	tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	  

	std::cout << "temps calcul du produit matriciel par Eigen " <<tempsCalc <<"s " << std::endl;
	//std::cout << "Le produit matriciel par Eigen donne : \n" << result2 << std::endl;

	begin = clock();
	result3 = strassenProduct(m1,m2);
	end = clock();
	tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
	  

	std::cout << "temps calcul du produit matriciel par Strassen " <<tempsCalc <<"s " << std::endl;
	//std::cout << "Le produit matriciel par Eigen donne : \n" << result3 << std::endl;



  	return 0;
}



// g++ -Wall -I /usr/include/eigen3/  eigenSample.cpp -o eigenSample-build
