#pragma once
#include "exercise_base.h"

class Ex1_2_Hello_Triangle : public ExerciseBase
{
private:
	void prepare() override
	{

	}

	void render() override
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void cleanup() override
	{

	}

public:
	Ex1_2_Hello_Triangle()
		: ExerciseBase("Exercise 1.2 - Hello Triangle")
	{
	}
};