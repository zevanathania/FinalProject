
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>


// ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
//             ("mavros/state", 10, state_cb);
// ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
//             ("mavros/setpoint_position/local", 10);

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;

const double x_min = 0.0;
const double y_min = 0.0;
const double x_max = 11.0;
const double y_max = 11.0;

const double pi = 3.14159265359;

void move(double speed, double distance, bool isForward)

void rotate(double angular_speed, double angle, bool clockwise)
{
    geometry_msgs::Twist vel_msg;

vel_msg.linear.x = 0;
vel_msg.linear.y = 0;
vel_msg.linear.z = 0;

vel_msg.angular.x = 0;
vel_msg.angular.y = 0;
if(clockwise)
    vel_msg.angular.z = -angular_speed;
else
    vel_msg.angular.z = angular_speed; 

double t0 = ros::Time::now().toSec();
double current_angle = 0;
ros::Rate loop_rate(10);

do
{
    velocity_publisher.publish(vel_msg) ;
    double t1 = ros::Time::now().toSec() ;
    current_angle = angular_speed * (t1-t0) ;
    ros::spinOnce () ;
    loop_rate.sleep() ; 

} while (current_angle < angle);

vel_msg.angular.z = 0.0;
velocity_publisher.publish(vel_msg);

}

int main(int argc, char **argv)
{
    double speed, angular_speed, angular_speed_degree;
    double distance, angle, angle_degree;
    bool isForward, clockwise; 

    ros::init(argc, argv, "fpb_node");
    ros::NodeHandle nh;

    velocity_publisher = nh.advertise<geometry_msgs::Twist> ("/turtle1/cmd_vel", 10);

    std::cout << "Enter the speed: ";
    std::cin >> speed;
    std::cout << "Enter the ditance: ";
    std::cin >> distance;
    std::cout << "Forward?";
    std::cin >> isForward;

    move(speed, distance, isForward);

    std::cout << "Enter angular speed:";
    std::cin >> angular_speed_degree;

    angular_speed = angular_speed_degree * 3.14/ 180;

    std::cout << "Enter desired angle:";
    std::cin >> angle_degree;

    angle = angle_degree *3.14/ 180;

    std::cout << "Clockwise?";
    std::cin >> clockwise;

    rotate(angular_speed,angle,clockwise);

    ros::spin();

    return 0;

}
   
