#!/bin/bash

# This will perform a clean (if necessary), full download of repositories, and conditional
# Buildroot build of full system. 

#remove previous directories if needed
echo "Checking Directories and cleaning"
if [ -d buildroot-at91 ]; then
	echo "removing buildroot-at91"
	rm -rf buildroot-at91
else	
	echo "buildroot-at91 did not exist"
fi


#Do the same for BR external demo build
if [ -d buildroot-external-microchip ]; then
	echo "removing addtional external directories"
	rm -rf buildroot-external-microchip
else
	echo "buildroot-external-microchip did not exist"
fi

# prep all
#buildroot sources
echo "Cloning Repositories"
git clone https://github.com/linux4sam/buildroot-at91.git
cd buildroot-at91
git tag | grep linux4sam
# old version - git checkout linux4sam_6.0 -b buildroot-at91-linux4sam_6.0
git checkout linux4sam-2020.04 -b buildroot-at91-linux4sam-2020.04
cd ..

#do BR externals

git clone https://github.com/linux4sam/buildroot-external-microchip.git
cd buildroot-external-microchip
git tag | grep linux4sam
#old version - git checkout linux4sam_6.0 -b buildroot-external-microchip-linux4sam_6.0
git checkout linux4sam-2020.04 -b buildroot-external-microchip-linux4sam-2020.04
cd ..

#setup defconfig for build, use the BR external
cd buildroot-at91
BR2_EXTERNAL=../buildroot-external-microchip/ make sama5d27_som1_ek_headless_defconfig

# I go ahead and download all of the sources so I can time the build on various systems, makes it non-dependent on 
# download speeds....
echo "Downloading All Sources"
make source


# Go into kernelconfig and then menuconfig and wait.
# You can add anything else here (drivers, apps like "nano", etc)

BR2_EXTERNAL=../buildroot-external-microchip/ make linux-menuconfig
BR2_EXTERNAL=../buildroot-external-microchip/ make menuconfig

# Now make. Be patient, this can take anywhere from 30 minutes on a very fast native host to 
# hours on a VM!

# note - if needed, temp comment out make so can edit dts and any source needed

make
# we now have a clean build waiting...








