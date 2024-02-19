SUMMARY = "recipe for custom kernel"
DESCRIPTION = "recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

FILESEXTRAPATHS:prepend:poky := "${THISDIR}/files:"

inherit kernel

SRC_URI = "https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.15.148.tar.xz;name=kernel \
           file://defconfig \
          "
#file://0001-dts-updtes.patch
S = "${WORKDIR}/linux-5.15.148"

SRC_URI[kernel.sha256sum] = "c48575c97fd9f4767cbe50a13b1b2b40ee42830aba3182fabd35a03259a6e5d8"

#addtask display_banner before do_build

