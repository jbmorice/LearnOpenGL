#include "ex1_1_hello_window.hpp"
#include "ex1_2_hello_triangle.hpp"

int main(int argc, char* argv[])
{
	Ex1_1_Hello_Window ex1_1;
	Ex1_2_Hello_Triangle ex1_2;
	
	ExerciseBase* currentExercise = &ex1_2;

	currentExercise->run();
}
