#include "ex1_1_hello_window.hpp"
#include "ex1_2_hello_triangle.hpp"
#include "ex1_2_hello_triangle_1.hpp"
#include "ex1_2_hello_triangle_2.hpp"
#include "ex1_2_hello_triangle_3.hpp"
#include "ex1_3_shaders.hpp"

int main(int argc, char* argv[])
{
	Ex1_1_Hello_Window ex1_1;
	Ex1_2_Hello_Triangle ex1_2;
	Ex1_2_Hello_Triangle_1 ex1_2_1;
	Ex1_2_Hello_Triangle_2 ex1_2_2;
	Ex1_2_Hello_Triangle_3 ex1_2_3;
	Ex1_3_Shaders ex1_3;

	ExerciseBase* currentExercise = &ex1_3;

	currentExercise->run();
}
