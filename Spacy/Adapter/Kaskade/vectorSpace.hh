#ifndef SPACY_ADAPTER_KASKADE_VECTOR_SPACE_HH
#define SPACY_ADAPTER_KASKADE_VECTOR_SPACE_HH

#include <type_traits>
#include <memory>

#include "Spacy/vector.hh"
#include "Spacy/vectorSpace.hh"
#include "Spacy/Spaces/productSpace.hh"
#include "Spacy/Util/Mixins/impl.hh"
#include "Spacy/Util/cast.hh"

#include "l2Product.hh"
#include "vector.hh"
#include "util.hh"

namespace Spacy
{
  namespace Kaskade
  {
    /**
     * @ingroup KaskadeGroup
     * @brief Creator for vector space elements for %Kaskade 7
     * @see @ref VectorCreatorAnchor "VectorCreator", @ref VectorCreatorConceptAnchor "VectorCreatorConcept"
     */
    template <class Description>
    class VectorCreator :
        public Mixin::Impl< std::decay_t< std::remove_pointer_t< std::decay_t<typename boost::fusion::result_of::at_c<typename Description::Spaces,0>::type> > > >
    {
      using Space = std::decay_t< std::remove_pointer_t< std::decay_t<typename boost::fusion::result_of::at_c<typename Description::Spaces,0>::type> > >;
    public:
      /**
       * @brief Create from %Kaskade 7 function space.
       * @param space single %Kaskade 7 function space (no product space)
       */
      VectorCreator(const Space& space)
        : Mixin::Impl<Space>{space}
      {}

      /// Generate vector for %Kaskade 7.
      Vector<Description> operator()(const VectorSpace* space) const
      {
        return Vector<Description>{*space};
      }
    };

    /**
     * @ingroup KaskadeGroup
     * @brief Create single space with hilbert space structure for %Kaskade 7.
     * @param space single %Kaskade 7 function space (no product space)
     */
    template <class Description, class Space>
    auto makeHilbertSpace(const Space& space)
    {
      return ::Spacy::makeHilbertSpace( Kaskade::VectorCreator<Description>{space} , l2Product<Description>{} );
    }

    /**
     * @ingroup KaskadeGroup
     * @brief Create product space with hilbert space structure for %Kaskade 7.
     * @param spaces boost fusion forward sequence of const pointers to %Kaskade 7 function spaces
     * @param primalIds ids of primal variables
     * @param dualIds ids of dual variables
     */
    template <class Description, class Spaces>
    auto makeHilbertSpace(const Spaces& spaces, const std::vector<unsigned>& primalIds, const std::vector<unsigned>& dualIds = {})
    {
      constexpr int n = boost::fusion::result_of::size<typename Description::Variables>::value;
      std::vector<std::shared_ptr< VectorSpace > > newSpaces( n );

      Detail::MakeSpaces<Description,0,n>::apply(spaces,newSpaces);

      return ::Spacy::ProductSpace::makeHilbertSpace( newSpaces , primalIds , dualIds );
    }
  }
}

#endif // SPACY_ADAPTER_KASKADE_VECTOR_SPACE_HH