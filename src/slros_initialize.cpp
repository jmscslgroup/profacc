#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "profacc";

// For Block profacc/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_profacc_std_msgs_Float64> Sub_profacc_1;

// For Block profacc/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_profacc_std_msgs_Float64> Sub_profacc_2;

// For Block profacc/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_profacc_std_msgs_Float64> Pub_profacc_9;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

