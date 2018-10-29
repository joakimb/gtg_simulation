#! /bin/bash

echo $PATH
chown -R 1000:1000 /omnet
#export DEFAULT_WORKSPACE_ARGS="‐vmargs ‐Dos‐gi.instance.area.default=/workspace"
omnetpp 

while true; do echo "running container"; test $? -gt 128 && break; sleep 9; done


