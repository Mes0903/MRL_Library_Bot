#include <ros/ros.h>
#include <std_msgs/Int32MultiArray.h>
#include <iostream>
#include <sstream>


int main(int argc, char **argv)
{
  ros::init::(argc, argv, "library_goal_setter");
  ros::NodeHandle n;
  ros::Publisher goal_pub = n.advertise<std_msgs::Int32MultiArray>("library_goal_setter", 1000);
  ros::Rate loop_rate(10);

  int _x{}, _y{};
  while (ros::ok()) {
    std_msgs::Int32MultiArray msg;
    std::cout << "Please input the x and y, separated by a space\n";
    std::cin >> _x >> _y;

    msg.data.push_back(_x);
    msg.data.push_back(_y);

    _x = 0, _y = 0;

    goal_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}