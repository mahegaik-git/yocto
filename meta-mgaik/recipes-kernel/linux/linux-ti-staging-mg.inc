# Linux Kernel 4.x/5.x common support
SECTION = "kernel"
DESCRIPTION = "Linux kernel for TI devices"
FILESEXTRAPATHS_prepend :="${THISDIR}/files:"
FILESEXTRAPATHS_prepend :="${THISDIR}/linux-ti-staging-5.10/ti33x:"

KERNEL_GIT_PROTOCOL_local-sources = "file"
# PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "git${SRCPV}"
SRCREV = "${AUTOREV}"
OVERRIDES_append = ":kernel-common-cfg"

SRC_URI_append_kernel-common-cfg = " \
        file://spi.cfg  \
        file://fragment.cfg  \
    "    

KERNEL_CONFIG_FRAGMENTS_append_kernel-common-cfg = " \
        ${WORKDIR}/spi.cfg  \
        ${WORKDIR}/fragment.cfg  \
    "
    
