#Guarding the Guards simulation
This repo contains code for simulating the overhead created by [TODO insert paper link].

##Prerequisites
###Programs
docker

###Files
Download omnet zip in project root dir: omnetpp-5.4.1-src-linux.tgz
https://omnetpp.org/omnetpp/download/30-omnet-releases/2331-omnetpp-5-4-1-linux

##How To

###Linux
    docker build -t omsim .
    xhost +local:docker
    docker run --net=host --cap-add SYS_ADMIN --env DISPLAY=$DISPLAY --volume="$HOME/.Xauthority:/root/.Xauthority:rw" -v "${PWD}"/code:/workspace --detach omsim

###Windows and OSX
Configure an X server as described in:
http://somatorio.org/en/post/running-gui-apps-with-docker/

Then do as described for linux.

##Install guides 
If you don't want to use the supplied docker container:
https://omnetpp.org/doc/omnetpp/InstallGuide.pdf
http://veins.car2x.org/tutorial/
https://github.com/karim-emara/PREXT
