#!/bin/sh

hdus=$(lsusb | grep 3275:6051)
hdp=$(lsusb | grep 3275:6081)

if [ -n "$hdus" ];then
    tuner="--hdus"
else
    if [ -n "$hdp" ];then
	tuner="--hdp"
    else
	echo "No HDUS or HDP found"
	exit 1
    fi
fi

$(dirname $0)/recfriio $tuner $@
