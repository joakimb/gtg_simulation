#! /bin/bash

#start sumo daemon
/workspace/veins/sumo-launchd.py  -vv -c /usr/bin/sumo > /sumolog.txt 2>&1 &

#start omnet
chown -R 1000:1000 /omnet
#export DEFAULT_WORKSPACE_ARGS="‐vmargs ‐Dos‐gi.instance.area.default=/workspace"

if [ "$RUN_MODE" = "gui" ]
then

  omnetpp

elif [ "$RUN_MODE" = "cmd" ]
then

  #build project
  cd workspace/veins
  ./configure
  make
  cd /workspace/dissemination
  make
  cd /workspace/dissemination/simulations
  #run it
  ../src/dissemination -m -u Cmdenv -n .:../src:../../veins/examples/veins:../../veins/src/veins --image-path=../../veins/images -l ../../veins/src/veins -c lustBatched -g omnetpp.ini #in batches
  
  #../src/dissemination -m -u Cmdenv -n .:../src:../../veins/examples/veins:../../veins/src/veins --image-path=../../veins/images -l ../../veins/src/veins -c lust omnetpp.ini #all at once
 
else

  exit 3;

fi

#keep container alive
while true; do echo "running container"; test $? -gt 128 && break; sleep 9; done


