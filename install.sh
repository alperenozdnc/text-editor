#!/bin/bash

clear
echo "building txtedt..."
make build

echo "moving to binaries folder..."
echo "(this will require sudo. i would check a script that requires sudo before running if i were you)"
sudo mv ./txtedt /usr/bin/txtedt
