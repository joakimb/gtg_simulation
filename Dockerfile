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
RUN apt update && apt install xvfb -y #fake x server to circumvent config warning

#fake display to circumvent config warning
ENV DISPLAY=:99 

##install omnet 5.2
#RUN mkdir /omnet
#COPY ./omnetpp-5.2-src-linux.tgz /omnet
#RUN tar -xf /omnet/omnetpp-5.2-src-linux.tgz -C /omnet
#RUN rm /omnet/omnetpp-5.2-src-linux.tgz
#ENV PATH="/omnet/omnetpp-5.2/bin:${PATH}"
#RUN Xvfb :99 -screen 0 640x480x8 -nolisten tcp &\
#    cd /omnet/omnetpp-5.2 && ./configure && make

#install omnet 5.4.1
RUN mkdir /omnet
COPY ./omnetpp-5.4.1-src-linux.tgz /omnet
RUN tar -xf /omnet/omnetpp-5.4.1-src-linux.tgz -C /omnet
RUN rm /omnet/omnetpp-5.4.1-src-linux.tgz
ENV PATH="/omnet/omnetpp-5.4.1/bin:${PATH}"
RUN Xvfb :99 -screen 0 640x480x8 -nolisten tcp &\
    cd /omnet/omnetpp-5.4.1 && ./configure && make

#install sumo
#RUN add-apt-repository -y ppa:sumo/stable && apt update && apt install -y sumo=0.25.0+dfsg1-2 sumo-tools=0.25.0+dfsg1-2 sumo-doc=0.25.0+dfsg1-2
RUN apt update && apt install -y sumo sumo-tools sumo-doc

#install eigen
RUN mkdir /eigen
RUN cd /eigen && wget http://bitbucket.org/eigen/eigen/get/3.3.5.zip && unzip 3.3.5.zip && rm 3.3.5.zip

#fixes for gui inside docker
ENV XDG_RUNTIME_DIR="/run/user/1000"

#install dependencies for debug
RUN apt update && apt install gdb -y

##install artery
RUN apt update && apt install git -y
RUN apt update && apt install geographiclib-tools -y
RUN apt update && apt install libgeographic14 -y
RUN apt update && apt install libgeographic-dev -y

RUN git clone --recursive https://github.com/riebl/artery.git

#install boost
RUN apt update && apt install wget -y
RUN wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
RUN tar xf boost_1_64_0.tar.gz
RUN apt update && apt install g++ -y
RUN apt update && apt install python python-dev -y
RUN cd boost_1_64_0 && ./bootstrap.sh --prefix=/usr/local # --with-libraries=atomic,chrono,container,context,coroutine,coroutine2,date_time,exception,fiber,filesystem,graph,graph_parallel,iostreams,locale,log,math,metaparse,mpi,program_options,python,random,regex,serialization,signals,system,test,thread,timer,type_erasure,wave 
RUN cd /boost_1_64_0 && ./b2 install --debug-configuration -d+2 -q

RUN rm -rf boost_1_64_0
RUN rm boost_1_64_0.tar.gz

##install cmake
RUN wget https://cmake.org/files/v3.13/cmake-3.13.0-Linux-x86_64.tar.gz
RUN tar xf cmake-3.13.0-Linux-x86_64.tar.gz
RUN cd cmake-3.13.0-Linux-x86_64 && cp -r bin /usr/ && cp -r share /usr/ && cp -r doc /usr/share/ && cp -r man /usr/share/

##install crypto++
RUN apt update && apt install libcrypto++-dev -y

#install artery
RUN cd artery/extern/vanetza && mkdir build && cd build && BOOST_ROOT="" BOOST_INCLUDEDIR="/usr/local" cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBoost_DEBUG=ON ..
RUN apt update && apt install python3 python3-dev python3-pip -y
RUN pip3 install pybind11
RUN cd /artery && make all
RUN cd /artery && mkdir build && cd build && cmake .. 
RUN ls -la /artery
RUN cd /artery/build && cmake .. &&  cmake --build .
#ENV DISPLAY=:98 
#RUN Xvfb :98 -screen 0 640x480x8 -nolisten tcp &\
#RUN cd artery/build && cmake --build . --target run_example -j 5


#runscript that starts omnet
COPY ./docker-entrypoint.sh /
ENTRYPOINT [ "/bin/bash", "/docker-entrypoint.sh" ]
