#include "JoeGoalY.h"

#include "../JoeConstants.h"

JoeGoalY::JoeGoalY(float target) : target(target) {}
bool JoeGoalY::isInGoal(vec3i pos) {
	return pos.y == target;
}
float JoeGoalY::getHeuristicEstimation(vec3i pos) {
	return heuristicEstimation(pos, target);
}
float JoeGoalY::heuristicEstimation(vec3i node, float target) {
	if(node.y > target)
		return FALL_N_BLOCKS_COST[(int)floorf(node.y - target)] * 0.99f;
	if(target > node.y)
		return (target - node.y) * JUMP_TIME * 0.99f;
	return 0;
}
