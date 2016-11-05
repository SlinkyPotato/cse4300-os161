#OS 161 v1.11

This is the main OS for UConn's CSE 4300 Operating System Class. Instructions are provided below and within `docs`.

## Simple Installation

Installation has been greatly simplified and should take several minutes. Simply pull the repo to your `$HOME` directory and enable execution for the following three scripts: `install.sh`, `rebuild.sh`, `run.sh`, followed by running the install script.

```bash
cd $HOME/cs4300-os161
chmod u+x install.sh | chmod u+x rebuild.sh | chmod u+x run.sh
./install.sh
```

On success you should be brought to the OS161 kernel command prompt.

![OS 161 Kernel](http://i.imgur.com/qMi874C.png)

## Manual Installation 

### Pre-Install
All the necessary download dependencies are located under `docs/downloads`. Download links to the dependenices are also provided below.

**Step 1:** Assuming you are using Windows, download [VirtualBox](https://www.virtualbox.org/wiki/Downloads) (or any virtual machine software) for Windows hosts x86/amd64. Instructions for installing Virtual box are provided under `docs/`.

**Step 2:** Once you finish installing virtual box, Download Ubuntu v11.10 from the following link (Please install this specific version to avoid incompatibility issues with OS161 v1.11. Choose not to update Linux while installing. Please note that this specific version is not supported anymore, which is fine.)
	[ubuntu-11.10-desktop-i386.iso](http://www.engr.uconn.edu/$HOMEmok11002/public_html/ubuntu-11.10-desktop-i386.iso)

**Step 3:** Install Ubuntu on the virtual machine.

**Step 4:** Once Ubuntu is installed on the virtual machine, turn on Ubuntu and set up your own user profile. Make sure the following files are located under `docs/downloads`, if there are not, please download:

* [gettext_0.18.1.1-3ubuntu1_i386.deb](http://www.engr.uconn.edu/$HOMEmok11002/public_html/gettext_0.18.1.1-3ubuntu1_i386.deb)
* [libncurses5-dev_5.9-1ubuntu5_i386.deb](http://www.engr.uconn.edu/$HOMEmok11002/public_html/libncurses5-dev_5.9-1ubuntu5_i386.deb)
* [libtinfo-dev_5.9-1ubuntu5_i386.deb](http://www.engr.uconn.edu/$HOMEmok11002/public_html/libtinfo-dev_5.9-1ubuntu5_i386.deb)
* [libunistring0_0.9.3-4_i386.deb](http://www.engr.uconn.edu/$HOMEmok11002/public_html/libunistring0_0.9.3-4_i386.deb)
* [texinfo_4.13a.dfsg.1-8ubuntu1_i386.deb](http://www.engr.uconn.edu/$HOMEmok11002/public_html/texinfo_4.13a.dfsg.1-8ubuntu1_i386.deb)

The files should now be located within `docs/downloads`. Please install package files as shown:

```bash
cd $HOME/cs4300-os161/docs/downloads
sudo dpkg -i ./libtinfo-dev*.deb 
sudo dpkg -i ./libncurses5-dev*.deb 
sudo dpkg -i ./libunistring0*.deb 
sudo dpkg -i ./gettext*.deb 
sudo dpkg -i ./texinfo*.deb
```

### Install Dependencies

**Step 1:** Make sure the following files are located under `docs/downloads`, if not please download:

* [os161.tar.gz]
* [os161-binutils.tar.gz]
* [os161-gcc.tar.gz]
* [os161-gdb.tar.gz]
* [sys161.tar.gz]

**Step 2:** Build and Install the Binary Utilities (Binutils)

Unpack the binutils archive by executing the following command from within `docs/downloads` folder: 

```bash
cd $HOME/cs4300-os161/docs/downloads
mkdir ../../temp
tar -xzf os161-binutils.tar.gz -C ../../temp
```

Next, in `temp/binutils-2.17+os161-2.0.1/configure`. Insert `(` before `[4-9]|`, and insert `[1-9][0-9])|` in between `[4-9]|` and `[5-9])` at the following:

`| egrep 'texinfo[^0-9]*([1-3][0-9]|4\.[4-9]|[5-9])' >/dev/null 2>&1; then`

to

`| egrep 'texinfo[^0-9]*([1-3][0-9]|4\.([4-9]|[1-9][0-9])|[5-9])' >/dev/null 2>&1; then`


Next, move into the newly-created directory and configure binutils:

```bash
cd ../../temp/binutils-2.17+os161-2.0.1
./configure --nfp --disable-werror --target=mips-harvard-os161 --prefix=$HOME/sys161/tools
find . -name '*.info' | xargs touch
make 					# make the binutils
make install			# this will create $HOME/sys161/temp and populate it
```

There should now be bin utilities located at `$HOME/sys161/tools` which will be used by the simulator.

**Step 3:** Adjust Your Shell's Command Path

First, make the directory in which your shell will eventually find the toolchain binaries: 

```bash
mkdir $HOME/sys161/bin
```

The following command will only **temporarily** add the bin tools to your PATH. You will need to re-execute this command if you reboot Ubuntu or 
open a new shell:

```bash
export PATH=$HOME/sys161/bin:$HOME/sys161/tools/bin:$PATH
```

**Setting these variables only work in the shell or window where you execute the above commands.** 

You may need to log out and log back in again so that this PATH change will take effect. You can check the current settings of the PATH environment variable using the command

```bash
printenv PATH
```

**Step 4:** Install the GCC MIPS Cross-Compiler

Unpack the gcc archive by executing the following command inside your `docs/downloads` folder:

```bash
cd ../../docs/downloads
tar -xzf os161-gcc.tar.gz -C ../../temp/
```

In `gcc-4.1.2+os161-2.0/configure` insert `(` before `[2-9]|` and insert `[1-9][0-9])|` in between `[2-9|]` and `[5-9])` at the following:

`| egrep 'texinfo[^0-9]*([1-3][0-9]|4\.[2-9]|[5-9])' >/dev/null 2>&1; then`

to

`| egrep 'texinfo[^0-9]*([1-3][0-9]|4\.([2-9]|[1-9][0-9])|[5-9])' >/dev/null 2>&1; then`

Move into the newly-created directory and configure gcc: 

```bash
cd ../../temp/gcc-4.1.2+os161-2.0
./configure -nfp --disable-shared --disable-threads --disable-libmudflap --disable-libssp --target=mips-harvard-os161 --prefix=$HOME/sys161/tools
make
make install
```

**Step 5:** Install GDB

Unpack the gdb archive by executing the following command inside `docs/downloads` folder: 

```bash
cd ../../docs/downloads
tar -xzf os161-gdb.tar.gz -C ../../temp/
```

In `gdb-6.6+os161-2.0/configure` insert `(` before `[4-9]|` and insert `[1-9][0-9])|` in between `[4-9]|` and `[5-9]` at the following: 

`| egrep 'texinfo[^0-9]*([1-3][0-9]|4\.[4-9]|[5-9])' >/dev/null 2>&1; then`

to

`| egrep 'texinfo[^0-9]*([1-3][0-9]|4\.([4-9]|[1-9][0-9])|[5-9])' >/dev/null 2>&1; then`

Move into the newly-created directory and configure: 

```bash
cd ../../temp/gdb-6.6+os161-2.0
./configure --target=mips-harvard-os161 --prefix=$HOME/sys161/tools --disable-werror
make
make install
```

### Build and Install sys161 Simulator

Unpack the sys161 archive by executing the following command inside `docs/downloads`: 

```bash
cd ../../docs/downloads
tar -xzf sys161.tar.gz -C ../../temp/

cd ../../temp/sys161-1.99.05
./configure --prefix=$HOME/sys161 mipseb
make
make install
```

**Step 1:** Set Up Links for Toolchain Binaries

Go into the `$HOME/sys161/tools` directory and install as shown:

```bash
cd $HOME/sys161/tools/bin
sh -c 'for i in mips-*; do ln -s ../tools/bin/$i $HOME/sys161/bin/cs4300-`echo $i | cut -d- -f4-`; done'

cd $HOME/sys161
ln -s share/examples/sys161/sys161.conf.sample sys161.conf
```

When you are finished with these steps, a listing of `$HOME/sys161/bin` using commands:

```bash
cd bin && ls 
```

should look similar to this:

```
cs4300-addr2line@ cs4300-gcc-4.1.2@ cs4300-nm@ cs4300-size@ stat161-1.99.05*
cs4300-ar@ cs4300-gccbug@ cs4300-objcopy@ cs4300-strings@ sys161@
cs4300-as@ cs4300-gcov@ cs4300-objdump@ cs4300-strip@ sys161-1.99.05*
cs4300-c++filt@ cs4300-gdb@ cs4300-ranlib@ hub161@ trace161@
cs4300-cpp@ cs4300-gdbtui@ cs4300-readelf@ hub161-1.99.05* trace161-1.99.05*
cs4300-gcc@ cs4300-ld@ cs4300-run@ stat161@
```

These are all of the tools you will need to work with sys161.

**Step 2:** Install OS161

Now go into `docs/downloads` extract the `os161.tar.gz` file into the root of the project. This will contain the compiled OS161 kernels, and related test programs: 

```bash
cd $HOME/cs4300-os161/docs/downloads
tar -xzf os161.tar.gz -C $HOME/cs4300-os161/		# contains the source code
```

### Configure and Build OS161 Kernel

**Step 1:** Configure and Build

The next step is to configure OS161 and compile the kernel. From the `$HOME/cs4300-os161` directory, do the following: 

```bash
cd $HOME/cs4300-os161/os161-1.11
./configure --ostree=$HOME/cs4300-os161/root --toolprefix=cs4300-

cd kern/conf
./config ASST0

cd ../compile/ASST0
make depend
make
make install
```

The string `ASST0` in the commands above indicates that you are working on assignment 0. For Assignment X, replace `ASST0` with `ASSTX` in the commands above. 
The make install command will create a directory called `$HOME/cs4300-os161/root`, into which it will place the compiled kernel in a file called `kernel-ASST0`. 
It will also create a symbolic link call kernel referring to `kernel-ASST0`. Check the `$HOME/cs4300-os161/root` directory to make sure that your kernel is in place.

Next, build the OS161 user level utilities and test programs:

```bash
cd $HOME/cs4300-os161/os161-1.11
make
```

**Step 2:** Try Running OS161
You should now be able to use the SYS/161 simulator to run the OS161 kernel that you built and installed. The SYS/161 simulator requires a configuration file in order to run. 
To obtain one, do this: 

```bash
cd $HOME/cs4300-os161/root
cp $HOME/sys161/sys161.conf .
```

Now run your compiled kernel on the simulator. Assuming that you're still in the `$HOME/cs4300-os161/root` directory, do this: 

```bash
sys161 kernel-ASST0
```

You should see some output that looks something like this:

```
sys161: System/161 release 1.99.05, compiled Apr 28 2011 21:49:59
OS/161 base system version 1.11
Copyright (c) 2000, 2001, 2002, 2003
President and Fellows of Harvard College. All rights reserved.
Put-your-group-name-here's system version 0 (ASST0 #1)
Cpu is MIPS r2000/r3000
336k physical memory available
Device probe...
lamebus0 (system main bus)
emu0 at lamebus0
ltrace0 at lamebus0
ltimer0 at lamebus0
hardclock on ltimer0 (100 hz)
beep0 at ltimer0
rtclock0 at ltimer0
lrandom0 at lamebus0
random0 at lrandom0
lhd0 at lamebus0
lhd1 at lamebus0
lser0 at lamebus0
con0 at lser0
pseudorand0 (virtual)
OS/161 kernel [? for menu]:
```

The last line is a command prompt from the OS161 kernel. For now, just enter the command q to shut down the simulation and return to your shell.

[//]: # (The following are link variables)

[os161.tar.gz]: <http://www.engr.uconn.edu/$HOMEmok11002/public_html/os161.tar.gz>
[os161-binutils.tar.gz]: <http://www.engr.uconn.edu/$HOMEmok11002/public_html/os161-binutils.tar.gz>
[os161-gcc.tar.gz]: <http://www.engr.uconn.edu/$HOMEmok11002/public_html/os161-gcc.tar.gz>
[os161-gdb.tar.gz]:<http://www.engr.uconn.edu/$HOMEmok11002/public_html/os161-gdb.tar.gz>
[sys161.tar.gz]: <http://www.engr.uconn.edu/$HOMEmok11002/public_html/sys161.tar.gz>