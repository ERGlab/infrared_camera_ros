#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>
#include "camera_class.h"
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"infrared");
    ros::NodeHandle n;
    Mat img;
    int key;
    camera cam;
    cam.start_cam();
    ros::Rate loop_rate(20);
    sensor_msgs::Image image_msg;
    sensor_msgs::CameraInfo camera_info_msg;
    image_transport::ImageTransport main_cam_image(n);
    image_transport::CameraPublisher image_pub = main_cam_image.advertiseCamera("/hikrobot_infrared_camera/rgb", 1000);

    cv_bridge::CvImagePtr cv_ptr = boost::make_shared<cv_bridge::CvImage>();
    cv_ptr->encoding = sensor_msgs::image_encodings::BGR8;  // 就是rgb格式 

    while(ros::ok())
    {
        cam.get_pic(&img);  //获取图片
        if (img.empty())
        {
            continue;
        }
        cv_ptr->image = img;
        image_msg = *(cv_ptr->toImageMsg());
        // imshow("test",img);  //imshow图片
        // key=waitKey(1);  //
        // if(key==27)
        // {
        //     cam.close_cam();
        //     break;
        // }
        loop_rate.sleep();
        image_msg.header.stamp = ros::Time::now() ;
        image_msg.header.frame_id = "hikrobot_infrared_camera";

        camera_info_msg.header.frame_id = image_msg.header.frame_id;
        camera_info_msg.header.stamp = image_msg.header.stamp;

        image_pub.publish(image_msg, camera_info_msg);


    }
}

