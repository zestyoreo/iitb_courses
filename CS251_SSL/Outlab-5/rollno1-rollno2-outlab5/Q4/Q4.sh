#!/bin/bash
inp_file=$1
start_time=$2
end_time=$3

hey()
{
    echo $start_time
    return $1
}
awk '{print hey $1}' $inp_file