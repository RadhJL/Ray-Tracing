#ifndef __ISICG_ISIR_BVH_NODE__
#define __ISICG_ISIR_BVH_NODE__

#include "box.hpp"
namespace ISICG_ISIR
{
	class BVHNode 
	{
	public:
		
		BVHNode() = default;
		BVHNode(BVHNode *left, BVHNode *right,const Box& box,const int &range0,const int &range1) :
				left(left), right(right), box(box), range0(range0), range1(range1)
		{
		
		}

		BVHNode *left;
		BVHNode *right;
		Box box;
		int range0;
		int range1;
	};
} 

#endif
