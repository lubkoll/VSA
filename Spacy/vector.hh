#ifndef SPACY_VECTOR_HH
#define SPACY_VECTOR_HH

#include "Spacy/Util/Mixins/impl.hh"
#include "Spacy/Util/Mixins/target.hh"
#include "Spacy/Util/memFnChecks.hh"
#include "Spacy/Util/memOpChecks.hh"
#include "Spacy/Util/cast.hh"
#include "Spacy/Util/typeErasedStorage.hh"
#include "Spacy/Spaces/RealSpace/real.hh"

namespace Spacy
{
  /// @cond
  class Real;
  class VectorSpace;
  /// @endcond

  /** \addtogroup SpacyGroup
   * @{
   */

  /**
   * @anchor VectorAnchor
   * @brief Vector class.  Can store objects that satisfy the requirements of \ref VectorConceptAnchor "VectorConcept".
   */
//  using AnyVector = boost::type_erasure::any< Concepts::VectorConcept >;


  /// Type-erased linear operator \f$A:\ X \to Y \f$.
  class Vector : public Mixin::ToTarget<Vector>
  {
    friend class ToTarget<Vector>;

    struct AbstractBase
    {
      virtual ~AbstractBase(){}
      virtual Real operator()(const Vector& x) const = 0;
      virtual void add(const Vector& y) = 0;
      virtual void subtract(const Vector& y) = 0;
      virtual void multiply(double a) = 0;
      virtual Vector negate() const = 0;
      virtual bool compare(const Vector& y) const = 0;
      virtual const VectorSpace* space() const = 0;
      virtual std::unique_ptr<AbstractBase> clone() const = 0;
    };

    template <class Impl>
    struct Base : AbstractBase, Mixin::Impl<Impl>
    {
      Base(Impl const& impl)
        : Mixin::Impl<Impl>(impl)
      {}

      Base(Impl&& impl)
        : Mixin::Impl<Impl>(std::move(impl))
      {}

      Real operator()(const Vector& x) const final override
      {
        return this->impl()(*x.template target<Impl>());
      }

      void add(const Vector& y) final override
      {
        this->impl() += (*y.template target<Impl>());
      }
      void subtract(const Vector& y) final override
      {
        this->impl() -= (*y.template target<Impl>());
      }

      void multiply(double a) final override
      {
        this->impl() *= a;
      }

      Vector negate() const final override
      {
        return Vector( -this->impl() );
      }

      bool compare(const Vector& y) const final override
      {
        return this->impl() == (*y.template target<Impl>());
      }

      const VectorSpace* space() const final override
      {
        return this->impl().space();
      }

      std::unique_ptr<AbstractBase> clone() const final override
      {
        return std::make_unique< Base<Impl> >(this->impl());
      }
    };

  public:
    Vector() = default;

    /// Construct from operator implementation.
    template <class Impl,
              class = std::enable_if_t<!std::is_same<std::decay_t<Impl>,Vector>::value>/*,
//              class = std::enable_if_t<HasMemOp_callable<Impl,Impl,Real>::value>,
              class = std::enable_if_t<HasMemOp_add<Impl>::value>,
              class = std::enable_if_t<HasMemOp_subtract<Impl>::value>,
              class = std::enable_if_t<HasMemOp_multiply<Impl>::value>,
//              class = std::enable_if_t<HasMemOp_negate<Impl>::value>,
              class = void_t< TryMemOp_negate<Impl> >,
              class = std::enable_if_t<HasMemFn_space<Impl>::value>*/ >
    Vector(Impl&& impl)
      : base_( Base< std::decay_t<Impl> >(std::forward<Impl>(impl)) )
    {}

    /// Assign from operator implementation.
    template <class Impl,
              class = std::enable_if_t<!std::is_same<std::decay_t<Impl>,Vector>::value>,
//              class = std::enable_if_t<HasMemOp_callable<Impl,Impl,Real>::value>,
              class = std::enable_if_t<HasMemOp_add<Impl>::value>,
              class = std::enable_if_t<HasMemOp_subtract<Impl>::value>,
              class = std::enable_if_t<HasMemOp_multiply<Impl>::value>,
              class = void_t< TryMemOp_negate<Impl> >,
              class = std::enable_if_t<HasMemFn_space<Impl>::value> >
    Vector& operator=(Impl&& impl)
    {
      base_ = Base< std::decay_t<Impl> >(std::forward<Impl>(impl));
      return *this;
    }


    /// Apply operator.
    Real operator()(const Vector& x) const;

    Vector& operator+=(const Vector& y);

    Vector& operator-=(const Vector& y);

    Vector& operator*=(double a);

    Vector operator-() const;

    bool operator==(const Vector& y) const;

    /// Access underlying space of linear operators.
    const VectorSpace& space() const;

    /// Check if an implementation has been assigned.
    operator bool() const;

  private:
    CopyViaClonePtr<AbstractBase> base_;
  };

//  class Vector : public Mixin::CopyingUniqueImpl<AnyVector>
//  {
//  public:
//    Vector()
//      : Mixin::CopyingUniqueImpl<AnyVector>( std::make_unique<AnyVector>() )
//    {}

//    template <class VImpl,
//              class = std::enable_if_t<!std::is_same<std::decay_t<VImpl>,Vector>::value>
//              >
//    Vector(VImpl&& v)
//      : Mixin::CopyingUniqueImpl<AnyVector>(std::make_unique<AnyVector>(std::forward<VImpl>(v)))
//    {}

////    Vector(AnyVector v);

// //   operator AnyVector() const;

//    /**
//     * @brief In-place summation \f$ x+=y\f$.
//     * @param y vector to add to this vector
//     * @return \f$ x+=y\f$.
//     */
//    Vector& operator+=(const Vector& y);

//    /**
//     * @brief In-place subtraction \f$ x-=y\f$.
//     * @param y vector to subtract from this vector
//     * @return \f$ x-=y\f$.
//     */
//    Vector& operator-=(const Vector& y);

//    /**
//     * @brief In-place multiplication \f$ x*=a\f$.
//     * @param a scaling factor
//     * @return \f$ x*=a\f$.
//     */
//    Vector& operator*=(double a);

//    /**
//     * @brief Negation \f$ -x\f$.
//     * @return \f$ -x \f$.
//     */
//    Vector operator-() const;

//    Vector operator()(const Vector& y) const;

//    /**
//     * @brief Comparison operator \f$ x==y\f$.
//     * @param y vector to compare with this vector
//     * @return \f$ x==y\f$.
//     */
//    bool operator==(const Vector& y) const;

//    const VectorSpace& space() const;
//  };

  template <class ToType>
  bool is(const Spacy::Vector& v)
  {
    return v.template target<ToType>() != nullptr;
//    return Spacy::target<ToType>(v) != nullptr;
//    return is<ToType>(v.impl());
  }

  template <class ToType>
  const ToType& cast_ref(const Spacy::Vector& v)
  {
    return *v.template target<ToType>();
//    return *Spacy::target<ToType>(v);
//    return cast_ref<ToType>(v.impl());
  }

  template <class ToType>
  ToType& cast_ref(Spacy::Vector& v)
  {
    return *v.template target<ToType>();
//    return *Spacy::target<ToType>(v);
//    return cast_ref<ToType>(v.impl());
  }

////  template <class> struct Scale;

  /**
   * @brief Multiplication with arithmetic types (double,float,int,...).
   * @return \f$z=a*x\f$.
   */
  template <class Arithmetic,
            class = std::enable_if_t< std::is_arithmetic<Arithmetic>::value > >
  Vector operator*(Arithmetic a, Vector x)
  {
    return x *= a;
  }

  Vector operator*(Vector x, double a);

  /**
   * @brief Sum of vectors.
   * @return Compute \f$z=x+y\f$.
   */
  Vector operator+(Vector x, const Vector& y);

  /**
   * @brief Subtract vectors.
   * @return \f$z=x-y\f$.
   */
  Vector operator-(Vector x, const Vector& y);

  /**
   * @brief Compute scalar product.
   * @return \f$z=x*y=(x,y)\f$.
   */
  Real operator*(const Vector& x, const Vector& y);

  /**
   * @brief Compute norm, where the norm associated with the underlying function space is used.
   * @return \f$ z = \|x\| \f$.
   */
  Real norm(const Vector& x);

  void checkDualPairing(const Vector& x, const Vector& y);
//  template <class T>
//  struct Scale
//  {
//    operator Vector() const
//    {
//      auto y = x;
//      return y *= a;
//    }

//    T a;
//    const Vector& x;
//  };
  /** @} */
}

#endif // SPACY_VECTOR_HH
