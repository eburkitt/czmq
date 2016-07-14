################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################

if (NOT MSVC)
    include(FindPkgConfig)
    pkg_check_modules(PC_SYSTEMD "libsystemd")
    if (NOT PC_SYSTEMD_FOUND)
        pkg_check_modules(PC_SYSTEMD "libsystemd")
    endif (NOT PC_SYSTEMD_FOUND)
    if (PC_SYSTEMD_FOUND)
        # add CFLAGS from pkg-config file, e.g. draft api.
        add_definitions(${PC_SYSTEMD_CFLAGS} ${PC_SYSTEMD_CFLAGS_OTHER})
        # some libraries install the headers is a subdirectory of the include dir
        # returned by pkg-config, so use a wildcard match to improve chances of finding
        # headers and SOs.
        set(PC_SYSTEMD_INCLUDE_HINTS ${PC_SYSTEMD_INCLUDE_DIRS} ${PC_SYSTEMD_INCLUDE_DIRS}/*)
        set(PC_SYSTEMD_LIBRARY_HINTS ${PC_SYSTEMD_LIBRARY_DIRS} ${PC_SYSTEMD_LIBRARY_DIRS}/*)
    endif(PC_SYSTEMD_FOUND)
endif (NOT MSVC)

find_path (
    SYSTEMD_INCLUDE_DIRS
    NAMES systemd/sd-daemon.h
    HINTS ${PC_SYSTEMD_INCLUDE_HINTS}
)

find_library (
    SYSTEMD_LIBRARIES
    NAMES libsystemd
    HINTS ${PC_SYSTEMD_LIBRARY_HINTS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    SYSTEMD
    REQUIRED_VARS SYSTEMD_LIBRARIES SYSTEMD_INCLUDE_DIRS
)
mark_as_advanced(
    SYSTEMD_FOUND
    SYSTEMD_LIBRARIES SYSTEMD_INCLUDE_DIRS
)

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
