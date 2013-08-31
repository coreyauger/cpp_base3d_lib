//
//   Copyright (C) 2004 by Corey Auger
//   corey@coreyauger.com
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

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Point.h"
#include <memory>

namespace Affine {


	class Sphere
	{
		private:
			std::auto_ptr< Point > 	mOrigin;
			Scalar			mRadius;
			
		public:
			Sphere( const Point& origin, Scalar radius=1.0f );
			Sphere( const Sphere &inSource );
			virtual ~Sphere() {};
	
			// ray intersect functions needed
	
	};

}//end Namespace Affine
#endif	//_SPHERE_H_

