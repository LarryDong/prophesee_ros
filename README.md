# prophesee_ros

This is my own prophesee development code.

## prophesee_ros_wrapper
Forked from prophesee-ai.

```bash
# Run the driver: 
roslaunch prophesee_ros_driver prophesee_publisher.launch

# Run its own receiver
roslaunch prophesee_ros_driver prophesee_receiver.launch
```

### 注意事项：

1. 代码中是通过`camera_.cd().add_callback`调用publish的代码，实现callback的作用

2. 原代码通过`getNumSubscribers`判断有无接收这个event的node，所以不开接收节点时，它也不会发送数据（已注释掉）

3. launch文件中通过设定`event_delta_t`进行pub的频率控制，但并不精确。且频率过高时，ros设定的500的缓存区会满，导致数据丢失。暂时设置成1-10ms比较合理。



## prophesee_dev
自己写的一些代码。

```bash
rosrun prophesee_dev receiver
```
