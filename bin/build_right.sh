#!/bin/bash

echo "making substitutions:\nRX from GP1 to GP5\nTX from GP0 to GP4\nGP15 to GP6\n"
# switch the GPIO pins for the right side
sed -i 's/\(RX_PIN\) GP1/\1 GP5/' keyboards/fingerpunch/ximi/config.h
sed -i 's/\(TX_PIN\) GP0/\1 GP4/' keyboards/fingerpunch/ximi/config.h
sed -i 's/GP15/GP6/' keyboards/fingerpunch/ximi/config.h

bin/fp_build.sh -k ximi -m benlubas -i -r

echo "cleaning up"
sed -i 's/\(TX_PIN\) GP4/\1 GP0/' keyboards/fingerpunch/ximi/config.h
sed -i 's/\(RX_PIN\) GP5/\1 GP1/' keyboards/fingerpunch/ximi/config.h
sed -i '/^[^\/\/]/ s/GP6/GP15/' keyboards/fingerpunch/ximi/config.h
