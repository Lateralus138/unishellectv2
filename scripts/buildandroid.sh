#!/usr/bin/env bash
SCRIPTDIR="$(dirname "$(readlink -f "$0")")"
PARENTDIR="$(dirname "${SCRIPTDIR}")"
LINUXDIR="${PARENTDIR}/linux"
BUILDDIR="${PARENTDIR}/build/android"
BLDSTC64DIR="${BUILDDIR}/static/64"
if [[ ! -d "${LINUXDIR}" ]]; then
  exit 243
fi
if [[ ! -d "${BUILDDIR}" ]]; then
  if ! mkdir -p "${BUILDDIR}"; then
    exit 242
  fi
fi
if [[ ! -d "${BLDSTC64DIR}" ]]; then
  if ! mkdir -p "${BLDSTC64DIR}"; then
    exit 241
  fi
fi
cd "${LINUXDIR}"
sudo apt update  || exit 240
sudo apt install g++-aarch64-linux-gnu -y || exit 239
if make android64staticall; then
  if ! mv android/static/64/unishellect.aarch64 "${BLDSTC64DIR}/unishellect.aarch64"; then
    exit 237
  fi   
  make clean
else
  exit 238
fi
