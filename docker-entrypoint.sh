#! /bin/bash

echo $PATH
chown -R 1000:1000 /omnet
omnetpp

top -b
