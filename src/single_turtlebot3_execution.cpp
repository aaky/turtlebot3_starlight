#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <starlight_lib/StarLightBase.h>


int main(int argc, char** argv)
{
	ros::init(argc, argv, "starlight_single_navigation");

	// Init base goal handler from Starlight base class
	starlight_robotics::StarLightBase base_goal_handler("move_base");

	// Check if action server is connected to our action client
	if(base_goal_handler.connectActionServer())
	{
		// Send x,Y and Yaw for robot to plan path
		if(base_goal_handler.sendGoalToRobot(1.0,0.0,0.0))
		{
			ROS_INFO("Goal was Sent successfully to Robot");

			//Check result of navigation task
			if(base_goal_handler.fetchLastGoalResult())
			{
				ROS_INFO("Single Robot goal was reached successfully by robot");
			}
			else
			{
				ROS_ERROR("Robot failed to reach destination.");
			}
		}
		else
		{
			ROS_ERROR("Cannot send goal on action server.Please check if Action server for receiving goal is started!");
		}
	}
	else
	{
		ROS_ERROR("Action server connection failed");
	}

	return 0;
}
