#!/bin/bash

# switch the GPIO pins for the right side
sed -i 's/GP15/GP6/' keyboards/fingerpunch/ximi/config.h
bin/fp_build.sh -k ximi -m benlubas -i -r
# switch them back
sed -i '/^[^\/\/]/ s/GP6/GP15/' keyboards/fingerpunch/ximi/config.h
