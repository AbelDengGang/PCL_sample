#include <sstream>
#include <string.h>

#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

//#define RAD2DEG(x) ((x)*180./M_PI)
void scanCallback(const sensor_msgs::LaserScan::ConstPtr &scan) {
  int count = scan->scan_time / scan->time_increment;
  printf("[RPLIDAR INFO]: I heard a laser scan %s[%d]:\n",
         scan->header.frame_id.c_str(), count);
  printf("[RPLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min),
         RAD2DEG(scan->angle_max));

  for (int i = 0; i < count; i++) {
    float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
    printf("[RPLIDAR INFO]: angle-distance : [%f, %f]\n", degree,
           scan->ranges[i]);
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "receive_laserscan_node");
  ros::NodeHandle n;
  ros::Subscriber sub =
      n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
  ros::spin();

  return 0;
}
