#pragma once

namespace Puly {

	struct ArrayStack {
		ArrayStack(float arr[10]);

		void push(void);
		void pop(void);
		void display(void);

		float stack[10];
		int top, x, i;
	};

}