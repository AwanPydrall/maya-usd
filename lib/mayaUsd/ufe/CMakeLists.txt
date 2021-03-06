# -----------------------------------------------------------------------------
# sources
# -----------------------------------------------------------------------------
target_sources(${PROJECT_NAME} 
    PRIVATE
        Global.cpp
        ProxyShapeHandler.cpp
        ProxyShapeHierarchy.cpp
        ProxyShapeHierarchyHandler.cpp
        StagesSubject.cpp
        UsdHierarchy.cpp
        UsdHierarchyHandler.cpp
        UsdRootChildHierarchy.cpp
        UsdRotatePivotTranslateUndoableCommand.cpp
        UsdRotateUndoableCommand.cpp
        UsdScaleUndoableCommand.cpp
        UsdSceneItem.cpp
        UsdSceneItemOps.cpp
        UsdSceneItemOpsHandler.cpp
        UsdStageMap.cpp
        UsdTransform3d.cpp
        UsdTransform3dHandler.cpp
        UsdTranslateUndoableCommand.cpp
        UsdUndoDeleteCommand.cpp
        UsdUndoDuplicateCommand.cpp
        UsdUndoRenameCommand.cpp
        Utils.cpp
        moduleDeps.cpp
)

if(CMAKE_UFE_V2_FEATURES_AVAILABLE)
    target_sources(${PROJECT_NAME}
        PRIVATE
            UsdAttribute.cpp
            UsdAttributes.cpp
            UsdAttributesHandler.cpp
            UsdObject3d.cpp
            UsdObject3dHandler.cpp
            UsdUndoCreateGroupCommand.cpp
    )
    if(UFE_PREVIEW_VERSION_NUM GREATER_EQUAL 2009)
        target_sources(${PROJECT_NAME}
            PRIVATE
                UsdContextOps.cpp
                UsdContextOpsHandler.cpp
        )
    endif()
endif()

set(headers
    Global.h
    ProxyShapeHandler.h
    ProxyShapeHierarchy.h
    ProxyShapeHierarchyHandler.h
    StagesSubject.h
    UsdHierarchy.h
    UsdHierarchyHandler.h
    UsdRootChildHierarchy.h
    UsdRotatePivotTranslateUndoableCommand.h
    UsdRotateUndoableCommand.h
    UsdScaleUndoableCommand.h
    UsdSceneItem.h
    UsdSceneItemOps.h
    UsdSceneItemOpsHandler.h
    UsdStageMap.h
    UsdTransform3d.h
    UsdTransform3dHandler.h
    UsdTranslateUndoableCommand.h
    UsdUndoDeleteCommand.h
    UsdUndoDuplicateCommand.h
    UsdUndoRenameCommand.h
    Utils.h
    UfeVersionCompat.h
)

if(CMAKE_UFE_V2_FEATURES_AVAILABLE)
    list(APPEND headers
        UsdAttribute.h
        UsdAttributes.h
        UsdAttributesHandler.h
        UsdContextOps.h
        UsdContextOpsHandler.h
        UsdObject3d.h
        UsdObject3dHandler.h
        UsdUndoCreateGroupCommand.h
    )
endif()

# -----------------------------------------------------------------------------
# promote headers
# -----------------------------------------------------------------------------
mayaUsd_promoteHeaderList(HEADERS ${headers} SUBDIR ufe)

# -----------------------------------------------------------------------------
# install
# -----------------------------------------------------------------------------
install(FILES ${headers}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/ufe
)

set(UFE_PYTHON_MODULE_NAME ufe)

# -----------------------------------------------------------------------------
# subdirectories
# -----------------------------------------------------------------------------
add_subdirectory(private)

# -----------------------------------------------------------------------------
# target (UFE Python Bindings)
# -----------------------------------------------------------------------------
# UFE Python Bindings
if(IS_WINDOWS AND MAYAUSD_DEFINE_BOOST_DEBUG_PYTHON_FLAG)
    # On Windows when compiling with debug python the library must be named with _d.
    set(UFE_PYTHON_TARGET_NAME "_${UFE_PYTHON_MODULE_NAME}_d")
else()
    set(UFE_PYTHON_TARGET_NAME "_${UFE_PYTHON_MODULE_NAME}")
endif()

add_library(${UFE_PYTHON_TARGET_NAME} SHARED)

# -----------------------------------------------------------------------------
# sources
# -----------------------------------------------------------------------------
target_sources(${UFE_PYTHON_TARGET_NAME} 
    PRIVATE
        module.cpp
        wrapUtils.cpp
)

# -----------------------------------------------------------------------------
# compiler configuration
# -----------------------------------------------------------------------------
target_compile_definitions(${UFE_PYTHON_TARGET_NAME}
    PRIVATE
        MFB_PACKAGE_NAME=${UFE_PYTHON_MODULE_NAME}
        MFB_ALT_PACKAGE_NAME=${UFE_PYTHON_MODULE_NAME}
        MFB_PACKAGE_MODULE="${PROJECT_NAME}.${UFE_PYTHON_MODULE_NAME}"
)

mayaUsd_compile_config(${UFE_PYTHON_TARGET_NAME})

# -----------------------------------------------------------------------------
# link libraries
# -----------------------------------------------------------------------------
target_link_libraries(${UFE_PYTHON_TARGET_NAME}
    PUBLIC
        ${PROJECT_NAME}
)

# -----------------------------------------------------------------------------
# properties
# -----------------------------------------------------------------------------
set_python_module_property(${UFE_PYTHON_TARGET_NAME})

# -----------------------------------------------------------------------------
# run-time search paths
# -----------------------------------------------------------------------------
if(IS_MACOSX OR IS_LINUX)
    mayaUsd_init_rpath(rpath "${PROJECT_NAME}")
    mayaUsd_add_rpath(rpath "../../..")
    if(IS_MACOSX AND DEFINED MAYAUSD_TO_USD_RELATIVE_PATH)
        mayaUsd_add_rpath(rpath "../../../../${MAYAUSD_TO_USD_RELATIVE_PATH}/lib")
    endif()
    mayaUsd_install_rpath(rpath ${UFE_PYTHON_TARGET_NAME})
endif()

# -----------------------------------------------------------------------------
# install
# -----------------------------------------------------------------------------
install(TARGETS ${UFE_PYTHON_TARGET_NAME}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python/${PROJECT_NAME}/${UFE_PYTHON_MODULE_NAME}
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python/${PROJECT_NAME}/${UFE_PYTHON_MODULE_NAME}
)

install(FILES __init__.py
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python/${PROJECT_NAME}/${UFE_PYTHON_MODULE_NAME}
)

if(IS_WINDOWS)
    install(FILES $<TARGET_PDB_FILE:${UFE_PYTHON_TARGET_NAME}> 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/python/${PROJECT_NAME}/${UFE_PYTHON_MODULE_NAME} OPTIONAL)
endif()
