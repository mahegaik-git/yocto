SECTION = "kernel"
SUMMARY = "Linux kernel for TI devices"

FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI_append = " file://git/arch/arm/boot/dts/am335x-boneblack.dts"
SRC_URI_append = " file://git/arch/arm/boot/dts/am335x-boneblack-common.dtsi"
KERNEL_DEVICETREE_append  = " am335x-boneblack.dtb"


# This was from TFT-FBT
SRC_URI_append = " file://fragment.cfg"
KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/fragment.cfg"
#RPROVIDES_${PN} += "kernel-module-fb_ili9341"

# This was from TINY-DRM
#SRC_URI_append = " file://tinydrm.cfg"
#KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/tinydrm.cfg"
#RPROVIDES_${PN} += "kernel-module-ili9341"
