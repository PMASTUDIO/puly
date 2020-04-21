#include "DebugDrawManager.h"

void Puly::DebugDrawManager::AddLine(Point& fromPosition, Point& toPosition)
{
	debugLines.push_back(std::make_shared<DebugLine>(fromPosition, toPosition));
}

void Puly::DebugDrawManager::OnUpdate()
{
	for (auto &line : debugLines)
		line->DrawLine();
}
