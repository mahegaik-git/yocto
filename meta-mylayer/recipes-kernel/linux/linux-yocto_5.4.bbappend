SECTION = "kernel"
SUMMARY = "Linux kernel for TI devices"

FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI += " \
        file://0001-updates-for-ili9341-on-spi.patch \
	"

# This was from TFT-FBT
SRC_URI_append = " file://fb_ili9341.cfg"
RPROVIDES_${PN} += "kernel-module-fb-ili9341-5.4.58-yocto-standard"
RPROVIDES_${PN} += "kernel-module-fbtft-5.4.58-yocto-standard"
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "kernel-module-fb-ili9341-5.4.58-yocto-standard"
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "kernel-module-fbtft-5.4.58-yocto-standard"
KERNEL_MODULE_AUTOLOAD += "kernel-module-fb-ili9341-5.4.58-yocto-standard"
KERNEL_MODULE_AUTOLOAD += "kernel-module-fbtft-5.4.58-yocto-standard"

# This was from TFT-FBT
#SRC_URI_append = " file://tiny_ili9341.cfg"
#RPROVIDES_${PN} += "kernel-module-ili9341-5.4.58-yocto-standard"
#MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "kernel-module-ili9341-5.4.58-yocto-standard"
#KERNEL_MODULE_AUTOLOAD += "kernel-module-ili9341-5.4.58-yocto-standard"
