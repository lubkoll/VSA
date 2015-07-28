#include "dampingStrategies.hh"

#include "c1Operator.hh"
#include "linearSolver.hh"

#include "Util/Exceptions/regularityTestFailedException.hh"

namespace Algorithm
{
  namespace Newton
  {
    namespace DampingStrategy
    {
      AffineCovariant::AffineCovariant(const C1Operator& F)
        : F_(F), oldDs(F.domain().element())
      {}

      DampingFactor AffineCovariant::compute(const LinearSolver& DFInv_, const FunctionSpaceElement& x, const FunctionSpaceElement& dx)
      {
        DampingFactor nu = 1;
        auto mu = 1., normDx = norm(dx);
        if( oldNu > 0 )
        {
          mu = normOldDx * normOldDs * oldNu / ( normDx * norm(oldDs - dx) );
          nu = std::min(1.,mu);
        }

        while(true)
        {
          if( !regularityTestPassed(nu)) throw RegularityTestFailedException("Newton::DampingStrategy::AffineCovariant",nu);

          auto trial = x + static_cast<double>(nu)*dx;
          auto ds = DFInv_(-F_(trial)) - (1-nu)*dx;
          auto normDs = norm(ds);

          auto muPrime = 0.5 * nu * nu / normDs;

          if( normDs/normDx >= 1)
          {
            nu = std::min(0.5*nu,muPrime);
            continue;
          }

          auto nuPrime = std::min(1.,muPrime);

          if( nu == 1 && nuPrime == 1 && normDs < eps() ) break;

          if( nuPrime >= 4*nu)
          {
            nu = nuPrime;
            continue;
          }

          break;
        }

        return nu;
      }


      AffineContravariant::AffineContravariant(const C1Operator& F)
        : F_(F)
      {}

      DampingFactor AffineContravariant::compute(const LinearSolver&, const FunctionSpaceElement& x, const FunctionSpaceElement& dx)
      {
        DampingFactor nu = 1.;
        auto norm_F_x = norm(F_(x));
        if( norm_F_x < sqrtEps() ) return nu;
        if( muPrime > 0 )
          nu = std::min( 1. , muPrime*norm_F_x_old/norm_F_x );

        while( true )
        {
          if( !regularityTestPassed(nu)) throw RegularityTestFailedException("Newton::DampingStrategy::AffineContravariant",nu);

          auto trial = x + static_cast<double>(nu)*dx;

          auto norm_F_trial = norm(F_(trial));

          auto theta = norm_F_trial/norm_F_x;
          muPrime = 0.5*norm_F_x*nu*nu / norm( F_(trial) - (1-nu)*F_(x) );

          if( theta >= 1 )
          {
            nu = std::min( muPrime , 0.5*nu );
            continue;
          }

          auto oldNu = nu;
          nu = std::min( 1. , muPrime );
          if( nu >= 4*oldNu ) continue;

          norm_F_x_old = norm_F_x;
          break;
        }

        return nu;
      }


      None::None(const C1Operator& F)
      {}

      DampingFactor None::compute(const LinearSolver&, const FunctionSpaceElement&, const FunctionSpaceElement&)
      {
        return 1;
      }
    }
  }
}
