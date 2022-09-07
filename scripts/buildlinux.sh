#!/usr/bin/env bash
SCRIPTDIR="$(dirname "$(readlink -f "$0")")"
PARENTDIR="$(dirname "${SCRIPTDIR}")"
LINUXDIR="${PARENTDIR}/linux"
BUILDDIR="${PARENTDIR}/build/linux"
BLDDYN64DIR="${BUILDDIR}/dynamic/64"
if [[ ! -d "${LINUXDIR}" ]]; then
  exit 255
fi
if [[ ! -d "${BUILDDIR}" ]]; then
  if ! mkdir -p "${BUILDDIR}"; then
    exit 254
  fi
fi
if [[ ! -d "${BLDDYN64DIR}" ]]; then
  if ! mkdir -p "${BLDDYN64DIR}"; then
    exit 253
  fi
fi
cd "${LINUXDIR}"
if make releasedynamicall; then
  chmod 0755 release/dynamic/unishellect
  if ! mv release/dynamic/unishellect "${BLDDYN64DIR}/unishellect"; then
    exit 251
  fi   
  make clean
else
  exit 252
fi
