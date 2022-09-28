#!/bin/bash
filename=$(basename "$1")
wget -q --reject=html,tmp --no-parent --no-host-directories --cut-dirs=$2 -r $1
if [ $filename != "mock_grading" ]
then
    mv $filename mock_grading
    rm -rf $filename
fi   