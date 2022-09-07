#!/usr/bin/env bash
SCRIPTDIR="$(dirname "$(readlink -f "$0")")"
PARENTDIR="$(dirname "${SCRIPTDIR}")"
LINUXDIR="${PARENTDIR}/linux"
DEBIANDIR="${PARENTDIR}/debian"
BUILDDIR="${PARENTDIR}/build/debian"
BLDDEB64DIR="${BUILDDIR}/64"
BUILDLINUXDIR="${PARENTDIR}/build/linux"
BLDDYN64DIR="${BUILDLINUXDIR}/dynamic/64"
if [[ ! -f "${BLDDYN64DIR}/unishellect" ]]; then
  exit 250
fi
if [[ ! -d "${DEBIANDIR}" ]]; then
  exit 249
fi
if [[ ! -d "${BLDDEB64DIR}" ]]; then
  if ! mkdir -p "${BLDDEB64DIR}"; then
    exit 248
  fi
fi
if ! cp "${BLDDYN64DIR}/unishellect" "${DEBIANDIR}/unishellect-2.0.1661201987/usr/bin/unishellect"; then
  exit 247
fi
cd "${DEBIANDIR}"
find -type f -iname ".nomedia" -exec rm "{}" \+ || exit 246 
if ! dpkg-deb --build --root-owner-group unishellect-2.0.1661201987; then
  exit 245
fi
if ! cp unishellect-2.0.1661201987.deb "${BLDDEB64DIR}/unishellect-2.0.1661201987.deb"; then
  exit 244
else
  rm unishellect-2.0.1661201987.deb
  rm unishellect-2.0.1661201987/usr/bin/unishellect
  find -depth -type d -empty -exec touch "{}/.nomedia" \;
fi
#if make android64staticall; then
#  if ! mv android/static/64/unishellect.aarch64 "${BLDSTC64DIR}/unishellect.aarch64"; then
#    exit 246
#  fi   
#  make clean
#else
#  exit 247
#fi
