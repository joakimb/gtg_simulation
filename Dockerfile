FROM ubuntu:latest
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

#install sumo
RUN apt install sumo=0.32.0+dfsg1-1 sumo-tools=0.32.0+dfsg1-1 sumo-doc=0.32.0+dfsg1-1 -y

#install omnet
RUN mkdir /omnet
COPY ./omnetpp-5.4.1-src-linux.tgz /omnet
RUN tar -xf /omnet/omnetpp-5.4.1-src-linux.tgz -C /omnet
RUN rm /omnet/omnetpp-5.4.1-src-linux.tgz

RUN apt update && apt install qt5-default -y
RUN apt update && apt install libopenscenegraph-dev openscenegraph -y
RUN apt update && apt install libosgearth-dev -y
ENV PATH="/omnet/omnetpp-5.4.1/bin:${PATH}"
RUN cd /omnet/omnetpp-5.4.1 && ./configure && make

ENV XDG_RUNTIME_DIR="/run/user/1000"
#ENTRYPOINT [ "sh", "-c", "/omnet/omnetpp-5.4.1/bin/omnetpp" ]
#CMD ["/omnet/omnetpp-5.4.1/bin/omnetpp" ]
COPY ./docker-entrypoint.sh /
ENTRYPOINT [ "/bin/bash", "/docker-entrypoint.sh" ]
