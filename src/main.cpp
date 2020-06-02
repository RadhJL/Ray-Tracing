#include <iostream>
#include <random>

#include <omp.h>
#include "core/defines.hpp"
#include "core/chrono.hpp"
#include "core/image.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "materials/flatColorMaterial.hpp"
#include "materials/damierMaterial.hpp"
#include "3d/sphere.hpp"
#include "3d/plane.hpp"
#include "3d/cube.hpp"
#include "3d/triangleMesh.hpp"
#include "3d/cylinder.hpp"
#include "3d/cone.hpp"
#include "light/sphere_light.hpp"
#include "light/dir_light.hpp"
#include "light/point_light.hpp"
#include "brdf/microfacet.hpp"
#include "accelerator/box.hpp"
#include "3d/csg.hpp"

namespace ISICG_ISIR
{
	int main(int argc, char **argv)
	{
		if (argc != 4)
		{
			throw std::runtime_error(
				"Invalid program argument: must be launched with <imageWidth> "
				"<imageHeight> <imageName>\n e.g. 800 600 results.jpg");
		}

		const std::string name(argv[1]);
		const uint width = 1500;
		const uint height = 1500;

		ImageJPG image(width, height);
		//origin target upguide fov aspectratio
		Camera camera(vec3(0.0f, 3.0f, 9.5f), vec3(0.0f, 0.0f, 0.1f), vec3(0.0f, 1.0f, 0.0f), 35.0f *  3.14159265359f/ 180.0f, (float)width / (float)height);
		Scene scene(camera);
	
		//Materials
		FlatColorMaterial glass= FlatColorMaterial::glass();
		FlatColorMaterial bronze = FlatColorMaterial::bronze();
		FlatColorMaterial emerald = FlatColorMaterial::emerald();

		FlatColorMaterial obsidian = FlatColorMaterial::obsidian();
		FlatColorMaterial pearl = FlatColorMaterial::pearl();
		FlatColorMaterial ruby = FlatColorMaterial::ruby();
		FlatColorMaterial turquoise = FlatColorMaterial::turquoise();

		FlatColorMaterial brass = FlatColorMaterial::brass();
		FlatColorMaterial chrome = FlatColorMaterial::chrome();
		FlatColorMaterial copper = FlatColorMaterial::copper();
		FlatColorMaterial gold = FlatColorMaterial::gold();
		FlatColorMaterial silver = FlatColorMaterial::silver();

		FlatColorMaterial white_plastic = FlatColorMaterial::white_plastic();
		FlatColorMaterial red_plastic = FlatColorMaterial::red_plastic();
		FlatColorMaterial black_plastic = FlatColorMaterial::black_plastic();
		FlatColorMaterial cyan_plastic = FlatColorMaterial::cyan_plastic();
		FlatColorMaterial green_plastic = FlatColorMaterial::green_plastic();
		FlatColorMaterial yellow_plastic = FlatColorMaterial::yellow_plastic();
		
		
		FlatColorMaterial black_rubber = FlatColorMaterial::black_rubber();
		FlatColorMaterial cyan_rubber = FlatColorMaterial::cyan_rubber();
		FlatColorMaterial red_rubber = FlatColorMaterial::red_rubber();
		FlatColorMaterial white_rubber = FlatColorMaterial::white_rubber();
		FlatColorMaterial yellow_rubber = FlatColorMaterial::yellow_rubber();
	
		FlatColorMaterial mirror = FlatColorMaterial::mirror();
		
		//axe x,y,z => 0, 1, 2
		DamierMaterial damier0(black_rubber,white_rubber,1);
		DamierMaterial damier1(white_plastic,bronze,2);
		//ruby ahmer  obsidian ak7el cool
		//blakc plastic + cyyan (azre9)plastic perfect yellow plastic 
		// red rubber perfect

		Cone left_cone(vec3(-4.7, -1, -5), 1.0f, 3.0f, &yellow_plastic,camera.getView());
		Cone right_cone(vec3(4.7, -1, -5), 1.0f, 3.0f, &yellow_plastic,camera.getView());

		Sphere top_left_sphere(vec3(-5, 7, -5), 1, &mirror,camera.getView());
		Sphere top_right_sphere(vec3(5, 7, -5), 1, &mirror,camera.getView());
		
		Cube left_cube(vec3(-4.0, -1, 4.5), vec3(-3.0, 0, 3.5), &ruby, camera.getView());// todo 6 faces with planes
		Sphere middle_left_sphere(vec3(-3.5, 1.0, 4), 0.5, &ruby,camera.getView());
		
		Cube right_cube(vec3(3.0, -1, 4.5), vec3(4.0, 0, 3.5), &pearl, camera.getView());// todo 6 faces with planes
		Sphere middle_right_sphere(vec3(3.5, 1.0, 4), 0.5, &pearl,camera.getView());

		Cylinder left_cylinder(vec3(-4.0,-1.0,0.0),vec3(-4.0,1.0,0.0), 0.2, &turquoise,camera.getView()); 
		Cylinder left_x0_cylinder(vec3(-4,1.5,1.5),vec3(-4,2.5,-0.5), 0.2, &turquoise,camera.getView()); 

		Cylinder right_cylinder(vec3(4.0,-1.0,0.0),vec3(4.0,1.0,0.0), 0.2, &cyan_rubber,camera.getView()); 
		Cylinder right_x0_cylinder(vec3(4,2.5,1.5),vec3(4,1.5,-0.5), 0.2, &cyan_rubber,camera.getView()); 


	   Sphere csg_sphere0(vec3(0, 0.0, 4.5), 0.9, &yellow_rubber,camera.getView());
	   Plane csg_plane0(vec3(-3, -0.2, 7.5),vec3(3,-0.2,7.5),vec3(3,-0.2,0),vec3(-3,-0.2,0), &damier0,camera.getView());
	   
	   Sphere csg_sphere1(vec3(0, 1.0, 5), 0.65, &red_rubber,camera.getView());
	   Cube csg_cube1(vec3(-0.5, 0.5, 5.5), vec3(0.5, 1.5, 4.5), &gold, camera.getView());// todo 6 faces with planes
	   
	   std::vector<Oper> csg_operations0;
 	   std::vector<AObject3D *> csg_primitives0 ;
	   csg_operations0.push_back(inter);
	   csg_primitives0.push_back(&csg_sphere0);
	   csg_primitives0.push_back(&csg_plane0);
	   CSG csg0(csg_primitives0, csg_operations0); 


	   std::vector<Oper> csg_operations1;
 	   std::vector<AObject3D *> csg_primitives1;
	   csg_operations1.push_back(diff);
	   csg_primitives1.push_back(&csg_cube1);
	   csg_primitives1.push_back(&csg_sphere1);
	   CSG csg1(csg_primitives1, csg_operations1); 

		scene.addObject(&csg0);
		scene.addObject(&csg1);

		scene.addObject(&top_left_sphere);
		scene.addObject(&top_right_sphere);
		scene.addObject(&left_cube);
		scene.addObject(&right_cube);
		scene.addObject(&left_cone);
		scene.addObject(&right_cone);
		scene.addObject(&middle_left_sphere);
		scene.addObject(&middle_right_sphere);
		scene.addObject(&left_cylinder);		
		scene.addObject(&right_cylinder);	
		scene.addObject(&left_x0_cylinder);	
		scene.addObject(&right_x0_cylinder);	
		
		vec3 min(-5,-1,5);
		vec3 max(5,7,-5);
		//Spheres
		Sphere red_plastic_sphere(vec3(-3, 1.5, 2), 0.65, &white_rubber,camera.getView());
		Sphere bronze_sphere(vec3(-1, 1.5, 2), 0.65, &yellow_rubber,camera.getView());
		Sphere glass_sphere(vec3(1, 1.5, 2), 0.65f, &cyan_rubber,camera.getView());
		Sphere white_plastic_sphere(vec3(3, 1.5, 2), 0.65, &red_rubber,camera.getView());
		Sphere emerald_sphere(vec3(3, 1.5, 2), 0.65, &emerald,camera.getView());
		//planes
		
		float z0 = min.z;
		float z1 = max.z;
		float y0 = min.y;
		float y1 = max.y;
		float x0 = min.x;
		float x1 = max.x;

		// a, b, c, d CCW and material
		//Plane plane0(vec3(5,0,5),vec3(5,0,-5),vec3(-5,0,-5),vec3(-5,0,5), &damier0,camera.getView());
		//Plane plane1(vec3(5,0,-5),vec3(5,5,-5),vec3(-5,5,-5),vec3(-5,0,-5), &damier1,camera.getView());
		Plane plane0(vec3(x0, y0, z0),vec3(x1,y0,z0),vec3(x1,y1,z0),vec3(x0,y1,z0), &damier0,camera.getView());
		Plane plane4(vec3(x0,y0,7), vec3(x1,y0,7), vec3(x1,y0,z1), vec3(x0, y0, z1), &red_rubber,camera.getView());//bas
		Plane plane5(vec3(x1,y1,z0), vec3(x0,y1,z0), vec3(x0,y1,z1), vec3(x1, y1, z1), &red_rubber,camera.getView());//haut
		Plane plane3(vec3(x0,y1,z1), vec3(x0,y1,z0), vec3(x0,y0,z0), vec3(x0, y0, z1),&yellow_rubber,camera.getView());//gauche
		Plane plane1(vec3(x1,y1,z0), vec3(x1,y1,z1), vec3(x1,y0,z1), vec3(x1, y0, z0), &yellow_rubber,camera.getView());//droite
		Plane plane2(vec3(x1,y1,z1),vec3(x0,y1,z1), vec3(x0,y0,z1),vec3(x1, y0, z1), &red_rubber,camera.getView());//face
		
		
		//Cubes
		Cube cube(vec3(-3.0, 0, 0.5), vec3(-2.0, 1, -0.5), &red_plastic, camera.getView());// todo 6 faces with planes
		Cube cube1(vec3(-0.5, 0, 0.5), vec3(0.5, 1, -0.5), &white_plastic, camera.getView());// todo 6 faces with planes
		Cube cube2(vec3(2.0, 0, 0.5), vec3(3.0, 1, -0.5), &bronze, camera.getView());// todo 6 faces with planes

		Cube cube3(vec3(1.1f, 0, 3), vec3(2.1, 0.5f, 1), &emerald, camera.getView());// todo 6 faces with planes
		Cube cube4(vec3(-2.f, 0, 3), vec3(-1.1, 0.5f, 1), &emerald, camera.getView());// todo 6 faces with planes
		
		//Cylinders
		vec3 a(-2,3,0);
		vec3 b(0,5,0);
		vec3 c(2,3,0);
		vec3 d(0,1,0);

		Cylinder cylinder0(vec3(0.0,0.5,5.5),vec3(0.0,0.5,-5.5), 0.3, &white_plastic,camera.getView());
		Cylinder cylinder1(vec3(5.0,0.5,0.0),vec3(-5.0,0.5,0.0), 0.3f, &white_plastic,camera.getView());
		Cylinder cylinder2(c,d, 0.3f, &emerald,camera.getView());
		Cylinder cylinder3(d,a, 0.3f, &bronze,camera.getView());
		Cylinder cylinder4(vec3(0, 3.0f, 1), vec3(0, 3.3f,-1), 0.3f, &red_plastic,camera.getView());


		//Cones
		Cone cone0(vec3(-3, 0.5f, 0), 1.0f, 2.0f, &red_plastic,camera.getView());
		Cone cone2(vec3(0, 0.5f, 0), 1.0f, 3.0f, &bronze,camera.getView());
		Cone cone1(vec3(3, 0.5f, 0), 1.0f, 2.0f, &white_plastic,camera.getView());

		//spheres	
		//scene.addObject(&glass_sphere);
		//scene.addObject(&glass_sphere);
		//scene.addObject(&white_plastic_sphere);
		//scene.addObject(&red_plastic_sphere);
		//scene.addObject(&bronze_sphere);
		//scene.addObject(&emerald_sphere);
		
		//planes
		//scene.addObject(&plane0);
		scene.addObject(&plane1);
	    scene.addObject(&plane2);
		scene.addObject(&plane3);
	    scene.addObject(&plane4);
		scene.addObject(&plane5);
	   
		//cubes
		//scene.addObject(&cube);
		//scene.addObject(&cube1);
		//scene.addObject(&cube2);
		//scene.addObject(&cube3);
		//scene.addObject(&cube4);

		//cylinders
		//scene.addObject(&cylinder0);
		//scene.addObject(&cylinder1);
		//scene.addObject(&cylinder2);
		//scene.addObject(&cylinder3);
		//scene.addObject(&cylinder4);
		//scene.addObject(&cylinder5);

		//cones
		//scene.addObject(&cone2);

		//Lights 
		SphereLight l1(vec3(1.0f, 1.0f, 1.0f), 500, camera.getView(),vec3(0.0f, 4.34f, 6.5f));
		SphereLight l2(vec3(1.0f, 1.0f, 1.0f), 500.0, camera.getView(),vec3(-5.0f, 5.5f, 5.0f));
		DirLight l3(vec3(1.0f, 1.0f, 1.0f), 1.1f, camera.getView(),vec3(0.0f, 0.5f, 0.5f));
		DirLight l4(vec3(1.0f, 1.0f, 1.0f), 1.0, camera.getView(),vec3(0.0f, 1.0f, 0.0f));
		PointLight l5(vec3(1.0f, 1.0f, 1.0f), 1.1f, camera.getView(),vec3(0.0f, 5.5f, 5.0f));
		PointLight l6(vec3(1.0f, 1.0f, 1.0f), 1.0, camera.getView(),vec3(-5.0f, 5.5f, 5.0f));
				
		scene.addLight(&l1);
		//scene.addLight(&l2);
		//scene.addLight(&l3);
		//scene.addLight(&l4);
		//scene.addLight(&l5);
		//scene.addLight(&l6);
		
		//Triangle Mesh
		//type (0,1) => (SAH,COUNT)
		TriangleMesh mesh("src/objects/polygon.obj",1,&chrome,camera.getView());
		scene.addObject(&mesh);
		
		Chrono chrono;
		chrono.start();
		std::cout << "Rendering..." << std::endl;
		
		int depth = 3;
		bool anti_aliasing = false;
		int grid_size = 4;
		float inc = 1 / float(grid_size);

		#pragma omp parallel for schedule(dynamic)
			for(int k=0; k < width * height ; k++) {
					int i = k / height; 
					int j = k % height;
					int nb_sample = 1;
					vec4 sample_color= vec4(0);
					Ray ray = scene.generateRay(vec3(2.0f * j/width - 1.0f, -2.0f * i/height + 1.0f, 1.0f));
					sample_color += vec4(scene.raytrace(ray,depth), 1.f);
						
					//anti-aliasing
					if(anti_aliasing)
					for(float l = -0.5 ; l <= 0.5 ; l +=inc){
						for(float c = -0.5 ; c <= 0.5 ; c+=inc){
							if(l == 0 && c ==0)
								continue;
							ray = scene.generateRay(vec3((2.0f * (j + l)) / width - 1.0f, (-2.0f * (i + c)) / height + 1.0f, 1.0f));
							sample_color += vec4(scene.raytrace(ray,depth), 1.f);
							nb_sample ++;
						}
					}

					image.setPixel(j, i, sample_color/float(nb_sample));	
			}

		chrono.stop();
		std::cout << "Rendering done. Image computed in "
				  << chrono.elapsedTime() << "s (" << image.getWidth() << "x"
				  << image.getHeight() << ")" << std::endl;

		std::cout << "Save image as: " << name << std::endl;
		image.save(name);

		return EXIT_SUCCESS;
	}
} 

int main(int argc, char **argv)
{
	try
	{
		return ISICG_ISIR::main(argc, argv);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception caught !" << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
