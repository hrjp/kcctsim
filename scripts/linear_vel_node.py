#!/usr/bin/env python
import rospy
from nav_msgs.msg import Odometry
from std_msgs.msg import Float32

pub = rospy.Publisher("/robot_linear_vel", Float32, queue_size = 10)
def callback(data):
    pubdata=Float32()
    pubdata.data=data.twist.twist.linear.x*3.6
    pub.publish(pubdata)

if __name__ == '__main__':
    rospy.init_node('linear_vel_node', anonymous=True)
    rospy.Subscriber("/diff_drive_controller/odom", Odometry, callback)
    rospy.spin()