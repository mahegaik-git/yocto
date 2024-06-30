DESCRIPTION = " Test code to verify readwrite kernel module available at /dev/dummydriver"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://test-gpiodriver.c \
           file://CMakeLists.txt \
          " 
S= "${WORKDIR}"

inherit cmake



