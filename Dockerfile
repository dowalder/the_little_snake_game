FROM ubuntu:18.04

RUN apt-get update && apt install -y --no-install-recommends \ 
    git g++ cmake libghc-x11-xft-dev libxcursor-dev \
    && rm -rf /var/lib/apt/lis

RUN mkdir /opt/snake
WORKDIR /opt/snake

COPY . /opt/snake

RUN mkdir build && cd build && cmake .. && make