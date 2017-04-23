#!/bin/bash

for executable in ./*.out; do
    $executable
    read -n1 -s -p "Press any key to continue"
    echo -e "\n\n"
done
