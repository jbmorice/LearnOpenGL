#ifndef EX1_1_HELLO_WINDOW
#define EX1_1_HELLO_WINDOW
#pragma once

#pragma once
#include "exercise_base.h"

class Ex1_1_Hello_Window : public ExerciseBase
{
private:
	void prepare() override
	{
		
	}

	void render() override
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void cleanup() override
	{
		
	}

public:
	Ex1_1_Hello_Window()
		: ExerciseBase("Exercise 1.1 - Hello Window")
	{
	}
};

#endif