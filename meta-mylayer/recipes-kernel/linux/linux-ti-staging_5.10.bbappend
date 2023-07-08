SECTION = "kernel"
SUMMARY = "Linux kernel for TI devices"

FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI_append = " file://fragment.cfg"
SRC_URI_append = " file://git/arch/arm/boot/dts/am335x-boneblack.dts"
SRC_URI_append = " file://git/arch/arm/boot/dts/am335x-boneblack-common.dtsi"
KERNEL_DEVICETREE_append  = " am335x-boneblack.dtb"
KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/fragment.cfg"

