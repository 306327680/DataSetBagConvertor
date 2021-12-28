#include <iostream>
#include <ros/ros.h>
#include <yaml-cpp/yaml.h>

int main(int argc, char **argv) {
    std::cout << "cfg path" <<argv[1]<< std::endl;
    YAML::Node config = YAML::LoadFile("/home/echo/CLionProjects/DataSetBagRecord/cfg/cfg.yaml");

    return 0;
}
