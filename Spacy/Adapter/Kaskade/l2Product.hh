#ifndef ALGORITHM_ADAPTER_KASKADE_L2PRODUCT_HH
#define ALGORITHM_ADAPTER_KASKADE_L2PRODUCT_HH

#include "Spacy/vector.hh"
#include "Spacy/Util/Exceptions/incompatibleSpaceException.hh"
#include "Spacy/Util/cast.hh"

namespace Spacy
{
  namespace Kaskade
  {
    /// \cond
    template <class> class Vector;
    /// \endcond

    /**
     * @ingroup KaskadeGroup
     * @brief l2 scalar product for Kaskade 7.
     */
    template <class Description>
    class l2Product
    {
    public:
      /**
       * @brief Compute l2 product.
       * @param x vector
       * @param y vector
       * @return \f$(x,y) = \sum_i x_i y_i \f$.
       */
      double operator()(const ::Spacy::Vector& x, const ::Spacy::Vector& y) const
      {
        checkSpaceCompatibility(x,y);
        return cast_ref< Vector<Description> >(x).impl() * cast_ref< Vector<Description> >(y).impl();
      }
    };
  }
}

#endif // ALGORITHM_ADAPTER_KASKADE_L2PRODUCT_HH