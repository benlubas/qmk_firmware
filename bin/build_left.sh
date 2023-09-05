#!/bin/bash

echo "make fingerpunch/ximi:benlubas FP_TRACKBALL_RIGHT_ONLY=yes RGB_MATRIX_ENABLE=no ENCODER_ENABLE=yes AUDIO_ENABLE=no HAPTIC_ENABLE=no"
make fingerpunch/ximi:benlubas FP_TRACKBALL_RIGHT_ONLY=yes RGB_MATRIX_ENABLE=no ENCODER_ENABLE=yes AUDIO_ENABLE=no HAPTIC_ENABLE=no
mv -v ~/github/qmk_firmware/fingerpunch_ximi_benlubas.uf2 ~/github/qmk_firmware/fingerpunch_ximi_benlubas_left.uf2

# bin/fp_build.sh -k ximi -m benlubas -i -r

