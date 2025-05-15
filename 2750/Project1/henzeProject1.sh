#!/bin/bash
#Adam Henze
#cs2750
#project1
#introduction to basic bash scripts and assignment submission

echo "Name of Script: "$0
echo "Name of Directory: "$PWD
echo "Name of UNIX Machine: "$HOSTNAME
echo "Name of Login Shell: "$SHELL
echo "Number of users on system: "$(w -h | wc -l)
echo "Current time: "$(date)

