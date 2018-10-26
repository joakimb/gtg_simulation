# Guarding the Guards simulation
This repo contains code for simulating the overhead created by [TODO insert paper link].

## Prerequisites
### Programs
docker

### Files
Download omnet zip in project root dir: omnetpp-5.4.1-src-linux.tgz
https://omnetpp.org/omnetpp/download/30-omnet-releases/2331-omnetpp-5-4-1-linux

## How To

### Command line
    docker run --env RUN_MODE=cmd -v "${PWD}"/code:/workspace omsim

### GUI

#### Linux
    docker build -t omsim .
    xhost +local:docker
    docker run --net=host --cap-add SYS_ADMIN --env DISPLAY=$DISPLAY --volume="$HOME/.Xauthority:/root/.Xauthority:rw" -v "${PWD}"/code:/workspace --detach omsim

When omnet opens, and you are prompted to select a workspace, select:
    /workspace

Add build paths as described in https://github.com/karim-emara/PREXT 
    /eigen
    /workspace/veins-veins-4.7.1/src/veins/modules/Prext/include

fix paths for makemake according to fixpath.png

make clean (important)

build project

[TODO make clearer how to]

#### OSX
Install xquarts, then:

    docker build -t omsim .
    /opt/X11/bin/xhost + $ip
    xhost + $ip
    docker run --net=host --cap-add SYS_ADMIN --env DISPLAY=$ip:0 --volume="/tmp/.X11-unix:/root/.Xauthority:rw" -v "${PWD}"/code:/workspace --detach omsim       \n

#### Windows
Configure an X server as described in:
http://somatorio.org/en/post/running-gui-apps-with-docker/

Then do as described for linux.

## Install guides 
If you don't want to use the supplied docker container:

https://omnetpp.org/doc/omnetpp/InstallGuide.pdf

http://veins.car2x.org/tutorial/

https://github.com/karim-emara/PREXT

# Links

http://sumo.dlr.de/wiki/Tutorials/Driving_in_Circles
https://github.com/burtonwilliamt/carlogicapi/tree/master/tutorials
