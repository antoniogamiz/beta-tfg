#!/bin/bash

function progress {
    echo  " $1/$2"
}

PROGRESS_DIR=progress

total_iterations=0
current_iterations=0

for entry in "$PROGRESS_DIR"/*
do
  local_progress=($(awk '/./{line=$0} END{print line}' $entry))
  current_iterations=$(($current_iterations+${local_progress[0]}))
  total_iterations=$(($total_iterations+${local_progress[1]}))
done

progress $current_iterations $total_iterations
