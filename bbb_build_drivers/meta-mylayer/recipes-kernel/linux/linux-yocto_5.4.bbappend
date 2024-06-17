SECTION = "kernel"
SUMMARY = "Linux kernel for TI devices"

FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI += " \
             file://0001-added-st7735r.patch \
	"
#        file://0006-update-st7789v-node.patch \
# This was from TFT-FBT
#SRC_URI_append = " file://st7789.cfg"
SRC_URI_append = " file://fragment.cfg"


