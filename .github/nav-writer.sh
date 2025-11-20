#!/usr/bin/bash

set -ex

echo "Arguments: $*"
IFS=';'
for project in $@; do
  echo $project
  dir="$BASEDIR/$(basename $project)"
  mkdir -p $dir
  echo " * [PCB]($project/top.png)" > $dir/nav.md
done