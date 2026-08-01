

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

3. 패키지의 생성과 빌드

패키지 최초 생성시에 ros2 pkg create --build-type ament_cmake --license Apache-2.0 --node-name my_node my_package 명령을 사용

이후 빌드시에는 colcon build --packages-select my_package 형태로 빌드함

다만 주의할 건 src 밑에 패키지를 두는게 범용적으로 보임


4. ROS의 개발 철학(gpt답변)

사용자분이 기존 C++/시스템 개발 경험이 있어서 낯선 지점은 정확히 여기입니다.
기존 사고:
"객체의 상태와 실행 순서는 내가 관리한다"
ROS2 사고:
"나는 반응 규칙을 등록하고, 실행 순서는 middleware/executor가 관리한다" 입니다.

이게 로봇 분야에서는 특히 중요합니다. 센서, 네트워크, 제어 루프가 동시에 돌아가기 때문에 사람이 
직접 main loop로 관리하는 방식은 규모가 커지면 유지가 어려워집니다.

ps : lamda를 사용한 콜백 개념, 함수 객체를 ros에 던지는 형태의 생명주기 관리
약간 안드로이드 앱 스타일 같기도 하고
*/

5. share_ptr의 많은 사용 부분

Node 생성시에 shared_ptr이 많이 쓰이게 된다.
이걸 어떻게 관리할지부터 고려해야 하는 게 참 빡세긴 할듯?
최상위 -> unique_ptr -> 하위 node에서 shared_ptr 일부 이런식이 일반적이겠지만
실제로 shared_ptr이 얼마나 참조될지 만든 후에는 장담을 할수가 없다.
weak_ptr로 만드는 경우에는 참조하는 객체의 생존을 보장할수가 없고 어렵네

6. 빌드할 src 위에서 의존성 검사 명령
rosdep install -i --from-path src --rosdistro lyrical -y

7. 전체 빌드
빌드 colcon -> 새 터미널 install의 source install/setup.bash-> 실행