//
//   Copyright (C) 2004 by Lakin Wecker And Corey Auger
//   nikal@nucleus.com corey@coreyauger.com
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
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Object.h"
#include <iostream>
namespace Affine {

/**
 * An affine point, which inherits from an affine object.
 */
class Vector : public Object
{
	public:
		/**
		 * Default constructor which creates itself as an affine point
		 * at the origin.
		 */
		Vector(const Scalar x=0.0, const Scalar y=0.0, const Scalar z=0.0);
		/**
		 * Copy constructor for base class
		 */
		Vector( const Object &source );

		/**
		 * Copy constructor.
		 */
		Vector( const Vector &source );

		/**
		 * The contructor, which is virtual so superclasses can inherit from
		 * it appropriately.
		 */
		virtual ~Vector();
		
		/**
		 * The assignment operator
		 * @param Other The other affine object you are assigning to this vector.
		 * @return Point A constant reference to *this;
		 */
		Vector &operator=( const Object &other );

		/**
		 * The assignment operator
		 * @param Other The other affine object you are assigning to this vector.
		 * @return Point A constant reference to *this;
		 */
		Vector &operator=( const Vector &other );
		/**
		 * overloaded output operator.
		 */
		friend const std::ostream &operator<<( std::ostream &out, const Vector &other ) {
			out << "{" << other[0] << ","
					<< other[1] << ","
					<< other[2] << ","
					<< other[3] << "}";
			return out;
		}
		
};

}//End namespace affine

#endif	//_VECTOR_H_
