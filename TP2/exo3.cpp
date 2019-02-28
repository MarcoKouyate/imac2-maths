#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;


float dotProduct(const VectorXf &v1, const VectorXf &v2)
	{
		if (v1.size() != v2.size()) return 0.0; // la condition pour faire le produit scalaire 
		double sum = 0.0;
		for (unsigned int i=0; i<v1.size(); i++)
		{
			sum += v1(i)*v2(i);
		}
		return sum;
	}

int main(int argc, char const *argv[])
{
	const unsigned int dimension = 5;
	VectorXf v1(dimension), v2(dimension);
	cout << "le produit scalaire est : " << dotProduct(v1,v2) << endl;
	return 0;
}