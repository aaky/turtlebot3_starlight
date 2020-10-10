#ifndef __STARLIGHT_BASE_CLASS_H__
#define __STARLIGHT_BASE_CLASS_H__

#pragma once

#include <mutex>
#include <unistd.h>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

using namespace std;

#define ACTION_SERVER_WAITING_TIME (5.0)
#define MAX_RESULT_WAIT_TIMEOUT (100.0)

namespace starlight_robotics
{

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class StarLightBase
{
private:
	MoveBaseClient action_client;
	string name_action_client;

public:
	StarLightBase() : name_action_client("move_base") , action_client("move_base",true)
	{
	
	}

	StarLightBase(string action_client_name) : 
		name_action_client(action_client_name) , action_client(action_client_name.c_str(),true)
	{
		ROS_INFO("Initialized Action client with name : %s",this->name_action_client.c_str());
	}

	StarLightBase(const StarLightBase &object) : 
		name_action_client(object.name_action_client) , action_client(object.name_action_client.c_str(),true)
	{

	}

	~StarLightBase()
	{

	}

	bool connectActionServer();

	bool sendGoalToRobot(float x_axis_coordinate, float y_axis_coordinate, double robot_yaw,string frame_namespace = "");

	bool fetchLastGoalResult();

};	

} //star_light_robotics

#endif
