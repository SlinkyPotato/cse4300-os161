#!/bin/bash

clear

# Install Dependencies
cd $HOME/cs4300-os161/docs/downloads
sudo dpkg -i ./libtinfo-dev*.deb 
sudo dpkg -i ./libncurses5-dev*.deb 
sudo dpkg -i ./libunistring0*.deb 
sudo dpkg -i ./gettext*.deb 
sudo dpkg -i ./texinfo*.deb

# Install and Configure os161-binutils
cd $HOME/cs4300-os161/docs/downloads
mkdir ../../temp
tar -xzf os161-binutils.tar.gz -C ../../temp
sed -i "s/| egrep 'texinfo\[\^0-9\]\*(\[1-3\]\[0-9\]|4\\\.\[4-9\]|\[5-9\])' >\/dev\/null 2>&1; then/| egrep 'texinfo\[\^0-9\]\*(\[1-3\]\[0-9\]|4\\\.(\[4-9\]|\[1-9\]\[0-9\])|\[5-9\])' >\/dev\/null 2>\&1; then/" $HOME/cs4300-os161/temp/binutils-2.17+os161-2.0.1/configure

cd ../../temp/binutils-2.17+os161-2.0.1
./configure --nfp --disable-werror --target=mips-harvard-os161 --prefix=$HOME/sys161/tools
find . -name '*.info' | xargs touch
make
make install

mkdir $HOME/sys161/bin
export PATH=$HOME/sys161/bin:$HOME/sys161/tools/bin:$PATH
printenv PATH

# Install and Configure gcc-4.1.2+os161.2.0 
cd ../../docs/downloads
tar -xzf os161-gcc.tar.gz -C ../../temp/
sed -i "s/| egrep 'texinfo\[\^0-9\]\*(\[1-3\]\[0-9\]|4\\\.\[2-9\]|\[5-9\])' >\/dev\/null 2>&1; then/| egrep 'texinfo\[\^0-9\]\*(\[1-3\]\[0-9\]|4\\\.(\[2-9\]|\[1-9\]\[0-9\])|\[5-9\])' >\/dev\/null 2>\&1; then/" $HOME/cs4300-os161/gcc-4.1.2+os161-2.0/configure

cd ../../temp/gcc-4.1.2+os161-2.0
./configure -nfp --disable-shared --disable-threads --disable-libmudflap --disable-libssp --target=mips-harvard-os161 --prefix=$HOME/sys161/tools
make
make install

# Install and Configure os161-gdb
cd ../../docs/downloads
tar -xzf os161-gdb.tar.gz -C ../../temp/
sed -i "s/| egrep 'texinfo\[\^0-9\]\*(\[1-3\]\[0-9\]|4\\\.\[4-9\]|\[5-9\])' >\/dev\/null 2>&1; then/| egrep 'texinfo\[\^0-9\]\*(\[1-3\]\[0-9\]|4\\\.(\[4-9\]|\[1-9\]\[0-9\])|\[5-9\])' >\/dev\/null 2>\&1; then/" $HOME/cs4300-os161/gdb-6.6+os161-2.0/configure

cd ../../temp/gdb-6.6+os161-2.0
./configure --target=mips-harvard-os161 --prefix=$HOME/sys161/tools --disable-werror
make
make install

# Install and Configure sys161.1.99.05
cd ../../docs/downloads
tar -xzf sys161.tar.gz -C ../../temp/

cd ../../temp/sys161-1.99.05
./configure --prefix=$HOME/sys161 mipseb
make
make install

# Set Up Links for Toolchain Binaries
cd $HOME/sys161/tools/bin
sh -c 'for i in mips-*; do ln -s ../tools/bin/$i $HOME/sys161/bin/cs4300-`echo $i | cut -d- -f4-`; done'

cd $HOME/sys161
ln -s share/examples/sys161/sys161.conf.sample sys161.conf

cd bin && ls # show available tools

# Install OS161
cd $HOME/cs4300-os161/docs/downloads
tar -xzf os161.tar.gz -C $HOME/cs4300-os161/

# Configure Os161
cd $HOME/cs4300-os161/os161-1.11
./configure --ostree=$HOME/cs4300-os161/root --toolprefix=cs4300-

cd kern/conf
./config ASST0

cd ../compile/ASST0
make depend
make
make install

# Build OS 161
cd $HOME/cs4300-os161/os161-1.11
make

cd $HOME/cs4300-os161/root
cp $HOME/sys161/sys161.conf .

sys161 kernel-ASST0