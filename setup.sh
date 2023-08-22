#!/bin/sh
apt install -y cmake pkg-config mesa-utils freeglut3-dev mesa-common-dev python3 python3-glad libopengl-dev libglfw3-dev libspdlog-dev
glad --profile compatibility --out-path vendor/glad --generator c