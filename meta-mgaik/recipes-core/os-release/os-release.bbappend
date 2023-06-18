# os-release: custom OS information

OS_RELEASE_FIELDS += "KERNEL_VERSION BUILD_ID HOME_URL"
OS_RELEASE_FIELDS_remove = "PRETTY_NAME ID VERSION_ID DISTRO_CODENAME"

NAME = "CRLD ${DISTRO_CODENAME} ${DISTRO_VERSION}"
VERSION = "${DISTRO_CODENAME}-${VERSION_ID}"
VERSION_ID = "${CLRD_BUILD_TYPE}${CLRD_VERSION_CODE}${CLRD_RELEASE_TYPE}"

KERNEL_VERSION = "${CARRIER_KERNEL_VERSION}"

BUILD_ID="${@time.strftime('%Y%m%d%H%M',time.localtime())}"
HOME_URL="http://www.carrier.com/"

def build_type(d):
    if d.getVar('CARRIER_BUILD_CONFIG') == 'prod':
        return 'V'
    else:
        return 'T'

######
# CRLD Versions

CLRD_BUILD_TYPE = "${@build_type(d)}"
CLRD_VERSION_CODE = "0011"
CLRD_RELEASE_TYPE = "C"

######
# Business Unit Support

VARIANT = "${BU_NAME}"
VARIANT_VERSION ="${BU_BUILD_TYPE}${BU_VERSION_CODE}.${BU_MAJOR_RELEASE_NO}.${BU_MINOR_RELEASE_NO}-${BU_RELEASE_TYPE}"

BU_BUILD_TYPE = "${@build_type(d)}"

python () {
    if d.getVar('BU_NAME'):
        d.appendVar('OS_RELEASE_FIELDS', ' VARIANT VARIANT_VERSION')
}

# Each BU must define the following in their own overlay
#BU_NAME = "BU"
#BU_VERSION_CODE="01"
#BU_MAJOR_RELEASE_NO="00"
#BU_MINOR_RELEASE_NO="00"
#BU_RELEASE_TYPE="A"

#########################################################################################################################
#DELETE EVERYTHING BELOW THIS SECTION INCLUSING THIS VERY LINE
#	1. Release version numbers that shall be part of OS-Release info available in /etc (This is how VERSION_ID is populated)
#		a. Vxx.yy.zz-R
#			i. xx - This will start with 01 and could only be changed per specificplatform need/directive
#			ii. yy - This shall start with 00 and shall increment for every new major change we shall add to release
#			iii. zz - This shall start with 00 and shall keep incrementing for every release we do
#			iv. R -  This shall start with A (Alpha) and go to B (Beta) and C(Charlie) where c is the final release to customer
#	2. OS-Release shall have option to BU specific ID & BU-Name (This is an option to give BU something they might need from versioning stand point)
#	3. VARIANT_REVISION shall be useful post BU release and then we do any enhancement at some point intime later than the release
#   4. BUILD_TYPE - This will be "V" for prod release and "T" for test releases, for T and V, going from T to V the number shall remain same to track
#   5. BU_SPECIFIC_ID and VENDOR_REVISION can be alphabetic or numeric or alphanumeric
#   6. Note : BUILD_ID are unique numbers, generated based on time stamp of build machine
#########################################################################################################################

