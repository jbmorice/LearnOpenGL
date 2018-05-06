#include <vector>

#include "ex1_getting_started/ex1_1_hello_window/ex1_1_hello_window.hpp"
#include "ex1_getting_started/ex1_2_hello_triangle/ex1_2_hello_triangle.hpp"
#include "ex1_getting_started/ex1_2_hello_triangle/ex1_2_hello_triangle_1.hpp"
#include "ex1_getting_started/ex1_2_hello_triangle/ex1_2_hello_triangle_2.hpp"
#include "ex1_getting_started/ex1_2_hello_triangle/ex1_2_hello_triangle_3.hpp"
#include "ex1_getting_started/ex1_3_shaders/ex1_3_shaders.hpp"
#include "ex1_getting_started/ex1_3_shaders/ex1_3_shaders_1.hpp"
#include "ex1_getting_started/ex1_4_textures/ex1_4_textures.hpp"
#include "ex1_getting_started/ex1_5_transformations/ex1_5_transformations.hpp"
#include "ex1_getting_started/ex1_6_coordinate_systems/ex1_6_coordinate_systems.hpp"

int main(int argc, char* argv[])
{
	// ExerciseBase and its derivatives follow a "Template Method" design pattern
	// #TODO : Clean this up and build a proper exercise manager class
	std::vector<ExerciseBase*> exercises;
	exercises.push_back(&Ex1_1_Hello_Window());
	exercises.push_back(&Ex1_2_Hello_Triangle());
	exercises.push_back(&Ex1_2_Hello_Triangle_1());
	exercises.push_back(&Ex1_2_Hello_Triangle_2());
	exercises.push_back(&Ex1_2_Hello_Triangle_3());
	exercises.push_back(&Ex1_3_Shaders());
	exercises.push_back(&Ex1_3_Shaders_1());
	exercises.push_back(&Ex1_4_Textures());
	exercises.push_back(&Ex1_5_Transformations());
	exercises.push_back(&Ex1_6_Coordinate_Systems());

	std::cout << "Exercises : " << std::endl;
	for(int i = 0; i < exercises.size(); i++)
	{
		std::cout << "---- " << std::to_string(i) << " : " << exercises[i]->getWindowName() << std::endl;
	}
	int choice;
	std::cin >> choice;

	exercises[choice]->run();

}
