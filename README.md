# Guarding the Guards simulation
This repo contains code for simulating the overhead in the system described in our VNC2018 paper "Guarding the Guards: Accountable Authorities in VANETs
".

 * [Published version](https://ieeexplore.ieee.org/abstract/document/8628329)
 * [Preprint version](http://portal.research.lu.se/portal/files/53740796/LUP_gtg_short_3_.pdf) (free of charge)

The simulation implements the key dissemination protocol described in the paper. It is written in C++ and runs inside the Omnet++ simulator, using Veins to connect to SUMO.

For convinience and reproducibility, the environment is provided as a Dockerfile

## Prerequisites for running
### Installed Programs
docker

### Files
Download the omnet 5.4.1 linux zip into the project root dir (keep the naming omnetpp-5.4.1-src-linux.tgz)

## How To

### Build execution environment (builds a docker image)

    cd {project-dir}
    docker build -t omsim .

### Run execution environment (runs the image and launches omnet within it)

### Command line (launches simulation)

    docker run --env RUN_MODE=cmd -v "${PWD}"/code:/workspace omsim

### GUI (launches omnet GUI)

#### Linux

    xhost +local:docker
    cd {project-dir}
    docker run --net=host --cap-add SYS_ADMIN --env DISPLAY=$DISPLAY --volume="$HOME/.Xauthority:/root/.Xauthority:rw" -v "${PWD}"/code:/workspace --detach omsim

When omnet opens, and you are prompted to select a workspace, select:
    /workspace

<!---
[TODO is this still needed?]
fix paths for makemake according to fixpath.png

make clean (important)

build project
--->

Then run project by right-clicking dissemination -> simulations -> omnetpp.ini and selecting Run As -> Omnet++ simulation

#### OSX
Install xquarts, then:

    ip={your-ip}
    docker build -t omsim .
    /opt/X11/bin/xhost + $ip
    xhost + $ip
    docker run --net=host --cap-add SYS_ADMIN --env DISPLAY=$ip:0 --volume="/tmp/.X11-unix:/root/.Xauthority:rw" -v "${PWD}"/code:/workspace --detach omsim       \n

#### Windows
Configure an X server as described in:
http://somatorio.org/en/post/running-gui-apps-with-docker/

Then do as described for linux.

## Install guides 
If you don't want to use the supplied docker container and instead run the code native, use the following install guides:

https://omnetpp.org/doc/omnetpp/InstallGuide.pdf

http://veins.car2x.org/tutorial/

