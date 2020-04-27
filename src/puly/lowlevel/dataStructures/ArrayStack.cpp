#include "ArrayStack.h"
#include "../debugging/Log.h"

Puly::ArrayStack::ArrayStack(float arr[10]) : x(0), top(-1), i(0)
{
	for (int ii = 0; ii < 10; ii++) {
		arr[ii] = stack[ii];
	}
}

void Puly::ArrayStack::push(void)
{
	if (top >= 10 - 1) {
		return;
	}
	else {
		top++;
		stack[top] = x;
	}
}

void Puly::ArrayStack::pop(void)
{
	if (top <= -1)
	{
		return;
	}
	else
	{
		top--;
	}
}

void Puly::ArrayStack::display(void)
{
	if (top >= 0)
	{
		for (i = top; i >= 0; i--)
			PL_LOG_INFO(stack[i]);
	}
	else
	{
		PL_LOG_INFO("Stack empty");
	}
}
