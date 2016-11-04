#!/bin/bash

clear

# Install Dependencies
cd $HOME/cs4300-os161/docs/downloads
sudo dpkg -i ./libtinfo-dev*.deb 
sudo dpkg -i ./libncurses5-dev*.deb 
sudo dpkg -i ./libunistring0*.deb 
sudo dpkg -i ./gettext*.deb 
sudo dpkg -i ./texinfo*.deb

cd $HOME/cs4300-os161/docs/downloads
mkdir ../../temp
tar -xzf os161-binutils.tar.gz -C ../../temp