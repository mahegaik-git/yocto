inherit core-image

require recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL += "usbutils \
                  fbida \
                  libdrm \
                  mycmake \
                  rsyslog \
                  test-readwrite \
                  "
                  
IMAGE_INSTALL += "sysbench \
                  lmbench \
                  stress \
                  sysstat \
                  fio \
                  curl \
                  python3 \
                  vim \
                  htop \
                  os-release \
                  tmux \ 
                  iperf3 \
                  "
                                    
IMAGE_FEATURES += "ssh-server-dropbear \
                  "

PACKAGECONFIG_append= " install-test-programs"

#IMAGE_FEATURES += "ssh-server-dropbear \
#                   splash \
#                  "


MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
                                     kernel-module-hello    \
                                     kernel-module-mymodule \
                                    "
