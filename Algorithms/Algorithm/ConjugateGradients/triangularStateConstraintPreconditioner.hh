#ifndef ALGORITHM_CONJUGATE_GRADIENTS_TRIANGULARSTATECONSTRAINTPRECONDITIONER_HH
#define ALGORITHM_CONJUGATE_GRADIENTS_TRIANGULARSTATECONSTRAINTPRECONDITIONER_HH

#include <memory>

#include "Interface/abstractLinearSolver.hh"
#include "Interface/Operator/abstractOperator.hh"
#include "FunctionSpaces/ProductSpace/productSpaceElement.hh"
#include "Util/Mixins/adjointIndex.hh"
#include "Util/Mixins/controlIndex.hh"
#include "Util/Mixins/stateIndex.hh"

namespace Algorithm
{
  /// \cond
  class VectorSpace;
  /// \endcond

  class TriangularStateConstraintPreconditioner
      : public Interface::AbstractOperator, public Mixin::AdjointIndex, public Mixin::ControlIndex, public Mixin::StateIndex
  {
  public:
    TriangularStateConstraintPreconditioner(std::shared_ptr<Interface::AbstractLinearSolver> stateSolver,
                                            std::shared_ptr<Interface::AbstractLinearSolver> controlSolver,
                                            std::shared_ptr<Interface::AbstractLinearSolver> adjointSolver,
                                            std::unique_ptr<Interface::AbstractOperator>&& B,
                                            std::unique_ptr<Interface::AbstractOperator>&& BT,
                                            VectorSpace* domain,
                                            VectorSpace* range);

    std::unique_ptr<Interface::AbstractVector> operator()(const Interface::AbstractVector& x) const final override;

    std::unique_ptr<Interface::AbstractVector> kernelOffset(const Interface::AbstractVector& rhs) const;

  private:
    TriangularStateConstraintPreconditioner* cloneImpl() const;

    std::shared_ptr<Interface::AbstractLinearSolver> stateSolver_, controlSolver_, adjointSolver_;
    std::unique_ptr<Interface::AbstractOperator> B_, BT_;
  };
}

#endif // ALGORITHM_CONJUGATE_GRADIENTS_TRIANGULARSTATECONSTRAINTPRECONDITIONER_HH
