

 # ROS_BEGINNING
 
1. wsl 환경하에서 한영 전환 입력시 fcitx5 입력

2. ~/.bashrc에 등록할 명령어

source ~/ros2_lyrical/install/local_setup.bash
source /etc/profile.d/colcon_cd.sh

function ros_build()
{
    colcon build --symlink-install
    source install/local_setup.bash
}

function ros_rebuild()
{
    echo "remove before build"
    rm -rf ./build ./install ./log
    colcon build --symlink-install
    source install/local_setup.bash
}

* 주의점 
sudo apt install 로 ros2를 설치한 경우 /opt/ros/lyrical/setup.bash 가 언더레이가 되나 나처럼 전체빌드를 한 경우 거기를 언더레이로 잡는게 맞다