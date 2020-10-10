#include <geometry_msgs/Pose.h>
#include <starlight_lib/StarLightBase.h>

using namespace starlight_robotics;

bool StarLightBase::connectActionServer()
{
	//wait for the action server to come up
	while(!action_client.waitForServer(ros::Duration(ACTION_SERVER_WAITING_TIME)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	return action_client.isServerConnected();
}

bool StarLightBase::sendGoalToRobot(float x_axis_coordinate, float y_axis_coordinate, double robot_yaw,string frame_namespace)
{
	tf2::Quaternion robot_orientation;

	robot_orientation.setRPY(0.0,0.0,robot_yaw);

	robot_orientation = robot_orientation.normalize();

	move_base_msgs::MoveBaseGoal goal;

	goal.target_pose.pose.orientation = tf2::toMsg(robot_orientation);

	goal.target_pose.pose.position.x = x_axis_coordinate;
	goal.target_pose.pose.position.y = y_axis_coordinate;
	goal.target_pose.pose.position.z = 0.0;

	goal.target_pose.header.frame_id = frame_namespace + "map";
	goal.target_pose.header.stamp = ros::Time::now();
	
	ROS_INFO("Sending below shown goal to Robot");

	cout << goal << endl;

	action_client.sendGoal(goal);

	return action_client.waitForResult(ros::Duration(MAX_RESULT_WAIT_TIMEOUT));
}

bool StarLightBase::fetchLastGoalResult()
{
	if(action_client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("Robot successfully reached the destination!!");
		return true;
	}
	else
	{
		ROS_INFO("Robot failed to reach the goal due to some reason");
		return false;
	}
}