#!/bin/bash

PROGRESS_DIR=progress

function progress {
    echo  "$1/$2"
}

[ ! -d $PROGRESS_DIR ] && echo "Ray tracer is not running!" && exit

while :
do
  [ ! -d $PROGRESS_DIR ] && echo "Ray tracer rendering has finished!" && exit

  total_iterations=0
  current_iterations=0

  for entry in "$PROGRESS_DIR"/*
  do
    if [ ! -s $entry ]; then
      continue
    fi
    local_progress=($(awk '/./{line=$0} END{print line}' $entry))
    current_iterations=$(($current_iterations + ${local_progress[0]}))
    total_iterations=$(($total_iterations + ${local_progress[1]}))
  done


  clear
  progress $current_iterations $total_iterations
	sleep 1
done

