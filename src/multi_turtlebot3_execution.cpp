#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <starlight_lib/StarLightMultiRobot.h>
#include <turtlebot3_starlight/StarLightMultiRobotMessage.h>

using namespace std;

#define NUM_OF_ROBOTS (3)

int main(int argc, char** argv)
{
	ros::init(argc, argv, "starlight_multi_navigation");

	vector<string> robot_namespaces;

	robot_namespaces.push_back("/tb3_0/move_base");
	robot_namespaces.push_back("/tb3_1/move_base");
	robot_namespaces.push_back("/tb3_2/move_base");

	starlight_robotics::StarLightMultiRobot multirobot_goal_handler(NUM_OF_ROBOTS,robot_namespaces);

	vector<turtlebot3_starlight::StarLightMultiRobotMessage> robot_goal_message_vector;

	turtlebot3_starlight::StarLightMultiRobotMessage robot_goal;

	// First Robot goal coordinates
	robot_goal.x_axis_coordinate = -3.0;
	robot_goal.y_axis_coordinate = 1.0;
	robot_goal.yaw = 0.0;

	robot_goal_message_vector.push_back(robot_goal);

	// Second Robot goal coordinates
	robot_goal.x_axis_coordinate = -2.0;
	robot_goal.y_axis_coordinate = 1.0;
	robot_goal.yaw = 0.0;

	robot_goal_message_vector.push_back(robot_goal);

	// Third Robot goal coordinates
	robot_goal.x_axis_coordinate = -1.0;
	robot_goal.y_axis_coordinate = 1.0;
	robot_goal.yaw = 0.0;

	robot_goal_message_vector.push_back(robot_goal);

	multirobot_goal_handler.sendMultipleGoals(robot_goal_message_vector);

	// vector<bool> goal_results;

	// goal_results = multirobot_goal_handler.fetchGoalResults();

	// for(int32_t cnt = 0 ; cnt < NUM_OF_ROBOTS ; cnt++)
	// {
	// 	ROS_INFO("Robot named %s %s",robot_namespaces[cnt].c_str(),goal_results[cnt] ? "SUCCESS" : "FAILED");
	// }

	return 0;
}
