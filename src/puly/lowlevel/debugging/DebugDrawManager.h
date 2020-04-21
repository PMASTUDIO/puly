#pragma once

#include <vector>
#include "primitives/DebugLine.h"
#include "primitives/Point.h"

namespace Puly {
	class DebugDrawManager {
	public:
		void AddLine(Point& fromPosition, Point& toPosition);

		void OnUpdate();

	private:
		std::vector<std::shared_ptr<DebugLine>> debugLines;
	};
};