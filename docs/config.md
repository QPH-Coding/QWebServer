# Config

`QWebServer` configure through a file `config.json`. 

The default path to read this file is `/server/config/config.json`.

If you want to change the config path and log path. You should read and modify the source code in `src/config/config.h`. And change the command in `install.sh`.

## Description of config.json

- The field of the config.json

| Field           | Type   | Description                |
| --------------- | ------ | -------------------------- |
| port            | int    | the port server used       |
| sub_reactor_num | int    | the num of SubReactor      |
| Thread_num      | int    | the num of service thread  |
| root            | string | the server web's root      |
| mysql           | object | the configuration of mysql |

- The field of the mysql config

| Field    | Type   | Description                              |
| -------- | ------ | ---------------------------------------- |
| num      | int    | the num of initial MySql-Connection      |
| host     | string | the IP address of the MySql-Server       |
| port     | int    | the port of the MySql-Server listened    |
| database | string | the database of the server used in MySql |
| username | string | the username used to connect to MySql    |
| password | string | the password used to connect to MySql    |

