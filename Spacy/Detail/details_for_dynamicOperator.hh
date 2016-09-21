// This file was automatically generated by friendly type erasure.
// Please do not modify.

#pragma once

#include <memory>
#include <functional>
#include <Spacy/linearOperator.hh>
#include <Spacy/vector.hh>
#include <Spacy/vectorSpace.hh>

namespace Spacy
{
    namespace DynamicOperatorDetail
    {
        template < class Interface, class Buffer >
        struct Functions
        {
            using clone_function = void ( * )( void*, std::shared_ptr< void >& );
            using clone_into_function = void ( * )( void*, Buffer&, std::shared_ptr< void >& );
            using call_const_Vector__ref__function = Vector ( * )( const Interface&, void*, const Vector& x );
            using M_function = LinearOperator ( * )( const Interface&, void* );
            using domain_function = const VectorSpace& (*)( const Interface&, void* );
            using range_function = const VectorSpace& (*)( const Interface&, void* );

            clone_function clone;
            clone_into_function clone_into;
            call_const_Vector__ref__function call_const_Vector__ref_;
            M_function M;
            domain_function domain;
            range_function range;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Vector call_const_Vector__ref_( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< const Impl* >( impl )->operator()( x );
            }

            static LinearOperator M( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->M();
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->range();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Vector call_const_Vector__ref_( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()( x );
            }

            static LinearOperator M( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().M();
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().range();
            }
        };
    }

    namespace DynamicLinearOperatorDetail
    {
        template < class Interface, class Buffer >
        struct Functions
        {
            using clone_function = void ( * )( void*, std::shared_ptr< void >& );
            using clone_into_function = void ( * )( void*, Buffer&, std::shared_ptr< void >& );
            using call_double__const_Vector__ref__function = Vector ( * )( const Interface&, void*, double t,
                                                                           const Vector& x );
            using add_const_DynamicLinearOperator__ref__function = Interface& (*)( Interface&, void*, void* y );
            using subtract_const_DynamicLinearOperator__ref__function = Interface& (*)( Interface&, void*, void* y );
            using multiply_double__function = Interface& (*)( Interface&, void*, double a );
            using negate_function = Interface ( * )( const Interface&, void* );
            using compare_const_DynamicLinearOperator__ref__function = bool ( * )( const Interface&, void*, void* y );
            using solver_function = std::function< Vector( const Vector& ) > ( * )( const Interface&, void* );
            using domain_function = const VectorSpace& (*)( const Interface&, void* );
            using range_function = const VectorSpace& (*)( const Interface&, void* );
            using space_function = const VectorSpace& (*)( const Interface&, void* );

            clone_function clone;
            clone_into_function clone_into;
            call_double__const_Vector__ref__function call_double__const_Vector__ref_;
            add_const_DynamicLinearOperator__ref__function add_const_DynamicLinearOperator__ref_;
            subtract_const_DynamicLinearOperator__ref__function subtract_const_DynamicLinearOperator__ref_;
            multiply_double__function multiply_double_;
            negate_function negate;
            compare_const_DynamicLinearOperator__ref__function compare_const_DynamicLinearOperator__ref_;
            solver_function solver;
            domain_function domain;
            range_function range;
            space_function space;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Vector call_double__const_Vector__ref_( const Interface& interface, void* impl, double t,
                                                           const Vector& x )
            {
                return static_cast< const Impl* >( impl )->operator()( std::move( t ), x );
            }

            static Interface& add_const_DynamicLinearOperator__ref_( Interface& interface, void* impl, void* y )
            {
                static_cast< Impl* >( impl )->operator+=( *static_cast< Impl* >( y ) );
                return interface;
            }

            static Interface& subtract_const_DynamicLinearOperator__ref_( Interface& interface, void* impl, void* y )
            {
                static_cast< Impl* >( impl )->operator-=( *static_cast< Impl* >( y ) );
                return interface;
            }

            static Interface& multiply_double_( Interface& interface, void* impl, double a )
            {
                static_cast< Impl* >( impl )->operator*=( std::move( a ) );
                return interface;
            }

            static Interface negate( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->operator-();
            }

            static bool compare_const_DynamicLinearOperator__ref_( const Interface& interface, void* impl, void* y )
            {
                return static_cast< const Impl* >( impl )->operator==( *static_cast< const Impl* >( y ) );
            }

            static std::function< Vector( const Vector& ) > solver( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->solver();
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->range();
            }

            static const VectorSpace& space( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->space();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Vector call_double__const_Vector__ref_( const Interface& interface, void* impl, double t,
                                                           const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()( std::move( t ), x );
            }

            static Interface& add_const_DynamicLinearOperator__ref_( Interface& interface, void* impl, void* y )
            {
                static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator+=(
                    static_cast< std::reference_wrapper< Impl >* >( y )->get() );
                return interface;
            }

            static Interface& subtract_const_DynamicLinearOperator__ref_( Interface& interface, void* impl, void* y )
            {
                static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator-=(
                    static_cast< std::reference_wrapper< Impl >* >( y )->get() );
                return interface;
            }

            static Interface& multiply_double_( Interface& interface, void* impl, double a )
            {
                static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator*=( std::move( a ) );
                return interface;
            }

            static Interface negate( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator-();
            }

            static bool compare_const_DynamicLinearOperator__ref_( const Interface& interface, void* impl, void* y )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator==(
                    static_cast< std::reference_wrapper< Impl >* >( y )->get() );
            }

            static std::function< Vector( const Vector& ) > solver( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().solver();
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().range();
            }

            static const VectorSpace& space( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().space();
            }
        };
    }

    namespace DynamicC1OperatorDetail
    {
        template < class Interface, class Buffer >
        struct Functions
        {
            using clone_function = void ( * )( void*, std::shared_ptr< void >& );
            using clone_into_function = void ( * )( void*, Buffer&, std::shared_ptr< void >& );
            using call_double__const_Vector__ref__function = Vector ( * )( const Interface&, void*, double t,
                                                                           const Vector& x );
            using d1_function = Vector ( * )( const Interface&, void*, double t, const Vector& x, const Vector& dx );
            using linearization_function = LinearOperator ( * )( const Interface&, void*, double t, const Vector& x );
            using M_function = LinearOperator ( * )( const Interface&, void* );
            using domain_function = const VectorSpace& (*)( const Interface&, void* );
            using range_function = const VectorSpace& (*)( const Interface&, void* );

            clone_function clone;
            clone_into_function clone_into;
            call_double__const_Vector__ref__function call_double__const_Vector__ref_;
            d1_function d1;
            linearization_function linearization;
            M_function M;
            domain_function domain;
            range_function range;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Vector call_double__const_Vector__ref_( const Interface& interface, void* impl, double t,
                                                           const Vector& x )
            {
                return static_cast< const Impl* >( impl )->operator()( std::move( t ), x );
            }

            static Vector d1( const Interface& interface, void* impl, double t, const Vector& x, const Vector& dx )
            {
                return static_cast< const Impl* >( impl )->d1( std::move( t ), x, dx );
            }

            static LinearOperator linearization( const Interface& interface, void* impl, double t, const Vector& x )
            {
                return static_cast< const Impl* >( impl )->linearization( std::move( t ), x );
            }

            static LinearOperator M( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->M();
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->range();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Vector call_double__const_Vector__ref_( const Interface& interface, void* impl, double t,
                                                           const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()( std::move( t ), x );
            }

            static Vector d1( const Interface& interface, void* impl, double t, const Vector& x, const Vector& dx )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().d1( std::move( t ), x, dx );
            }

            static LinearOperator linearization( const Interface& interface, void* impl, double t, const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().linearization( std::move( t ), x );
            }

            static LinearOperator M( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().M();
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().domain();
            }

            static const VectorSpace& range( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().range();
            }
        };
    }
}