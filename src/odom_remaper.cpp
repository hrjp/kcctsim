/**
* @file odom_remaper.cpp
* @brief twist_joy_selecter node
* @author Shunya Hara
* @date 2021.9.9
* @details コントローラーを使うかジョイスティックを使うかを選択する
*/

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

ros::Publisher odom_pub;
void odom_callback(const nav_msgs::Odometry& odom_msg_){
    nav_msgs::Odometry odom_msg=odom_msg_;
    odom_pub.publish(odom_msg);
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "odom_remaper");
    ros::NodeHandle n;
    //制御周期10Hz
    ros::Rate loop_rate(10);

    ros::NodeHandle lSubscriber("");

    ros::Subscriber odom_sub = lSubscriber.subscribe("/diff_drive_controller/odom", 50, odom_callback);

    //WayPointPath　publisher
    odom_pub = n.advertise<nav_msgs::Odometry>("/odom", 10);


    ros::spin();//subsucriberの割り込み関数はこの段階で実装される
  
    
    return 0;
}