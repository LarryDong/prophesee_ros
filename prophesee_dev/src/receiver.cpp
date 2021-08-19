
#include <iostream>
#include <mutex>

#include <prophesee_event_msgs/Event.h>
#include <prophesee_event_msgs/EventArray.h>

#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WIDTH 1280
#define HEIGHT 720


mutex m_eventsBuff;
vector<prophesee_event_msgs::EventArray> v_eventsBuff;


void eventsCallback(const prophesee_event_msgs::EventArray::ConstPtr &msg){
    // ROS_INFO("Events callbcak");
    m_eventsBuff.lock();
    v_eventsBuff.push_back(*msg);
    m_eventsBuff.unlock();
    ROS_INFO_STREAM("event callback. Received: " << msg->events.size());
}

void drawImage(void){

    vector<prophesee_event_msgs::EventArray> vEventArray;
    m_eventsBuff.lock();
    vEventArray.swap(v_eventsBuff);
    m_eventsBuff.unlock();

    vector<prophesee_event_msgs::Event> events;     // saved
    
    for(auto eventArray : vEventArray){
        // events.reserve(eventArray.events.size());
        for (auto e : eventArray.events){
            events.push_back(e);
        }
    }

    Mat event_img=Mat::zeros(Size(WIDTH, HEIGHT), CV_8UC1);
    event_img.setTo(128);
    for(auto e : events){
        uchar value = e.polarity == true ? 255 : 0;
        event_img.at<uchar>(e.y, e.x) = value;
    }
    imshow("src", event_img);
    ROS_INFO_STREAM("Draw func(). Processed: " << events.size());
    waitKey(1);
}


int main(int argc, char **argv) {

    ROS_INFO("Prophesee receiver begin");
    ros::init(argc, argv, "receiver");
    ros::NodeHandle nh;

    string topic_name="/prophesee/camera/cd_events_buffer";
    ros::Subscriber subEvent = nh.subscribe(topic_name,  100, eventsCallback);
    
    ros::Rate r(10);
    while (ros::ok()) {
        drawImage();
        ros::spinOnce();
        r.sleep();
    }

    return 0;
}
