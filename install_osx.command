#!/bin/bash
cd "$( dirname "$0" )"

effects=~/Library/Application\ Support/REAPER/Effects
if [ ! -d "$effects" ]; then exit 1; fi

cp -i -R Tale "$effects"
