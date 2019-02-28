#include <iostream>
#include <eigen3/Eigen/Dense>
#include <vector>

using namespace Eigen;

double evalPolynomial(const VectorXd &p, const double x){
  double res = 0;
  double myx = 1;

  for (int i = 1 ; i < p.size();++i){
    res+=p[i]*myx;
    myx*=x;
  }

  return res;
}

VectorXd polymonialFromRoots(const VectorXd &roots){
  VectorXd p = VectorXd::Ones(roots.size()+1) ;

  p(0)= -roots(0);

  for (int i = 1; roots.size(); ++i){
    for (int j=i; j > 0 ; --j){
      p(j)=p(j-1)- roots(i)*p(j);
      p(0)*=-roots(i);
    }
  }

  return p;
}


VectorXd solvePolymonialRoots(const VectorXd &p, const unsigned int nbInter){

	//Compagnon Matrix
	VectorXd unitPoly(p/(-p(p.size()-1)));
	MatrixXd C = MatrixXd::Zero(p.size()-1,p.size()-1);
	C.bottomLeftCorner(C.rows()-1, C.cols()-1).setIdentity();
	C.rightCols(1)= unitPoly.head(unitPoly.size()-1);

	//iterative solver
	for(unsigned int i=0; i<nbInter; ++i){
		HouseholderQR<MatrixXd> qr(C);
		MatrixXd Q = qr.householderQ();
		MatrixXd R = qr.matrixQR().triangularView<Upper>();
		C= R*Q  ;
	}

	return C.diagonal();
}

int main()
{
	
  VectorXd roots(3);
  roots << 1,2,3;


  //std::cout << polymonialFromRoots(roots) << std::endl;
  

  

  return 0;
}



// g++ -Wall -I ~/eigen/  eigenSample.cpp 