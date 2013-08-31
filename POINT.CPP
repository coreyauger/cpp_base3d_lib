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
#include "Point.h"

namespace Affine {

	Point::Point(const Scalar x, const Scalar y, const Scalar z) 
		: Object( x, y, z, 1.0)
	{
	}
	Point::Point( const Object &other ) 
		: Object( other )
	{
		/*if( other[3] == 1.0 ) {
			std::cerr << "[" << __FILE__ << ":" << __LINE__ << 
				"] Construction from an Affine object other than a point." << std::endl;
		}*/
	}

	Point::~Point()
	{
	}

	const Point &Point::operator=( const Object &other ) {
		/*if( other[3] == 1.0 ) {
			std::cerr << "[" << __FILE__ << ":" << __LINE__ << 
				"] Assignment from an Affine object other than a point." << std::endl;
		}*/
		myAffine[0] = other[0];
		myAffine[1] = other[1];
		myAffine[2] = other[2];
		return *this;
	}

}// namespace Affine::Point
