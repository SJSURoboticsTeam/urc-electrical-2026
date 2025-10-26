#!/usr/bin/sh

set -euo pipefail
40Vservo/40Vservo;drive/drive;main_arm/main_arm;HUB/HUB;Science/Science;POE/POE;bldc/bldc

IFS=';'
for project in $@; do
  dir=$(basename $project)
  echo " * [PCB]($dir/top.png)" > $BASEDIR/$dir/nav.md
done