#ifndef ALGORITHM_UTIL_MIXIN_FORWARDCONNECTION_HH
#define ALGORITHM_UTIL_MIXIN_FORWARDCONNECTION_HH

#include <functional>
#include <utility>
#include <vector>

namespace Algorithm
{
  namespace Mixin
  {
    /**
     * \brief Connection that forwards arguments of types Args...
     */
    template <class... Args>
    class ForwardConnection
    {
    protected:
      /**
       * @brief Forward args to all connected functions.
       */
      void forward(const Args&... args)
      {
        for( auto& f : connected ) f(args...);
      }

      /**
       * \brief Connect f.
       *
       * f must be storable in an object of type std::function<void(const Args&...)>.
       */
      template <class F>
      void connect(F&& f)
      {
        connected.push_back(std::forward<F>(f));
      }

    private:
      std::vector< std::function<void(const Args&...)> > connected;
    };
  }
}

#endif // ALGORITHM_UTIL_MIXIN_FORWARDCONNECTION_HH

