#include <laser_geometry/laser_geometry.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud.h>
#include <string.h>
#include <tf/transform_listener.h>
#include <boost/shared_ptr.hpp>
#include <sstream>

//#define RAD2DEG(x) ((x)*180./M_PI)
static ros::Publisher cloud_pub;
static laser_geometry::LaserProjection projector_;
static boost::shared_ptr<tf::TransformListener> plistener_;
void scanCallback(const sensor_msgs::LaserScan::ConstPtr &scan) {
  sensor_msgs::PointCloud2 cloud;
  printf(" call transformLaserScanToPointCloud !\n");
  projector_.transformLaserScanToPointCloud("laser", *scan, cloud, *plistener_);
  cloud_pub.publish(cloud);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "receive_laserscan_node");
  ros::NodeHandle n;
  ros::Subscriber sub =
      n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
  cloud_pub = n.advertise<sensor_msgs::PointCloud2>("/cloud2", 1);
  //此处的tf是 laser_geometry 要用到的
  plistener_ = boost::make_shared<tf::TransformListener>();
  plistener_->setExtrapolationLimit(ros::Duration(0.1));
  ros::spin();

  return 0;
}
