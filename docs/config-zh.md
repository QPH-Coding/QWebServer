# config.json详细介绍

- config.json的字段

| Field           | Type   | Description           |
| --------------- | ------ | --------------------- |
| port            | int    | 服务器监听的端口      |
| sub_reactor_num | int    | SubReactor的数量      |
| Thread_num      | int    | service thread的数量  |
| root            | string | 服务器使用的web根目录 |
| mysql           | object | MySql的配置           |

- MySql的配置字段

| Field    | Type   | Description                     |
| -------- | ------ | ------------------------------- |
| num      | int    | 初始化的MySql连接               |
| host     | string | MySql服务器使用的IP地址         |
| port     | int    | MySql服务器监听的端口           |
| database | string | server使用的在MySql里面的数据库 |
| username | string | 连接MySql使用的用户名           |
| password | string | 连接MySql使用的密码             |

