FILESEXTRAPATHS:prepend:poky := "${THISDIR}/files:"

SRC_URI += " \
            file://st7789v.cfg \
            file://am335x-boneblack.dts \
            file://am335x-bone-common.dtsi \
           "

do_update_dts(){
    cp ${WORKDIR}/am335x-boneblack.dts ${STAGING_KERNEL_DIR}/arch/arm/boot/dts/am335x-boneblack.dts
    cp ${WORKDIR}/am335x-bone-common.dtsi ${STAGING_KERNEL_DIR}/arch/arm/boot/dts/am335x-bone-common.dtsi
}

addtask update_dts after do_patch before do_configure

#KERNEL_DEVICETREE:append += "am335x-boneblack.dtb"



