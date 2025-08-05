set(VERSION_INFO_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

function(generate_version_resource target_name)
    set(options)
    set(one_value_args OUTPUT_FILE
                       NAME
                       FILENAME
                       MAJOR_VERSION
                       MINOR_VERSION
                       PATCH_VERSION
                       COMPANY_NAME
                       COPYRIGHT)
    set(multi_value_args)
    cmake_parse_arguments(VERSIONINFO "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    get_target_property(TARGET_TYPE ${target_name} TYPE)
    if(TARGET_TYPE STREQUAL EXECUTABLE)
        set(VERSIONINFO_TARGET_TYPE 0)
    elseif(TARGET_TYPE STREQUAL SHARED_LIBRARY)
        set(VERSIONINFO_TARGET_TYPE 1)
    elseif(TARGET_TYPE STREQUAL STATIC_LIBRARY)
        set(VERSIONINFO_TARGET_TYPE 2)
    else()
        set(VERSIONINFO_TARGET_TYPE 3)
    endif()

    configure_file("${VERSION_INFO_SOURCE_DIR}/version.rc.in"
                   ${VERSIONINFO_OUTPUT_FILE}
                   @ONLY)
endfunction()

function(generate_version_header)
    set(options)
    set(one_value_args OUTPUT_FILE PREFIX MAJOR MINOR PATCH)
    set(multi_value_args)
    cmake_parse_arguments(VERSION "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
    configure_file("${VERSION_INFO_SOURCE_DIR}/version.h.in"
                   ${VERSION_OUTPUT_FILE}
                   @ONLY
                   NEWLINE_STYLE LF)
endfunction()