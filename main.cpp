#include <iostream>
#include <ros/ros.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <yaml-cpp/yaml.h>
#include "include/DataIO/ReadBag.h"
int main(int argc, char **argv) {
    //std::cout << "cfg path" <<argv[1]<< std::endl;
    YAML::Node config = YAML::LoadFile("/home/echo/CLionProjects/DataSetBagRecord/cfg/cfg.yaml");
    ReadBag rb;
    std::cout<<config["bagPath"].as<std::string>()<<std::endl;
    std::cout<<config["LiDARType"].as<std::string>()<<std::endl;
    std::cout<<config["LiDARTopic"].as<std::string>()<<std::endl;
    std::cout<<config["cameraType"].as<std::string>()<<std::endl;
    std::cout<<config["cameraTopicL"].as<std::string>()<<std::endl;
    std::cout<<config["cameraTopicR"].as<std::string>()<<std::endl;
    std::cout<<config["IMUType"].as<std::string>()<<std::endl;
    std::cout<<config["IMUTopic"].as<std::string>()<<std::endl;
    std::cout<<config["GPSTopic"].as<std::string>()<<std::endl;
    std::cout<<config["savePath"].as<std::string>()<<std::endl;
    if(config["LiDARType"].as<std::string>() == "velodyne"){
        std::string folderPath;
        folderPath = config["savePath"].as<std::string>()+"/pcd";
        if (0 != access(folderPath.c_str(), 0))
        {
            mkdir(folderPath.c_str(),0777);
        }
        rb.readVLP16(config["bagPath"].as<std::string>(),folderPath );
    }
    return 0;
}
