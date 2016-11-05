#!/bin/bash

clear

export PATH=$HOME/sys161/bin:$HOME/sys161/tools/bin:$PATH

echo "os161 is being rebuilt."

cd kern/conf
./config ASST0

cd ../compile/ASST0
make depend
make
make install

cd $HOME/cs4300-os161/os161-1.11
make

echo "os161 finished building. You may now run script run.sh"