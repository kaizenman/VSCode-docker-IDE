cp -v /usr/include /include -R

# FIXME: workaround
mkdir /include/machine
cp /usr/include/endian.h /include/machine/