# @file
# 
# CMakeLists.txt for covise kernel
#
# @author Blasius Czink

PROJECT(kernel CXX C)

if (NOT COVISE_BUILD_ONLY_COVER)
    ADD_SUBDIRECTORY(file)
endif()

if (NOT XERCESC_FOUND OR COVISE_BUILD_ONLY_FILE)
   return()
endif()

ADD_SUBDIRECTORY(util)
ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(net)
ADD_SUBDIRECTORY(img)
ADD_SUBDIRECTORY(vrb)
ADD_SUBDIRECTORY(grmsg)
ADD_SUBDIRECTORY(gpu)
ADD_SUBDIRECTORY(tui)
ADD_SUBDIRECTORY(qtutil)
if (NOT COVISE_BUILD_ONLY_COVER)
   ADD_SUBDIRECTORY(shm)
   ADD_SUBDIRECTORY(covise)
   ADD_SUBDIRECTORY(do)
   ADD_SUBDIRECTORY(appl)
   ADD_SUBDIRECTORY(api)
   ADD_SUBDIRECTORY(alg)
   ADD_SUBDIRECTORY(vtk)
   ADD_SUBDIRECTORY(dmgr)
   ADD_SUBDIRECTORY(reader)
   ADD_SUBDIRECTORY(star)
   ADD_SUBDIRECTORY(wslib)
endif()