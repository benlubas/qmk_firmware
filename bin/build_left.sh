#!/bin/bash

# echo "make fingerpunch/ximi:benlubas FP_TRACKBALL_RIGHT_ONLY=yes FP_SPLIT_RIGHT=yes RGB_MATRIX_ENABLE=yes ENCODER_ENABLE=yes AUDIO_ENABLE=no HAPTIC_ENABLE=no"
# make fingerpunch/ximi:benlubas FP_TRACKBALL_RIGHT_ONLY=yes FP_SPLIT_LEFT=yes RGB_MATRIX_ENABLE=yes ENCODER_ENABLE=yes AUDIO_ENABLE=no HAPTIC_ENABLE=no
bin/fp_build.sh -k ximi -m benlubas -i -r

# mv -v ~/github/qmk_firmware/fingerpunch_ximi_benlubas.uf2 ~/github/qmk_firmware/fingerpunch_ximi_benlubas_left.uf2
