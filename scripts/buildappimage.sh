#!/usr/bin/env bash
SCRIPTDIR="$(dirname "$(readlink -f "$0")")"
PARENTDIR="$(dirname "${SCRIPTDIR}")"
LINUXDIR="${PARENTDIR}/linux"
APPIMAGEDIR="${PARENTDIR}/appimage"
BUILDDIR="${PARENTDIR}/build/appimage"
BLDAPPIMAGE64DIR="${BUILDDIR}/64"
BUILDLINUXDIR="${PARENTDIR}/build/linux"
BLDDYN64DIR="${BUILDLINUXDIR}/dynamic/64"
if [[ ! -f "${BLDDYN64DIR}/unishellect" ]]; then
  exit 236
fi
if [[ ! -d "${APPIMAGEDIR}" ]]; then
  exit 235
fi
if [[ ! -d "${BLDAPPIMAGE64DIR}" ]]; then
  if ! mkdir -p "${BLDAPPIMAGE64DIR}"; then
    exit 234
  fi
fi
if ! cp "${BLDDYN64DIR}/unishellect" "${APPIMAGEDIR}/unishellect-x86_64.AppDir/usr/bin/unishellect"; then
  exit 233
fi
cd "${APPIMAGEDIR}"
find -type f -iname ".nomedia" -exec rm "{}" \+ || exit 232
if ! ./appimagetool unishellect-x86_64.AppDir; then
  exit 231
fi
if ! cp UniShellect-x86_64.AppImage "${BLDAPPIMAGE64DIR}/UniShellect-x86_64.AppImage"; then
  exit 230
else
  rm UniShellect-x86_64.AppImage
  rm unishellect-x86_64.AppDir/usr/bin/unishellect
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
