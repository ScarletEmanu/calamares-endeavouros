# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "mypkgchooserq (QML is not supported in this build)" )
    return()
endif()

find_package(${qtname} ${QT_VERSION} CONFIG REQUIRED Core)

# include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../packagechooser )
set(_packagechooser ${CMAKE_CURRENT_SOURCE_DIR}/../packagechooser)

### OPTIONAL AppData XML support in PackageModel
#
#
option(BUILD_APPDATA "Support appdata: items in PackageChooser (requires QtXml)" OFF)
if(BUILD_APPDATA)
    find_package(${qtname} REQUIRED COMPONENTS Xml)
endif()

### OPTIONAL AppStream support in PackageModel
#
#
include(AppStreamHelper)

calamares_add_plugin(mypkgchooserq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        MyPkgChooserQmlViewStep.cpp
        ${_packagechooser}/Config.cpp
        ${_packagechooser}/PackageModel.cpp
        ${_extra_src}
    RESOURCES
        mypkgchooserq${QT_VERSION_SUFFIX}.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${_extra_libraries}
    SHARED_LIB
)
target_include_directories(${mypkgchooserq_TARGET} PRIVATE ${_packagechooser})

if(AppStreamQt_FOUND)
    target_link_libraries(${mypkgchooserq_TARGET} PRIVATE calamares::appstreamqt)
    target_sources(${mypkgchooserq_TARGET} PRIVATE ${_packagechooser}/ItemAppStream.cpp)
endif()

if(BUILD_APPDATA AND TARGET ${qtname}::Xml)
    target_compile_definitions(${mypkgchooserq_TARGET} PRIVATE HAVE_APPDATA)
    target_link_libraries(${mypkgchooserq_TARGET} PRIVATE ${qtname}::Xml)
    target_sources(${mypkgchooserq_TARGET} PRIVATE ${_packagechooser}/ItemAppData.cpp)
endif()
