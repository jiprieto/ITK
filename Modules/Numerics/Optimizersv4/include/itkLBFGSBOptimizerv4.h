/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkLBFGSBOptimizerv4_h
#define __itkLBFGSBOptimizerv4_h

#include "itkLBFGSOptimizerBasev4.h"
#include "vnl/algo/vnl_lbfgsb.h"

namespace itk
{
/** \class LBFGSBOptimizerv4
 * \brief Limited memory Broyden Fletcher Goldfarb Shannon minimization with simple bounds.
 *
 * This class is a wrapper for converted fortan code for performing limited
 * memory Broyden Fletcher Goldfarb Shannon minimization with simple bounds.
 * The algorithm miminizes a nonlinear function f(x) of n variables subject to
 * simple bound constraints of l <= x <= u.
 *
 * See also the documentation in Numerics/lbfgsb.c
 *
 * References:
 *
 * [1] R. H. Byrd, P. Lu and J. Nocedal.
 * A Limited Memory Algorithm for Bound Constrained Optimization, (1995),
 * SIAM Journal on Scientific and Statistical Computing ,
 * 16, 5, pp. 1190-1208.
 *
 * [2] C. Zhu, R. H. Byrd and J. Nocedal.
 * L-BFGS-B: Algorithm 778: L-BFGS-B, FORTRAN routines for large scale
 * bound constrained optimization (1997),
 * ACM Transactions on Mathematical Software,
 * Vol 23, Num. 4, pp. 550 - 560.
 *
 * \ingroup Numerics Optimizersv4
 * \ingroup ITKOptimizersv4
 */
class LBFGSBOptimizerv4:
  public LBFGSOptimizerBasev4< vnl_lbfgsb >
{
public:
  /** Standard "Self" typedef. */
  typedef LBFGSBOptimizerv4                 Self;
  typedef LBFGSOptimizerBasev4<vnl_lbfgsb>  Superclass;
  typedef SmartPointer< Self >              Pointer;
  typedef SmartPointer< const Self >        ConstPointer;

  typedef Superclass::MetricType     MetricType;
  typedef Superclass::ParametersType ParametersType;
  typedef Superclass::ScalesType     ScalesType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(LBFGSBOptimizerv4, Superclass);

  /**  BoundValue type.
   *  Use for defining the lower and upper bounds on the variables.
   */
  typedef Array< double > BoundValueType;

  /** BoundSelection type
   * Use for defining the boundary condition for each variables.
   */
  typedef Array< long > BoundSelectionType;

  /**  Set the position to initialize the optimization. */
  void SetInitialPosition(const ParametersType & param);

  /** Get the position to initialize the optimization. */
  ParametersType & GetInitialPosition(void)
  {
  return m_InitialPosition;
  }

  /** Start optimization with an initial value. */
  virtual void StartOptimization(bool doOnlyInitialization = false) ITK_OVERRIDE;

  /** Plug in a Cost Function into the optimizer  */
  virtual void SetMetric(MetricType *metric) ITK_OVERRIDE;

  /** Set the lower bound value for each variable. */
  void SetLowerBound(const BoundValueType & value);

  itkGetConstReferenceMacro(LowerBound,BoundValueType);

  /** Set the upper bound value for each variable. */
  void SetUpperBound(const BoundValueType & value);

  itkGetConstReferenceMacro(UpperBound,BoundValueType);

  /** Set the boundary condition for each variable, where
   * select[i] = 0 if x[i] is unbounded,
   *           = 1 if x[i] has only a lower bound,
   *           = 2 if x[i] has both lower and upper bounds, and
   *           = 3 if x[1] has only an upper bound
   */
  void SetBoundSelection(const BoundSelectionType & select);

  itkGetConstReferenceMacro(BoundSelection,BoundSelectionType);

  /** Set/Get the CostFunctionConvergenceFactor. Algorithm terminates
   * when the reduction in cost function is less than factor * epsmcj
   * where epsmch is the machine precision.
   * Typical values for factor: 1e+12 for low accuracy;
   * 1e+7 for moderate accuracy and 1e+1 for extremely high accuracy.
   */
  virtual void SetCostFunctionConvergenceFactor(double);

  itkGetConstMacro(CostFunctionConvergenceFactor, double);

  /** Set/Get the MaximumNumberOfIterations. Default is 500 */
  virtual void SetMaximumNumberOfIterations(unsigned int);

  itkGetConstMacro(MaximumNumberOfIterations, unsigned int);

  /** Set/Get the MaximumNumberOfCorrections. Default is 5 */
  virtual void SetMaximumNumberOfCorrections(unsigned int);

  itkGetConstMacro(MaximumNumberOfCorrections, unsigned int);

  /** This optimizer does not support scaling of the derivatives. */
  virtual void SetScales(const ScalesType &) ITK_OVERRIDE;

  /** Get the current iteration number. */
  itkGetConstReferenceMacro(CurrentIteration, unsigned int);

  /** Get the current infinity norm of the project gradient of the cost
   * function. */
  itkGetConstReferenceMacro(InfinityNormOfProjectedGradient, double);

protected:
  LBFGSBOptimizerv4();
  virtual ~LBFGSBOptimizerv4();
  virtual void PrintSelf(std::ostream & os, Indent indent) const ITK_OVERRIDE;

  /** Internal optimizer type. */
  typedef   vnl_lbfgsb   InternalOptimizerType;

private:
  LBFGSBOptimizerv4(const Self &); //purposely not implemented
  void operator=(const Self &); //purposely not implemented

  double       m_CostFunctionConvergenceFactor;
  unsigned int m_MaximumNumberOfIterations;
  unsigned int m_MaximumNumberOfCorrections;
  unsigned int m_CurrentIteration;
  double       m_InfinityNormOfProjectedGradient;

  ParametersType          m_InitialPosition;
  BoundValueType          m_LowerBound;
  BoundValueType          m_UpperBound;
  BoundSelectionType      m_BoundSelection;
};
} // end namespace itk
#endif
