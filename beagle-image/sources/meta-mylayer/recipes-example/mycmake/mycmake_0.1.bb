DESCRIPTION = " Simple CMAKE TEst"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://userprog.c \
           file://CMakeLists.txt \
           file://0001-First-Patch.patch" 
S= "${WORKDIR}"

inherit cmake

