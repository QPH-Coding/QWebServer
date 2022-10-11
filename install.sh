#!/usr/bin/bash

if [ $# -eq 1 ]
then
  project_user=$1
else
  echo "Error: Please input the username"
  exit
fi

mkdir -p /server/log
mkdir -p /server/config
cp ./config.json /server/config/config.json
cp -r ./root /server

chown -R "$project_user" /server