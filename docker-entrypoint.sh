#! /bin/bash

#start sumo daemon
/workspace/veins/sumo-launchd.py  -vv -c /usr/bin/sumo > /sumolog.txt 2>&1 &

#start omnet
chown -R 1000:1000 /omnet
#export DEFAULT_WORKSPACE_ARGS="‐vmargs ‐Dos‐gi.instance.area.default=/workspace"
#omnetpp

#run veins
cd artery/build && cmake --build . --target run_example -j 5

#keep container alive
while true; do echo "running container"; test $? -gt 128 && break; sleep 9; done


