// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#include "functional.hh"

#include "Spacy/vector.hh"
#include "Spacy/Spaces/RealSpace/real.hh"

#include <cassert>

namespace Spacy
{
  Real Functional::operator()(const Vector& x) const
  {
    assert(base_);
    return base_->operator ()(x);
  }

  const VectorSpace& Functional::domain() const
  {
    assert(base_);
    return base_->domain();
  }

  Functional::operator bool() const
  {
    return base_;
  }
}