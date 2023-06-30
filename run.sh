#!/bin/bash

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:."

export QT_QPA_EGLFS_KMS_CONFIG=/etc/eglfs.json
export QT_QPA_EGLFS_ALWAYS_SET_MODE=1
export QT_QPA_EGLFS_KMS_ATOMIC=1
export QT_QPA_PLATFORM=eglfs
export QT_LOGGING_RULES="qt.scenegraph.general=true;qt.scenegraph.time.*=false;"

./$@
