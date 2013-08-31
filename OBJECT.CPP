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
#include "Object.h"
// Overloaded matrix multiplication function.  (friend).
Affine::Object Affine::operator*( const std::valarray<Affine::Scalar> &matrix, const Affine::Object &aObj ) {
	assert( matrix.size() == 16 );
	Scalar nAffine[4];
	nAffine[0] = matrix[0] * aObj.myAffine[0] + 
			matrix[1]*aObj.myAffine[1] +
			matrix[2]*aObj.myAffine[2] +
			matrix[3]*aObj.myAffine[3];
	nAffine[1] = matrix[4] * aObj.myAffine[0] + 
			matrix[5]*aObj.myAffine[1] +
			matrix[6]*aObj.myAffine[2] +
			matrix[7]*aObj.myAffine[3];
	nAffine[2] = matrix[8] * aObj.myAffine[0] + 
			matrix[9]*aObj.myAffine[1] +
			matrix[10]*aObj.myAffine[2] +
			matrix[11]*aObj.myAffine[3];
	nAffine[3] = matrix[12] * aObj.myAffine[0] + 
			matrix[13]*aObj.myAffine[1] +
			matrix[14]*aObj.myAffine[2] +
			matrix[15]*aObj.myAffine[3];
	return Affine::Object( nAffine );
}

// Overloaded scalar multiplication operator.
Affine::Object Affine::operator*( const Affine::Scalar &s, const Affine::Object &obj ) {
	Scalar nAffine[4];
	nAffine[0] = obj.myAffine[0] * s;
	nAffine[1] = obj.myAffine[1] * s;
	nAffine[2] = obj.myAffine[2] * s;
	nAffine[3] = obj.myAffine[3] * s;
	return Object( nAffine );
}

//All the following methods are part of the Affine::Object class.
//Hence they are all in it's namespace.
namespace Affine {
	//------------------------------------------------------------------------------
	// Object Constructors and Destructors
	//------------------------------------------------------------------------------
	
	Object::Object(const Scalar x, const Scalar y, const Scalar z, const Scalar w, Scalar *mem) 
		:
		myShared( true ),
		myAffine( mem )
		
	{
		if( !mem ) {
			myShared = false;
			myAffine = new Scalar[4];
		}
		
		myAffine[0] = x;
		myAffine[1] = y;
		myAffine[2] = z;
		myAffine[3] = w;
	}
	
	Object::Object( Scalar a[] ) :
		myShared( false ),
		myAffine( new Scalar[4] )
	{
		myAffine[0] = a[0];	
		myAffine[1] = a[1];	
		myAffine[2] = a[2];	
		myAffine[3] = a[3];	
	}
	
	Object::Object( const Object &source ) 
		: 
		myShared( source.myShared ),
		myAffine( source.myAffine )
	{
		if( !myShared ) {
			myAffine = new Scalar[4];
			myAffine[0] = source[0];
			myAffine[1] = source[1];
			myAffine[2] = source[2];
			myAffine[3] = source[3];
		}
	}
	
	Object::~Object() {
		if( !myShared ) delete[] myAffine;
	}
	
	
	Scalar Object::dot( const Object &other ) const {
		return myAffine[0]*other[0] +
				myAffine[1]*other[1] +
				myAffine[2]*other[2] +
				myAffine[3]*other[3];
	}
	
	Object Object::cross( const Object &other ) const {
		Object c;
		c[0] = myAffine[1]*other[2] - myAffine[2]*other[1];//v1.y*v2.z - v1.z*v2.y;
		c[1] = myAffine[2]*other[0] - myAffine[0]*other[2];//v1.z*v2.x - v1.x*v2.z;
		c[2] = myAffine[0]*other[1] - myAffine[1]*other[0];//v1.x*v2.y - v1.y*v2.x;
		c[3] = 0.0; // A vector
		return c;
	}
	
	void Object::transform( const std::valarray<Scalar> &matrix ) {
		assert( matrix.size() == 16 );
		Scalar nAffine[4];
		nAffine[0] = matrix[0] * myAffine[0] + 
				matrix[1]*myAffine[1] +
				matrix[2]*myAffine[2] +
				matrix[3]*myAffine[3];
		nAffine[1] = matrix[4] * myAffine[0] + 
				matrix[5]*myAffine[1] +
				matrix[6]*myAffine[2] +
				matrix[7]*myAffine[3];
		nAffine[2] = matrix[8] * myAffine[0] + 
				matrix[9]*myAffine[1] +
				matrix[10]*myAffine[2] +
				matrix[11]*myAffine[3];
		nAffine[3] = matrix[12] * myAffine[0] + 
				matrix[13]*myAffine[1] +
				matrix[14]*myAffine[2] +
				matrix[15]*myAffine[3];
		myAffine[0] = nAffine[0];
		myAffine[1] = nAffine[1];
		myAffine[2] = nAffine[2];
		myAffine[3] = nAffine[3];
	}
	
	void Object::normalize() {
		Scalar len = length();
		myAffine[0] = myAffine[0]/len;
		myAffine[1] = myAffine[1]/len;
		myAffine[2] = myAffine[2]/len;
		//I'm normalzing the homogenous
		//coordinate, as it will have no affect
		//on a vector but will mess with a point
		//and we don't want to normalize points.
		myAffine[3] = myAffine[3]/len;
	}
	
	Scalar Object::length() const {
		return sqrt( dot(*this) );
	}
	void Object::set( const Scalar x, const Scalar y, const Scalar z ) {
		myAffine[0] = x;
		myAffine[1] = y;
		myAffine[2] = z;
	}
	//------------------------------------------------------------------------------
	// Overloaded operators
	//------------------------------------------------------------------------------
	
	Object &Object::operator=( const Object &source ) {
		if( !myShared ) delete[] myAffine;
		myShared = source.myShared;
		if( !myShared ) myAffine = new Scalar[4];
		myAffine[0] = source[0];
		myAffine[1] = source[1];
		myAffine[2] = source[2];
		myAffine[3] = source[3];
		return *this;
	}
	
	bool Object::operator==( const Object &other ) const {
		if( myAffine[0] != other[0] ) return false;
		if( myAffine[1] != other[1] ) return false;
		if( myAffine[2] != other[2] ) return false;
		if( myAffine[3] != other[3] ) return false;
		return true;
	}
	
	
	Object Object::operator+( const Object &addend) const {
		Scalar affine[4];
		affine[0] = myAffine[0] + addend[0];
		affine[1] = myAffine[1] + addend[1];
		affine[2] = myAffine[2] + addend[2];
		affine[3] = myAffine[3] + addend[3];
		return Object( affine );
	}
	
	void Object::operator+=( const Object &addend) {
		myAffine[0] += addend[0];
		myAffine[1] += addend[1];
		myAffine[2] += addend[2];
		myAffine[3] += addend[3];
	}
	
	Object Object::operator-( const Object &minuend) const {
		Scalar affine[4];
		affine[0] = myAffine[0] - minuend[0];
		affine[1] = myAffine[1] - minuend[1];
		affine[2] = myAffine[2] - minuend[2];
		affine[3] = myAffine[3] - minuend[3];
		return Object( affine );
	}
	
	void Object::operator-=( const Object &minuend) {
		myAffine[0] -= minuend[0];
		myAffine[1] -= minuend[1];
		myAffine[2] -= minuend[2];
		myAffine[3] -= minuend[3];
	}
	
	Object Object::operator*( const Scalar &other ) const {
		Scalar affine[4];
		affine[0] = myAffine[0] * other;
		affine[1] = myAffine[1] * other;
		affine[2] = myAffine[2] * other;
		affine[3] = myAffine[3] * other;
		return Object( affine );
	}
	
	void Object::operator*=( const Scalar &other ) {
		myAffine[0] *= other;
		myAffine[1] *= other;
		myAffine[2] *= other;
		myAffine[3] *= other;
	}
	
	Object Object::operator/( const Scalar &other ) const {
		Scalar affine[4];
		affine[0] = myAffine[0] / other;
		affine[1] = myAffine[1] / other;
		affine[2] = myAffine[2] / other;
		affine[3] = myAffine[3] / other;
		return Object( affine );
	}
	
	void Object::operator/=( const Scalar &other ) {
		myAffine[0] /= other;
		myAffine[1] /= other;
		myAffine[2] /= other;
		myAffine[3] /= other;
	}
	
	Object Object::operator-( ) const {
		Scalar affine[4];
		affine[0] = -myAffine[0];
		affine[1] = -myAffine[1];
		affine[2] = -myAffine[2];
		affine[3] = -myAffine[3];
		return Object( affine);
	}
	
	Object Object::operator*( const Object &other ) const {
		Scalar affine[4];
		affine[0] = myAffine[0] * other[0];
		affine[1] = myAffine[1] * other[1];
		affine[2] = myAffine[2] * other[2];
		affine[3] = myAffine[3] * other[3];
		return Object( affine );
	}
	
	Object Object::operator%( const Object &other ) const {
		return cross( other );
	}
	
	Scalar &Object::operator[]( const unsigned int i ) {
		assert( i < 4 && "Scalar &Object::operator[]...");
		return myAffine[i];
	}

	const Scalar &Object::operator[]( const unsigned int i ) const {
		assert( i < 4 && "const Scalar &Object::operator[]...");
		return myAffine[i];
	}

}//Namespace Affine
