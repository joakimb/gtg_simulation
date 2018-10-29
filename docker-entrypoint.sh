#! /bin/bash

echo $PATH
chown -R 1000:1000 /omnet
omnetpp

while true; do echo "running container"; test $? -gt 128 && break; sleep 9; done


