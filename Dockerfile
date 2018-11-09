#requires xenial because of bug: https://bugs.launchpad.net/ubuntu/+source/qtbase-opensource-src/+bug/1774739
FROM ubuntu:xenial
ENV DEBIAN_FRONTEND noninteractive 

#install dependencies
RUN apt update && apt install build-essential -y
RUN apt update && apt install gcc -y
RUN apt update && apt install g++ -y
RUN apt update && apt install bison -y
RUN apt update && apt install flex -y
RUN apt update && apt install perl -y
RUN apt update && apt install tcl-dev -y
RUN apt update && apt install tk-dev -y
RUN apt update && apt install blt -y
RUN apt update && apt install libxml2-dev -y
RUN apt update && apt install zlib1g-dev -y
RUN apt update && apt install default-jre -y
RUN apt update && apt install doxygen -y
RUN apt update && apt install graphviz -y
RUN apt update && apt install libwebkitgtk-1.0-0 -y
RUN apt update && apt install openmpi-bin -y
RUN apt update && apt install libopenmpi-dev -y
RUN apt update && apt install libpcap-dev -y
RUN apt update && apt install autoconf -y
RUN apt update && apt install automake -y
RUN apt update && apt install libtool -y
RUN apt update && apt install libproj-dev -y
RUN apt update && apt install libfox-1.6-dev -y
RUN apt update && apt install libgdal-dev -y
RUN apt update && apt install libxerces-c-dev -y
RUN apt update && apt install qt4-dev-tools -y
RUN apt update && apt install qt5-default -y
RUN apt update && apt install libopenscenegraph-dev openscenegraph -y
RUN apt-get install software-properties-common -y 
RUN add-apt-repository ppa:ubuntugis/ppa -y
RUN apt update && apt install libosgearth-dev -y
RUN apt update && apt install libdrm-dev -y
RUN apt update && apt install wget unzip -y

#install omnet
RUN mkdir /omnet
COPY ./omnetpp-5.4.1-src-linux.tgz /omnet
RUN tar -xf /omnet/omnetpp-5.4.1-src-linux.tgz -C /omnet
RUN rm /omnet/omnetpp-5.4.1-src-linux.tgz
ENV PATH="/omnet/omnetpp-5.4.1/bin:${PATH}"
#begin ugly workaround for verison conflict, basically import cxmlelement->tostr from omnet 5.0 to 5.4.1 (https://groups.google.com/forum/#!topic/omnetpp/6iZhpyg9vlQ)
COPY ./cxmlelement.h /omnet/omnetpp-5.4.1/include/omnetpp/cxmlelement.h
COPY ./cxmlelement.cc /omnet/omnetpp-5.4.1/src/sim/cxmlelement.cc
# end workaround
RUN cd /omnet/omnetpp-5.4.1 && ./configure && make

#install sumo
RUN add-apt-repository -y ppa:sumo/stable && apt update && apt install -y sumo=0.25.0+dfsg1-2 sumo-tools=0.25.0+dfsg1-2 sumo-doc=0.25.0+dfsg1-2

#install eigen
RUN mkdir /eigen
RUN cd /eigen && wget http://bitbucket.org/eigen/eigen/get/3.3.5.zip && unzip 3.3.5.zip && rm 3.3.5.zip

#fixes for gui inside docker
ENV XDG_RUNTIME_DIR="/run/user/1000"

#runscript that starts omnet
COPY ./docker-entrypoint.sh /
ENTRYPOINT [ "/bin/bash", "/docker-entrypoint.sh" ]
