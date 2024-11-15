#ifndef __FCMATRIXALGO_H__
#define  __FCMATRIXALGO_H__
#include "eigen3/Eigen/Core"
#include<utility>

using MCoef  = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>;
using MConst = Eigen::Matrix<double,Eigen::Dynamic,1>;
using MOrder = Eigen::Matrix< int  ,Eigen::Dynamic,1>;

class FCmatrixAlgo{
 public:
  
  FCmatrixAlgo() = default;
  ~FCmatrixAlgo() = default;


  static void GaussElimination(MCoef&, MConst&);

  static void GaussEliminationPivot(MCoef&, MConst&, MOrder&);

  static void LUdecomposition(MCoef&, MOrder&, bool bpivot=false);

  static std::pair<MCoef, MCoef> LUmatrices(MCoef&);		// retrive L and U matrices from hybrid

};
#endif //ifndef __FCMATRIXALGO_H__
