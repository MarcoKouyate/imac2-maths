#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cassert>
#include <ctime>

using namespace Eigen;
using namespace std;


MatrixXf matrixProduct(const MatrixXf &m1, const MatrixXf &m2)
	{
		assert(m1.cols() == m2.rows() && "error");
		MatrixXf mResult = MatrixXf::Zero(m1.rows(),m2.cols());
		for (unsigned int i=0; i<mResult.rows(); i++)
		{
			for (unsigned int j=0; j<mResult.cols(); j++)
			{
				for (unsigned int k=0; k<m1.cols(); k++)
				{
					mResult(i,j) += m1(i,k)*m2(k,j);
				}
			}
		}
		return mResult;
	}

int main(int argc, char const *argv[])
{
	const unsigned int dimension = 5;
	MatrixXf m1 = MatrixXf::Random(dimension,dimension);
	MatrixXf m2 = MatrixXf::Random(dimension,dimension);
	clock_t begin = clock();
  	cout << "le produit matriciel est : " << endl ;
	cout << matrixProduct(m1,m2) << endl;
  	clock_t end = clock();
  	double tempsCalc = double(end - begin) / CLOCKS_PER_SEC;
  	std::cout << "temps calcul du produit matriciel: " <<tempsCalc <<"s " << std::endl;
	clock_t begin2 = clock();
	cout << "le produit matriciel est : " << endl ;
	cout << m1*m2 << endl;
	clock_t end2 = clock();
  	double tempsCalc2 = double(end2 - begin2) / CLOCKS_PER_SEC;
  	std::cout << "temps calcul du produit matriciel (Eigen): " <<tempsCalc2 <<"s " << std::endl;
	return 0;
}