#! /bin/bash

#start sumo daemon
/workspace/veins-veins-4.7.1/sumo-launchd.py  -vv -c /usr/bin/sumo &

#start omnet
chown -R 1000:1000 /omnet
#export DEFAULT_WORKSPACE_ARGS="‐vmargs ‐Dos‐gi.instance.area.default=/workspace"
omnetpp 

#keep container alive
while true; do echo "running container"; test $? -gt 128 && break; sleep 9; done


