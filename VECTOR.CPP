//
//   Copyright (C) 2004 by Lakin Wecker And Corey Auger
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
#include "Vector.h"
namespace Affine {


	Vector::Vector(const Scalar x, const Scalar y, const Scalar z) 
		: Object( x, y, z, 0.0)
	{
	}


	Vector::~Vector()
	{
	}
	
	Vector::Vector( const Object &source ) 
		: Object( source )
	{
		/*
		if( myAffine[3] != 0.0 ) {
			std::cerr << "[" << __FILE__ << ":" << __LINE__ << 
				"] Construction from an Affine object other than a Vector." << std::endl;
		}
		*/
	}

	Vector::Vector( const Vector &source ) 
		: Object( source[0], source[1], source[2], source[3] )
		
	{
		/*
		if( myAffine[3] != 0.0 ) {
			std::cerr << "[" << __FILE__ << ":" << __LINE__ << 
				"] Construction from an Affine object other than a Vector." << std::endl;
		}
		*/
	}

	Vector &Vector::operator=( const Object &other ) {
		/*if( other[3] != 0.0 ) {
			std::cerr << "[" << __FILE__ << ":" << __LINE__ << 
				"] Assignment from an Affine object other than a Vector." << std::endl;
		}*/
		myAffine[0] = other[0];
		myAffine[1] = other[1];
		myAffine[2] = other[2];
		return *this;
	}

	Vector &Vector::operator=( const Vector &other ) {
		/*if( other[3] != 0.0 ) {
			std::cerr << "[" << __FILE__ << ":" << __LINE__ << 
				"] Assignment from an Affine object other than a Vector." << std::endl;
		}*/
		myAffine[0] = other[0];
		myAffine[1] = other[1];
		myAffine[2] = other[2];
		return *this;
	}


} // Namespace Affine::Vector
