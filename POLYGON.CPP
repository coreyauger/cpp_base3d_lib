#include "Polygon.h"

namespace Affine{
	

/*
	Polygon::Polygon( const unsigned int num,  )
		:
		mNumVerticies( num )
	{
		return;
	}
*/	
	/*
	Polygon::Polygon( const Polygon& inSource )
		:
		
	{
		return;
	}
	
	
	int Polygon::classify(Polygon *poly)
	{
		int		result	=	CF_UNCLASSIFYED;			// stores the result	 
		float	distance;								// holds the distance results when we test the verts to this faces plane
		for(int i=0; i<numVerts; i++)					// loop through all the vertex data in the (to_classify) face
		{
			distance = this->distance(*poly->verts[i]);	// get the distance to this point from our plane.
			if(distance > -SMALL && distance < SMALL)			// if the distance is zero (with float error) then this poin is on the plane
			{
				if(result == CF_UNCLASSIFYED || result == CF_ONPLANE)	// if this is the first point tested or all other points have been on the plane
				{	
					result = CF_ONPLANE;								// classify the result so far as onplane
					continue;											// continue setting points
				}
				else continue;											// otherwise leave result set as back or front and keep testing points
			}
			else if(distance > 0.0f)										// if the distance is positive then the point is in fron of the plane.
			{
				if(result == CF_UNCLASSIFYED || result == CF_FRONT || result == CF_ONPLANE)	// if the point is unclassifyed all front or all onplane so far then
				{
					result = CF_FRONT;									// classify the result as front so far
					continue;											// continue checking points
				}
				else return CF_SPANNING;								// otherwise we know that it is spannign and we can return for now.
			}
			else if(distance < 0.0f)										// if the distance is negative then we know that the point is behind the plane
			{
				if(result == CF_UNCLASSIFYED || result == CF_BACK || result == CF_ONPLANE)	// if the point is unclassifyed all back or all onplane so far then
				{
					result = CF_BACK;									// classify the result as back so far
					continue;											// continue checking points
				}
				else return CF_SPANNING;								// otherwise we know that it is spannign and we can return for now.			
			}
		}
		return result;	
	}
	
	
	int Polygon::classify(Plane *plane)
	{
		int		result	=	CF_UNCLASSIFYED;			// stores the result	 
		float	distance;								// holds the distance results when we test the verts to this faces plane
		for(int i=0; i<numVerts; i++)							// loop through all the vertex data in the (to_classify) face
		{
			distance = plane->distance(*this->verts[i]);	// get the distance to this point from our plane.
			if(distance > -SMALL && distance < SMALL)			// if the distance is zero (with float error) then this poin is on the plane
	
			{
				if(result == CF_UNCLASSIFYED || result == CF_ONPLANE)	// if this is the first point tested or all other points have been on the plane
				{	
					result = CF_ONPLANE;								// classify the result so far as onplane
					continue;											// continue setting points
				}
				else continue;											// otherwise leave result set as back or front and keep testing points
			}
			else if(distance > 0.0f)										// if the distance is positive then the point is in fron of the plane.
			{
				if(result == CF_UNCLASSIFYED || result == CF_FRONT || result == CF_ONPLANE)	// if the point is unclassifyed all front or all onplane so far then
				{
					result = CF_FRONT;									// classify the result as front so far
					continue;											// continue checking points
				}
				else return CF_SPANNING;								// otherwise we know that it is spannign and we can return for now.
			}
			else if(distance < 0.0f)										// if the distance is negative then we know that the point is behind the plane
			{
				if(result == CF_UNCLASSIFYED || result == CF_BACK || result == CF_ONPLANE)	// if the point is unclassifyed all back or all onplane so far then
				{
					result = CF_BACK;									// classify the result as back so far
					continue;											// continue checking points
				}
				else return CF_SPANNING;								// otherwise we know that it is spannign and we can return for now.			
			}
		}
		return result;	
	}
	
	
	void Polygon::split(Plane *splitter, Polygon *front, Polygon *back)
	{
		int			frontIndex = 0;
		int			backIndex = 0;
		int			i;
		float		dist;
		float		lastSide = 0.0f;
		Vector3		*newVertex;
		Ray			*edge;
		front->verts = (Vector3**)malloc(sizeof(Vector3*)*(this->numVerts+1));	// get some mem
		back->verts = (Vector3**)malloc(sizeof(Vector3*)*(this->numVerts+1));		// get some mem
		
		for(i=0; i<this->numVerts; i++)
		{
			dist = splitter->distance(*this->verts[i]);
			if((dist<0.0f && lastSide>0.0f) || (dist>0.0f && lastSide<0.0f))		// edge spanning plane
			{
				edge = new Ray(*this->verts[i-1], *this->verts[i]);	// make an ray to signify edge
				newVertex = (Vector3*)malloc(sizeof(Vector3));
				edge->getIntersection(splitter, newVertex);			// find itersection with plane
				front->verts[frontIndex++] = newVertex;				// add new vert to front
				back->verts[backIndex++] = newVertex;				// add new vert to back
			}
	
			if(dist > 0.0f)											// in front of the plane
			{
				front->verts[frontIndex++] = this->verts[i];			// add vert to front poly
			}
			else if(dist < 0.0f)									// in back of plane
			{
				back->verts[backIndex++] = this->verts[i];			// add vert to the back poly
			}
			else{													// right on split plane
				front->verts[frontIndex++] = this->verts[i];			// add to front
				back->verts[backIndex++] = this->verts[i];			// and back
			}
			lastSide = dist;
		}
		dist = splitter->distance(*this->verts[0]);					// last edge case below
		if((dist<0.0f && lastSide>0.0f) || (dist>0.0f && lastSide<0.0f))	// edge spanning plane
		{
			edge = new Ray(*this->verts[0], *this->verts[this->numVerts-1]);// make an ray to signify edge
			newVertex = (Vector3*)malloc(sizeof(Vector3));
			edge->getIntersection(splitter, newVertex);				// find itersection with plane
			front->verts[frontIndex++] = newVertex;					// add new vert to front
			back->verts[backIndex++] = newVertex;					// add new vert to back
		}
		front->numVerts = frontIndex;							// record num verts for front poly
		back->numVerts = backIndex;								// record num verts for back poly
	}
	
	
	AABB*	Polygon::getPolygonAABB()
	{
		AABB *aabb = new AABB();
		for(int i=0; i<numVerts; i++)
		{
			aabb->addPoint(*verts[i]);
		}
		return aabb;
	}
	*/
	
} // end Affine namespace

