inherit core-image

require recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL += "usbutils \
                  fbida \
                  libdrm \
                  "
IMAGE_FEATURES += "ssh-server-dropbear \
                  "

PACKAGECONFIG_append= " install-test-programs"

#IMAGE_FEATURES += "ssh-server-dropbear \
#                   splash \
#                  "
