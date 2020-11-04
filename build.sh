#!/bin/bash
options="ri:"
debug=true
build_dir=
PLAT=txmp
installdir="/tftpboot/$PLAT"
date=$(date -I)

set -e

while getopts "$options" opt;do
    case $opt in
	i)
	    installdir="$OPTARG"
	    ;;
	r)
	    debug=false
	    ;;
	\?)
	    exit 1
	    ;;
	*)
	    echo "unsupported option -- $opt"
	    usage
    esac
done
shift $(($OPTIND - 1))

export CROSS_COMPILE=${CROSS_COMPILE:-arm-cortexa7-linux-gnueabi-}
ARCH=${ARCH:-aarch32}

make_opts=()
make_opts[${#make_opts[@]}]="VENDOR=karo"
make_opts[${#make_opts[@]}]="ARM_ARCH_MAJOR=7"
make_opts[${#make_opts[@]}]="AARCH32_SP=sp_min"
if $debug;then
    make_opts[${#make_opts[@]}]="DEBUG=1"
    make_opts[${#make_opts[@]}]="LOG_LEVEL=40"
    builddir=build/${PLAT:-txmp}/debug
    suffix=-dbg
else
    make_opts[${#make_opts[@]}]="LOG_LEVEL=10"
    builddir=build/${PLAT:-txmp}/release
    suffix=""
fi
#make_opts[${#make_opts[@]}]="ENABLE_ASSERT=1"
#make_opts[${#make_opts[@]}]="ENABLE_BACKTRACE=1"
#make_opts[${#make_opts[@]}]="AARCH32_INSTRUCTION_SET=A32"
#make_opts[${#make_opts[@]}]="AARCH32_EXCEPTION_DEBUG=1"

dtb_files=(
    stm32mp151a-qsmp-1510
    stm32mp153a-qsmp-1530
    stm32mp157c-qsmp-1570
    stm32mp153a-txmp-1530
    stm32mp157c-txmp-1570
)

for dtb in "${dtb_files[@]}";do
    echo make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} PLAT=${PLAT:-txmp} DTB_FILE_NAME="${dtb}.dtb" "${make_opts[@]}" "$@"
    make ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} PLAT=${PLAT:-txmp} DTB_FILE_NAME="${dtb}.dtb" "${make_opts[@]}" "$@"
    if [ -n "$installdir" ];then
	cp -avu "${builddir}/tf-a-${dtb}.stm32" "${installdir}/tf-a-${dtb}${suffix}-${date}.stm32"
	ln -snvf "tf-a-${dtb}${suffix}-${date}.stm32" "${installdir}/tf-a-${dtb}${suffix}-latest.stm32"
    fi
done
