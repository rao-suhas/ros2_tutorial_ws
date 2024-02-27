#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
from example_interfaces.srv import SetBool


class NumberCounter(Node):

    def __init__(self):
        super().__init__("number_counter")
        self.counter_ = 0
        self.publisher_ = self.create_publisher(Int64, "number_count", 10)
        self.subscriber_ = self.create_subscription(Int64, "number", self.callback_count_numbers, 10)
        self.server_ = self.create_service(SetBool, "reset_counter", self.callback_reset_counter)
        self.get_logger().info("Number counter node started")

    def callback_count_numbers(self, msg):
        if msg.data != None:
            self.counter_ += msg.data
            counter_msg = Int64()
            counter_msg.data = self.counter_
            self.get_logger().info(str(self.counter_))
            self.publisher_.publish(counter_msg)

    def callback_reset_counter(self, request, response):
        if request.data:
            self.counter_ = 0
            response.success = True
            response.message = "Counter initialized to 0"
            self.get_logger().info("Counter initialized to 0")
        else:
            response.success = False
            response.message = "Counter not initialized to 0"
        return response

def main(args=None):
    rclpy.init(args=args)
    node = NumberCounter()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()