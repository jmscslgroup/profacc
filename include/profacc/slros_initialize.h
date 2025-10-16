#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "profacc_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block profacc/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_profacc_std_msgs_Float64> Sub_profacc_1;

// For Block profacc/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_profacc_std_msgs_Float64> Sub_profacc_2;

// For Block profacc/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_profacc_std_msgs_Float64> Pub_profacc_9;

// For Block profacc/Get Parameter
extern SimulinkParameterGetter<real64_T, double> ParamGet_profacc_18;

// For Block profacc/Get Parameter1
extern SimulinkParameterGetter<real64_T, double> ParamGet_profacc_19;

void slros_node_init(int argc, char** argv);

#endif
