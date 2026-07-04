# Copies every DLL produced under the FetchContent build tree next to the
# executable. Runs at build time (not configure time) so it picks up DLLs
# that don't exist yet when CMake first configures the project.
file(GLOB_RECURSE RUNTIME_DLLS "${BUILD_DIR}/_deps/*.dll")
file(COPY ${RUNTIME_DLLS} DESTINATION "${DEST_DIR}")
