#ifndef __STARLIGHT_MULTIROBOT_CLASS_H__
#define __STARLIGHT_MULTIROBOT_CLASS_H__

#pragma once

#include <thread>
#include <mutex>
#include <unistd.h>
#include <geometry_msgs/Pose.h>
#include <starlight_lib/StarLightBase.h>
#include <turtlebot3_starlight/StarLightMultiRobotMessage.h>

using namespace std;

namespace starlight_robotics
{
class StarLightMultiRobot 
{
private:
	int32_t number_of_robots;
	vector<string> robot_namespaces;
	vector<StarLightBase> goal_send_handler_pool;
	vector<bool> goal_results;
	mutex goal_handling_mutex;
	vector<thread> multi_robot_thread_pool;

	void setGoalResults(int32_t goal_idx,bool result)
	{
		lock_guard<mutex> guard(goal_handling_mutex);
		goal_results[goal_idx] = result;
	}

	vector<bool> getGoalResults() { return goal_results; }
public:
	StarLightMultiRobot(int32_t num_robots,vector<string> robot_namespaces)
	{
		this->number_of_robots = num_robots;
		this->robot_namespaces = robot_namespaces; 
		goal_results.reserve(num_robots);

		for(int32_t cnt = 0 ; cnt < this->number_of_robots; cnt++)
		{
			goal_send_handler_pool.push_back(StarLightBase(robot_namespaces[cnt].c_str()));
		}

		ROS_INFO("Created multiple robot action client instances");
	}

	~StarLightMultiRobot()
	{

	}

	void goalSendingThread(StarLightBase &base_goal_handler,
							turtlebot3_starlight::StarLightMultiRobotMessage goal_message,string robot_namespace,int32_t goal_index);

	void sendMultipleGoals(vector<turtlebot3_starlight::StarLightMultiRobotMessage> multi_robot_goals);

	vector<bool> fetchGoalResults();

};
}


#endif