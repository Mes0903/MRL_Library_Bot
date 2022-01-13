#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>
#include <iostream>
#include <string>

using MoveBaseClient = actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while (!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";    //"map" for global frame. "base_link" for local frame;
  goal.target_pose.header.stamp = ros::Time::now();

  //ros::NodeHandle n;
  //ros::Subscriber sub = n.subscribe("library_goal_setter", 1000, [&goal, &ac](const std_msgs::Int32MultiArray::ConstPtr &msg) {
  //});

  std::string __target;

  while (ros::ok()) {
    bool __invalid_input = false;
    goal.target_pose.pose.orientation.w = 1.0;    //Quaternion

    do {
      std::cout << "Please input the position you wanna go.\nThere are A, B and C, three points, input \"exit\" to kill this process\n> ";
      getline(std::cin, __target);

      if (__target == "A" || __target == "a") {
        goal.target_pose.pose.position.x = 0.0;
        goal.target_pose.pose.position.y = 0.0;
      }
      else if (__target == "B" || __target == "b") {
        goal.target_pose.pose.position.x = 0.3;
        goal.target_pose.pose.position.y = 0.3;
      }
      else if (__target == "C" || __target == "c") {
        goal.target_pose.pose.position.x = -0.3;
        goal.target_pose.pose.position.y = -0.3;
      }
      else if (__target == "exit") {
        return 0;
      }
      else {
        ROS_WARN("Unvalid Input");
        __invalid_input = false;
      }

      __target.clear();
    } while (__invalid_input);

    ROS_INFO("Sending goal...");

    ac.sendGoalAndWait(goal, ros::Duration(40.0, 0), ros::Duration(40.0, 0));
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Goal arrived!");
    else
      ROS_INFO("The base failed to move to goalfor some reason");
  }

  return 0;
}