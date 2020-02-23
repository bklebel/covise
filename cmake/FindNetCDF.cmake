
FIND_PATH(NETCDF_INCLUDE_DIR netcdf.h)
FIND_PATH(NETCDF_C++_INCLUDE_DIR netcdfcpp.h)

FIND_LIBRARY(NETCDF_LIBRARY NAMES netcdf) 
FIND_LIBRARY(NETCDF_LIBRARY_DEBUG NAMES netcdfd) 
FIND_LIBRARY(NETCDF_C++_LIBRARY NAMES netcdf_c++) 
FIND_LIBRARY(NETCDF_C++_LIBRARY_DEBUG NAMES netcdf_c++d) 


IF(MSVC)
  # VisualStudio needs a debug version
  FIND_LIBRARY(NETCDF_C++_LIBRARY_DEBUG NAMES ${NETCDF_C++_DBG_NAMES}
    PATHS
    $ENV{NETCDF_HOME}/lib
    $ENV{EXTERNLIBS}/NETCDF/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
    DOC "NETCDF_C++ - Library (Debug)"
  )
  FIND_LIBRARY(NETCDF_LIBRARY_DEBUG NAMES ${NETCDF_DBG_NAMES}
    PATHS
    $ENV{NETCDF_HOME}/lib
    $ENV{EXTERNLIBS}/NETCDF/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
    DOC "NETCDF - Library (Debug)"
  )
  
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(NETCDF DEFAULT_MSG
      NETCDF_LIBRARY NETCDF_LIBRARY_DEBUG
      NETCDF_C++_LIBRARY NETCDF_C++_LIBRARY_DEBUG
      NETCDF_INCLUDE_DIR)

  MARK_AS_ADVANCED(NETCDF_C++_LIBRARY NETCDF_C++_LIBRARY_DEBUG NETCDF_LIBRARY NETCDF_LIBRARY_DEBUG NETCDF_INCLUDE_DIR)

  IF(NETCDF_FOUND)
    SET(NETCDF_LIBRARIES optimized ${NETCDF_LIBRARY} debug ${NETCDF_LIBRARY_DEBUG} optimized ${NETCDF_C++_LIBRARY} debug ${NETCDF_C++_LIBRARY_DEBUG} )
    SET(NETCDF_C++_LIBRARIES optimized ${NETCDF_C++_LIBRARY} debug ${NETCDF_C++_LIBRARY_DEBUG})
  ENDIF(NETCDF_FOUND)
  
ELSE(MSVC)

    FIND_PACKAGE_HANDLE_STANDARD_ARGS(NETCDF DEFAULT_MSG NETCDF_LIBRARY NETCDF_C++_LIBRARY NETCDF_INCLUDE_DIR NETCDF_C++_INCLUDE_DIR)
    IF (NETCDF_FOUND)
        SET(NETCDF_LIBRARIES ${NETCDF_LIBRARY} ${NETCDF_C++_LIBRARY})
        SET(NETCDF_INCLUDE_DIRS ${NETCDF_INCLUDE_DIR} ${NETCDF_C++_INCLUDE_DIR})
    ENDIF (NETCDF_FOUND)

ENDIF(MSVC)
