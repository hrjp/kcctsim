# kcctsim
gazebo上でナビトンを動かすパッケージ
topicがハードウェアを動かす時と対応しているので実物と同じ感覚でシミュレーションが可能


## sim.launch

```bash
roslaunch kcctsim sim.launch
```

#### Subscribed Topics 

* cmd_vel ([geometry_msgs/Twist](http://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/Twist.html))
    * linear.xで並進速度[m/s] , angular.zで角速度[rad/s]を指定する
    * sim.launch内でtopic名をfinal_cmd_velに変更している



#### Published Topics
* scan1 ([sensor_msgs/LaserScan](http://docs.ros.org/en/api/sensor_msgs/html/msg/LaserScan.html))
    * front LiDAR
    * topic名変更はkcctsim/robots/naviton.urdf.xacro
* scan2 ([sensor_msgs/LaserScan](http://docs.ros.org/en/api/sensor_msgs/html/msg/LaserScan.html))
    * rear LiDAR
    * topic名変更はkcctsim/robots/naviton.urdf.xacro
* tf ([tf/tfMessage](http://docs.ros.org/en/api/tf/html/msg/tfMessage.html))
    * /odom -> /base_foot_point -> /base_link