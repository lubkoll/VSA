#include "minimalAccuracy.hh"

namespace Algorithm
{
  namespace Mixin
  {
    MinimalAccuracy::MinimalAccuracy(double accuracy) noexcept
      : minimalAccuracy_(accuracy)
    {}

    void MinimalAccuracy::setMinimalAccuracy(double accuracy)
    {
      minimalAccuracy_ = accuracy;
      notify();
    }

    double MinimalAccuracy::minimalAccuracy() const noexcept
    {
      return minimalAccuracy_;
    }

    void MinimalAccuracy::update(MinimalAccuracy* changedSubject)
    {
      setMinimalAccuracy( changedSubject->minimalAccuracy() );
    }

    void MinimalAccuracy::attachMinimalAccuracy(MinimalAccuracy& other)
    {
      attach(other);
    }

    void MinimalAccuracy::detachMinimalAccuracy(MinimalAccuracy& other)
    {
      detach(other);
    }
  }
}
