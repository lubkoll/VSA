#ifndef ALGORITHM_INTERFACE_ABSTRACT_C0_FUNCTIONAL_HH
#define ALGORITHM_INTERFACE_ABSTRACT_C0_FUNCTIONAL_HH

#include <memory>

namespace Algorithm
{
  class AbstractBanachSpace;
  class AbstractFunctionSpaceElement;

  class AbstractC0Functional
  {
  public:
    AbstractC0Functional(const AbstractBanachSpace& domain);

    virtual ~AbstractC0Functional();
    
    virtual std::unique_ptr<AbstractC0Functional> clone() const = 0;

    virtual void setArgument(const AbstractFunctionSpaceElement& x) = 0;

    virtual double operator()(const AbstractFunctionSpaceElement&);// = 0;

    virtual double d0() const = 0;

    const AbstractBanachSpace& getDomain() const;

  private:
    const AbstractBanachSpace& domain_;
  };
}

#endif // ALGORITHM_INTERFACE_ABSTRACT_C0_FUNCTIONAL_HH