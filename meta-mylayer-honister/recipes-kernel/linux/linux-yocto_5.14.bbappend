FILESEXTRAPATHS:prepend:poky := "${THISDIR}/files:"

SRC_URI += " \
            file://0001-updated-model-for-st7735r.patch \
            file://0001-adding-st7735r.patch \
            file://0001-add-to-dts-st7789v.patch \
            file://fragment.cfg \
	"
#file://st7735r.cfg \
#file://fragment.cfg \
#        file://0006-update-st7789v-node.patch \
# This was from TFT-FBT
#SRC_URI_append = " file://st7735r.cfg"


