# lrd-image-minimal.inc: Carrier LRD minimal base image definition

inherit core-image

LICENSE = "CLOSED"

IMAGE_INSTALL += " \
	fbida \
	psplash \
	os-release \
	"

