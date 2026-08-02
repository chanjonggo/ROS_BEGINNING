#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    //1. 파라미터가 어떤 설정을 가지는가 정의
    this->declare_parameter("my_parameter", "world");

    auto timer_callback = [this](){
      //2. 파라미터 현재값 체크 방법
      std::string my_param = this->get_parameter("my_parameter").as_string();

      RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

      //3. 신규 파라미터 적용
      if (++m_nCnt > 5) {
        my_param = "change world";
      }
      
      std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", my_param.c_str())};
      //std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
      this->set_parameters(all_new_parameters);
    };
    timer_ = this->create_wall_timer(1000ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  int m_nCnt = 0;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}