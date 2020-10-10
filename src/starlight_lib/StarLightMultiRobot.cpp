#include <starlight_lib/StarLightMultiRobot.h>

using namespace starlight_robotics;

void StarLightMultiRobot::sendMultipleGoals(vector<turtlebot3_starlight::StarLightMultiRobotMessage> multi_robot_goals)
{
	for(int32_t cnt = 0 ; cnt < this->number_of_robots; cnt++)
	{
		multi_robot_thread_pool.push_back(thread(&StarLightMultiRobot::goalSendingThread,this,ref(this->goal_send_handler_pool[cnt]),
			multi_robot_goals[cnt],this->robot_namespaces[cnt],cnt));

		usleep(500);
	}

	for(int32_t cnt = 0 ; cnt < this->number_of_robots; cnt++)
	{
		multi_robot_thread_pool[cnt].join();
	}
}

vector<bool> StarLightMultiRobot::fetchGoalResults()
{
	return getGoalResults();
}

void StarLightMultiRobot::goalSendingThread(StarLightBase &base_goal_handler,
				turtlebot3_starlight::StarLightMultiRobotMessage goal_message,string robot_namespace,int32_t goal_index)
{

	if(base_goal_handler.connectActionServer())
	{
		ROS_INFO("Sending Goal to robot named : %s",robot_namespace.c_str());

		if(base_goal_handler.sendGoalToRobot(goal_message.x_axis_coordinate,goal_message.y_axis_coordinate,goal_message.yaw,
			robot_namespace.substr(0,robot_namespace.find("move_base"))))
		{
			ROS_INFO("Goal was Sent successfully to Robot named %s",robot_namespace.c_str());

			if(base_goal_handler.fetchLastGoalResult())
			{
				ROS_INFO("Multi Robot named %s goal was reached successfully by robot",robot_namespace.c_str());
				setGoalResults(goal_index,true);
			}
			else
			{
				ROS_ERROR("Robot named %s failed to reach destination.",robot_namespace.c_str());
				setGoalResults(goal_index,false);
			}
		}
		else
		{
			ROS_ERROR("Cannot send goal on action server for robot %s .Please check if Action server for receiving goal is started!",robot_namespace.c_str());
			setGoalResults(goal_index,false);
		}
	}
	else
	{
		ROS_ERROR("Action server connection failed for robot %s",robot_namespace.c_str());
		setGoalResults(goal_index,false);
	}
}
