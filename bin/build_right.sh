#!/bin/bash

echo "making substitutions:"
echo "RX from GP1  to GP5"
echo "TX from GP0  to GP4"
echo "        GP15 to GP6"
# switch the GPIO pins for the right side
sed -i 's/\(RX_PIN\) GP1/\1 GP5/' keyboards/fingerpunch/ximi/config.h
sed -i 's/\(TX_PIN\) GP0/\1 GP4/' keyboards/fingerpunch/ximi/config.h
sed -i 's/GP15/GP6/' keyboards/fingerpunch/ximi/config.h

echo "make fingerpunch/ximi:benlubas FP_TRACKBALL_RIGHT_ONLY=yes RGB_MATRIX_ENABLE=no ENCODER_ENABLE=yes AUDIO_ENABLE=no HAPTIC_ENABLE=no"
make fingerpunch/ximi:benlubas FP_TRACKBALL_RIGHT_ONLY=yes RGB_MATRIX_ENABLE=no ENCODER_ENABLE=yes AUDIO_ENABLE=no HAPTIC_ENABLE=no
# bin/fp_build.sh -k ximi -m benlubas -i -r

echo "cleaning up"
sed -i 's/\(TX_PIN\) GP4/\1 GP0/' keyboards/fingerpunch/ximi/config.h
sed -i 's/\(RX_PIN\) GP5/\1 GP1/' keyboards/fingerpunch/ximi/config.h
sed -i '/^[^\/\/]/ s/GP6/GP15/' keyboards/fingerpunch/ximi/config.h

mv -v ~/github/qmk_firmware/fingerpunch_ximi_benlubas.uf2 ~/github/qmk_firmware/fingerpunch_ximi_benlubas_right.uf2
