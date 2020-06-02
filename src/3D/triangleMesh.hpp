#ifndef __ISICG_ISIR_TRIANGLE_MESH__
#define __ISICG_ISIR_TRIANGLE_MESH__

#include "core/defines.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <vector>
#include "aObject3D.hpp"
#include "assimp/mesh.h"
#include <accelerator/bvh.hpp>
#include "triangle.hpp"

namespace ISICG_ISIR
{
	struct MeshTriangle
	{
		union {
			struct
			{
				uint _v0, _v1, _v2;
			};
			uint _v[3];
		};
	};

	class TriangleMesh : public AObject3D
	{
	public:

		TriangleMesh(const std::string &path,const int& type, AMaterial *const material, const glm::mat3 &view)
		{
			this->load(path);
			this->setMaterial(material);
			this->setViewMatrix(view);
			bvh = new BVH(p_primitives,root_bbx,type );
		}
		
		void load(const std::string &path)
		{
			Assimp::Importer importer;
			std::vector<MeshTriangle> triangles;
			std::vector<vec3> vertices;
			root_bbx = Box();
			const aiScene *const scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate);

			if (scene == nullptr)
				throw std::runtime_error("Cannot import file: " + path);

			const uint nbMeshes = scene->mNumMeshes;
			uint nbTriangles = 0;
			uint nbVertices = 0;
			
			for (uint i = 0; i < nbMeshes; ++i)
			{
				const aiMesh *const mesh = scene->mMeshes[i];
				nbTriangles += mesh->mNumFaces;
				nbVertices += mesh->mNumVertices;
			}
			printf("nbTriangles  %d \n" ,nbTriangles);

			triangles.resize(nbTriangles);
			vertices.resize(nbVertices);

			uint currentTriangle = 0;
			uint currentVertex = 0;
			
			for (uint m = 0; m < nbMeshes; ++m)
			{
				const aiMesh *const mesh = scene->mMeshes[m];
				const aiMaterial *const material = scene->mMaterials[mesh->mMaterialIndex];

				for (uint f = 0; f < mesh->mNumFaces; ++f, ++currentTriangle)
				{
					const aiFace face = mesh->mFaces[f];

					MeshTriangle &tri = triangles[currentTriangle];

					for (uint v = 0; v < 3; ++v)
					{
						const uint idV = face.mIndices[v];
						tri._v[v] = idV;
					}
				}

				for (uint v = 0; v < mesh->mNumVertices; ++v, ++currentVertex)
				{
					vec3 &vertex = vertices[currentVertex];
					vertex.x = mesh->mVertices[v].x/3.0f;
					vertex.y = mesh->mVertices[v].y/3.0f + 2 ;
					vertex.z = mesh->mVertices[v].z/3.0f;
					
				}
			}

			primitives.reserve(triangles.size());
			for (int i = 0; i < triangles.size(); i++)
			{
				Triangle T(vertices[triangles[i]._v0],vertices[triangles[i]._v1],vertices[triangles[i]._v2]);
				primitives.push_back(T);
				p_primitives.push_back(&(primitives[i]));
				root_bbx.expand(T.centroid);
			}

			std::cout << "Loaded: " << std::endl
					  << "- nb faces: " << triangles.size() << std::endl
					  << "- nb vertices: " << vertices.size() << std::endl;
		}

		 Intersection intersect(const Ray &ray)
		 {
				Intersection inter;
				float t;
				if(bvh->root->box.intersectBox(ray))
				{	
					inter = bvh->intersect(bvh->root,ray); 
					if(inter.obj != nullptr){
						inter.normal = normalize(inter.normal);
						inter.obj = this;
					}
				}

				return inter;
		};

	private:
		std::vector<Triangle> primitives;
		std::vector<Triangle*> p_primitives;
		BVH* bvh;
		Box root_bbx;
	};
} 

#endif
