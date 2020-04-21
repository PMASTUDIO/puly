#include "DebugDrawManager.h"

void Puly::DebugDrawManager::AddLine(Point& fromPosition, Point& toPosition)
{
	DebugLine newLine(fromPosition, toPosition);
	debugLines.push_back(newLine);
}

void Puly::DebugDrawManager::OnUpdate()
{
	for (auto line : debugLines)
		line.DrawLine();
}
