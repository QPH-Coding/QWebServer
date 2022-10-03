#!/usr/bin bash

mkdir -p /server/log
mkdir -p /server/config

cp ./config.json /server/config/config.json
cp -r ./root /server