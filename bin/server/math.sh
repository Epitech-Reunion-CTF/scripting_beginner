#!/bin/bash


rm fifou 2>/dev/null
mkfifo fifou


socat - TCP-LISTEN:2234,fork,reuseaddr < fifou | ./script.sh 1> fifou
