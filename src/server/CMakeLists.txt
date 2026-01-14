# 定义SRC_LIST变量, 包含该目录下所有源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)

# 创建ChatServer可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST})

# 添加依赖项
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient pthread)