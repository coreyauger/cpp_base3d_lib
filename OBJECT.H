//
//   Copyright (C) 2004 by Corey Auger
//   nikal@nucleus.com
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
//

#ifndef _OBJECT_H_
#define _OBJECT_H_

//------------------------------------------------------------------------------
// STL includes
//------------------------------------------------------------------------------
#include <valarray>
#include <numeric>
#include <iostream>
#include <cassert>

#include "Scalar.h"
//------------------------------------------------------------------------------
// Object Declaration
//------------------------------------------------------------------------------
namespace Affine {

class Object
{
	public:
		//------------------------------------------------------------------------------
		// Object Constructors and Destructors
		//------------------------------------------------------------------------------
		/**
		 * Default constructor which creates the Affine::Object with the option
		 * of using default values. Default assumes a point at the origin.
		 * @param x The x value for the object. Default = 0.0.
		 * @param y The y value for the object. Default = 0.0.
		 * @param z The z value for the object. Default = 0.0.
		 * @param w The w value for the object. Default = 1.0.
		 */
		Object(const Scalar x=0.0, 
			const Scalar y=0.0, 
			const Scalar z=0.0, 
			const Scalar w=1.0, 
			Scalar *mem=NULL);
		 
		/**
		 * Default constructor allowing an Affine object to b built from an array
		 * of points.
		 * @param a The array corresponding to the points we need. Must be size 4.
		 */
		explicit Object( Scalar a[] );
		/**
		 * Copy Constructor.
		 */
		Object( const Object &source );
		/**
		 * The default virtual destructor.
		 */
		virtual ~Object();
		
		/**
		 * Finds the dot product of this affine object and the other.
		 * @param other The other affine object used in the inner product
		 */
		virtual Scalar dot( const Object &other ) const;
		/**
		 * Finds the cross product of this object "cross" the other object.
		 * @param other The other affine object used in the outer product.
		 */
		virtual Object cross( const Object &other ) const;
		/**
		 * Applies the myAffine transformation matrix to this myAffine object.
		 *
		 * @param matrix The Affine transformation matrix.  Must have 16 elements.
		 */
		virtual void transform( const std::valarray<Scalar> &matrix );
		/**
		 * Turns this vector into a unit length vector.
		 */
		virtual void normalize();
		/**
		 * Returns the length of this, assuming it's a vector.
		 * @return Scalar
		 */
		virtual Scalar length() const;

		/**
		 * Allows you to set the 3 components.
		 */
		virtual void set( const Scalar x, const Scalar y, const Scalar z );
		
		//------------------------------------------------------------------------------
		// Overloaded operators
		//------------------------------------------------------------------------------
		/**
		 * Assignment operator.
		 */
		Object &operator=( const Object &source );
		/**
		 * Equality comparison operator
		 */
		bool operator==( const Object &other ) const;
		/**
		 * Overloaded operator for matrix * affine object multiplication.
		 *
		 * @param matrix The 16 element transformation matrix.
		 * @param aObj The Affine object to apply this matrix to.
		 */
		friend Object operator*( const std::valarray<Scalar> &matrix, const Object &aObj );
		/**
		 * Overloaded addition operator which adds the addend to this object.
		 * @param addend The object which is being added to this objects.
		 */
		virtual Object operator+( const Object &addend) const;
		/**
		 * Overloaded addition operator which adds the addend to this object.
		 * @param addend The object which is being added to this objects.
		 */
		virtual void operator+=( const Object &addend);
		/**
		 * Overloaded subtraction operator which subtracts the minuend from this object.
		 * @param minuend The object which is being subtracted from this object.
		 */
		virtual Object operator-( const Object &minuend) const;
		/**
		 * Overloaded subtraction operator which subtracts the minuend from this object.
		 * @param minuend The object which is being subtracted from this object.
		 */
		virtual void operator-=( const Object &minuend);
		/**
		 * Multiplies the scalar by this object, resulting in a new object.
		 * @param s The Scalar that is the lhs of this multiplaction.
		 * @param obj The Affine Object that is the rhs of this multiplication.
		 */
		friend Object operator*( const Scalar &s, const Object &obj );
		/**
		 * Overloaded multiplication operator which multiplies the Scalar against this object.
		 * @param other The scalar which is multiplied by each element of this object.
		 */
		virtual Object operator*( const Scalar &other ) const;
		/**
		 * Overloaded multiplication operator which multiplies the Scalar against this object.
		 * @param other The scalar which is multiplied by each element of this object.
		 */
		virtual void operator*=( const Scalar &other );
		/**
		 * Overloaded subtraction operator which subtracts the rhs from the lhs.
		 * @param other The Scalar which is divided into each element of this object.
		 */
		virtual Object operator/( const Scalar &other ) const;
		/**
		 * Overloaded subtraction operator which subtracts the rhs from the lhs.
		 * @param other The Scalar which is divided into each element of this object.
		 */
		virtual void operator/=( const Scalar &other );
		/**
		 * Overloaded unary minus operator negates the object.
		 */
		virtual Object operator-( ) const;
		/**
		 * Overloaded operator which multiplies each entry of the objects together
		 * returning a new object.
		 * @param other The other object which we will use in our inner product
		 * @return Object the resulting object
		 */
		virtual Object operator*( const Object &other ) const;
		/**
		 * Overloaded cross product operator which finds the outer product off
		 * the two affine objects.
		 * @param other The other object which we will use in our cross product
		 */
		virtual Object operator%( const Object &other ) const;

		/**
		 * Overloaded element access operator.
		 * @return Scalar
		 */
		Scalar &operator[]( const unsigned int i );

		/**
		 * Overloaded element access operator doesn't allow access
		 * @return Scalar
		 */
		const Scalar &operator[]( const unsigned int i ) const;
		 
	protected:
		bool myShared;
		// Object variables
		Scalar *myAffine;
};

}// End Affine namespace



#endif	//_OBJECT_H_
