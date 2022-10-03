#!/usr/bin bash

sudo mkdir -p /server/log
sudo mkdir -p /server/config

sudo cp ./config.json /server/config/config.json
sudo cp -r ./root /server