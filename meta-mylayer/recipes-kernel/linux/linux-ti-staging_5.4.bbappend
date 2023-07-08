SECTION = "kernel"
SUMMARY = "Linux kernel for TI devices"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

inherit kernel

S= "${WORKDIR}"

SRC_URI += "file://0001-genetaring-patch-for-DTS.patch"


