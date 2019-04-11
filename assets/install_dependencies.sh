#!/usr/bin/env bash

declare -A osInfo;
osInfo[/etc/redhat-release]="yum install "
osInfo[/etc/arch-release]="pacman -S "
osInfo[/etc/gentoo-release]="emerge "
osInfo[/etc/SuSE-release]="zypper install "
osInfo[/etc/debian_version]="apt-get install "
dependencies=(wmctrl)
packageInstaller=""
for f in ${!osInfo[@]};do if [[ -f $f ]];then unset packageInstaller; packageInstaller=${osInfo[$f]}; fi done
for cmd in "${dependencies[@]}";do which $cmd &> /dev/null; if [ $? -eq 1 ];then sudo $packageInstaller $cmd; fi done