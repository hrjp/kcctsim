/**
* @file twist_joy_selecter.cpp
* @brief twist_joy_selecter node
* @author Shunya Hara
* @date 2021.9.9
* @details コントローラーを使うかジョイスティックを使うかを選択する
*/

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

geometry_msgs::Twist cmd_vel;
void cmd_callback(const geometry_msgs::Twist& cmd_vel_){
    cmd_vel=cmd_vel_;
}

geometry_msgs::Twist joy_cmd_vel;
bool use_joy=false;
void joy_callback(const sensor_msgs::Joy& joy_msg){
    if(joy_msg.axes.size()>3){
        joy_cmd_vel.linear.x =joy_msg.axes[1];
        joy_cmd_vel.linear.y =joy_msg.axes[0];
        joy_cmd_vel.angular.z=joy_msg.axes[3];
    }
    if(joy_msg.buttons.size()>9){
        if(joy_msg.buttons.at(8)){
            use_joy=true;
        }
        if(joy_msg.buttons.at(9)){
            use_joy=false;
        }
    }
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "twist_joy_selecter");
    ros::NodeHandle n;
    //制御周期10Hz
    ros::Rate loop_rate(10);

    ros::NodeHandle lSubscriber("");

    //cmd_vel subscliber
    ros::Subscriber cmd_sub = lSubscriber.subscribe("cmd_vel", 50, cmd_callback);
    //joy subscliber
    ros::Subscriber joy_sub = lSubscriber.subscribe("joy", 50, joy_callback);

    //WayPointPath　publisher
    ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("/diff_drive_controller/cmd_vel", 10);


    //param setting
    ros::NodeHandle pn("~");

    while (n.ok())  {
        if(use_joy){
            cmd_pub.publish(joy_cmd_vel);
        }
        else{
            cmd_pub.publish(cmd_vel);
        }
        
        ros::spinOnce();//subsucriberの割り込み関数はこの段階で実装される
        loop_rate.sleep();
        
    }
    
    return 0;
}