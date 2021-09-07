#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

pub = rospy.Publisher("/diff_drive_controller/cmd_vel", Twist, queue_size = 10)
def callback(data):
    pub.publish(data)

if __name__ == '__main__':
    rospy.init_node('twist_remapper', anonymous=True)
    rospy.Subscriber("/cmd_vel", Twist, callback)
    rospy.spin()