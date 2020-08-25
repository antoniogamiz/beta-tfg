#!/bin/bash

function progress {
    echo  "$1/$2"
}

[ ! -d "progress" ] && echo "Ray tracer is not running!" && exit

PROGRESS_DIR=progress

total_iterations=0
current_iterations=0

while :
do
  for entry in "$PROGRESS_DIR"/*
  do
    local_progress=($(awk '/./{line=$0} END{print line}' $entry))
    current_iterations=$(($current_iterations + ${local_progress[0]}))
    total_iterations=$(($total_iterations + ${local_progress[1]}))
  done


  clear
  progress $current_iterations $total_iterations
	sleep 1
done

