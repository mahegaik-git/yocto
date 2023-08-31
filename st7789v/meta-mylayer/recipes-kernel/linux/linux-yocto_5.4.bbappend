SECTION = "kernel"
SUMMARY = "Linux kernel for TI devices"

FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI += " \
        file://0001-patch-for-st7735r.patch \
        file://0002-compatible-is-ili9341.patch \
        file://0003-spi-at-8MHZ.patch \
        file://0004-compatible-st7789v.patch \
        file://0005-update-st7789-node.patch \
        file://0007-added-waveshare-along-with-st7789v.patch \
        file://0008-st7789v-32MHz.patch \
	"
#        file://0006-update-st7789v-node.patch \
# This was from TFT-FBT
#SRC_URI_append = " file://fb_ili9341.cfg"
#SRC_URI_append = " file://st7735_fragment.cfg"

#SRC_URI_append = " file://new-ili-fragment.cfg"
SRC_URI_append = " file://st7789.cfg"

#below one get back for st7735r
#SRC_URI_append = " file://new-fragment.cfg"

#kernel-module-fb-st7735r-5.4.58-yocto-standard
#kernel-module-fb-st7789v-5.4.58-yocto-standard

#RPROVIDES_${PN} += "kernel-module-fb-ili9341-5.4.58-yocto-standard"
#RPROVIDES_${PN} += "kernel-module-fbtft-5.4.58-yocto-standard"
#MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "kernel-module-fb-ili9341-5.4.58-yocto-standard"
#MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "kernel-module-fbtft-5.4.58-yocto-standard"
#KERNEL_MODULE_AUTOLOAD += "kernel-module-fb-ili9341-5.4.58-yocto-standard"
#KERNEL_MODULE_AUTOLOAD += "kernel-module-fbtft-5.4.58-yocto-standard"

