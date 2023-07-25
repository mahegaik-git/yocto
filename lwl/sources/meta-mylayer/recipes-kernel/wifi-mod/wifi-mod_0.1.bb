SUMMARY = "Example of how to build an external Linux kernel module"
DESCRIPTION = "${SUMMARY}"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit module

SRC_URI = "git://github.com/nxp-imx/mwifiex.git;protocol=https;branch=lf-5.15.71_2.2.0"
SRCREV = "${AUTOREV}"
#S = "${WORKDIR}/git"
S = "${WORKDIR}/git/mxm_wifiex/wlan_src"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.


export KERNELDIR="${KERNEL_SRC}"

#RPROVIDES_${PN} += "kernel-module-hello"
RPROVIDES_${PN} += "kernel-module-mlan"


#MY_MODULE_NAME ?= "${SOURCE_DIRECTORY}"
#S = "${WORKDIR}/${SOURCE_DIRECTORY}"
#RPROVIDES_${PN} += "kernel-module-${MY__MODULE_NAME}"
