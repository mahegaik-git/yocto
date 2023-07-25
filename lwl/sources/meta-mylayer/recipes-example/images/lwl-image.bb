inherit core-image

require recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL += "usbutils \
                  mycmake"
IMAGE_FEATURES += "ssh-server-dropbear \
                   splash"


