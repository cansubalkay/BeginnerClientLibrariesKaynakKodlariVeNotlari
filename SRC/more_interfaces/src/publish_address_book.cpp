#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher()
  : Node("address_book_publisher")
  {
    address_book_publisher_ =
      this->create_publisher<more_interfaces::msg::AddressBook>("address_book", 10);

    auto publish_msg = [this]() -> void {
   auto msg = std::make_shared<more_interfaces::msg::AddressBook>();
   {
     rosidl_tutorials_msgs::msg::Contact contact;
     contact.first_name = "John";
     contact.last_name = "Doe";
     contact.phone_number = "1234567890";
     contact.phone_type = message.PHONE_TYPE_MOBILE;
     msg->address_book.push_back(contact);
   }
   {
     rosidl_tutorials_msgs::msg::Contact contact;
     contact.first_name = "Jane";
     contact.last_name = "Doe";
     contact.phone_number = "4254242424";
     contact.phone_type = message.PHONE_TYPE_HOME;
     msg->address_book.push_back(contact);
   }

   std::cout << "Publishing address book:" << std::endl;
   for (auto contact : msg->address_book) {
     std::cout << "First:" << contact.first_name << "  Last:" << contact.last_name <<
       std::endl;
   }

   address_book_publisher_->publish(*msg);
 };
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr address_book_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddressBookPublisher>());
  rclcpp::shutdown();

  return 0;
}
