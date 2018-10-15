MACRO(USE_V8)
    covise_find_package(V8)
    if ((NOT V8_FOUND) AND (${ARGC} LESS 1))
        using_message("Skipping because of missing V8")
        return()
    endif((NOT V8_FOUND) AND (${ARGC} LESS 1))
    if(NOT V8_USED AND V8_FOUND)
        set(V8_USED TRUE)
        ADD_DEFINITIONS(-DHAVE_V8)
        include_directories(SYSTEM ${V8_INCLUDE_DIRS})
        set(EXTRA_LIBS ${EXTRA_LIBS} ${V8_LIBRARIES})
    endif()
ENDMACRO(USE_V8)
