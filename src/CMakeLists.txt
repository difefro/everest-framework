#
# \file        CMakeLists.txt
# \author      Felix Dilly
# \date        Created at: 2024-04-15
# \date        Last modified at: 2024-05-08
# ---
# \copyright   Copyright 2024 Fronius International GmbH.
#              https://www.fronius.com
#

find_package(liblogging CONFIG REQUIRED)

add_executable(manager)
target_sources(manager
    PRIVATE
        system_unix.cpp
        manager.cpp
)

target_link_libraries(manager
    PRIVATE
        everest::framework
        Boost::program_options
        PkgConfig::libcap
        frostd::liblogging_static
)
target_link_libraries(manager

)

if (EVEREST_ENABLE_ADMIN_PANEL_BACKEND)
    target_link_libraries(manager
        PRIVATE
            controller-ipc
    )

    target_compile_definitions(manager PRIVATE ENABLE_ADMIN_PANEL)

    add_subdirectory(controller)
endif ()

target_compile_options(manager PRIVATE ${COMPILER_WARNING_OPTIONS})

target_compile_features(manager PRIVATE cxx_std_20)

install(
    TARGETS manager
    RUNTIME
)

# FIXME (aw): the www folder currently always needs to exist, so that the manager does not complain
install(
    DIRECTORY # intentionally left blank
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/everest/www"
)
