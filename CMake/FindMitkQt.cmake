SET(DESIRED_QT_VERSION 0 CACHE STRING "Pick a version of Qt to use: 3 or 4")

IF(DESIRED_QT_VERSION MATCHES 0)
  MESSAGE("Please set the DESIRED_QT_VERSION")
ELSE(DESIRED_QT_VERSION MATCHES 0)
  
  SET (QT_MT_REQUIRED 1 )
  SET(QT_USE_QT3SUPPORT 1)

  INCLUDE( ${CMAKE_ROOT}/Modules/FindQt${DESIRED_QT_VERSION}.cmake )
ENDIF(DESIRED_QT_VERSION MATCHES 0)

SET(DESIRED_QT_VERSION 0 CACHE STRING "Pick a version of Qt to use: 3 or 4")

IF(DESIRED_QT_VERSION MATCHES 0)
  MESSAGE("Please set the DESIRED_QT_VERSION")
ELSE(DESIRED_QT_VERSION MATCHES 0)
  SET (QT_MT_REQUIRED 1 )
  SET(QT_USE_QT3SUPPORT 1)
  INCLUDE( ${CMAKE_ROOT}/Modules/FindQt${DESIRED_QT_VERSION}.cmake )
ENDIF(DESIRED_QT_VERSION MATCHES 0)


SET(DESIRED_QT_VERSION 0 CACHE STRING "Pick a version of Qt to use: 3 or 4")

IF(DESIRED_QT_VERSION MATCHES 0)
  MESSAGE("Please set the DESIRED_QT_VERSION")
ELSE(DESIRED_QT_VERSION MATCHES 0)
  
  SET (QT_MT_REQUIRED 1 )
  SET(QT_USE_QT3SUPPORT 1)

  INCLUDE( ${CMAKE_ROOT}/Modules/FindQt${DESIRED_QT_VERSION}.cmake )
ENDIF(DESIRED_QT_VERSION MATCHES 0)

SET(DESIRED_QT_VERSION 0 CACHE STRING "Pick a version of Qt to use: 3 or 4")

IF(DESIRED_QT_VERSION MATCHES 0)
  MESSAGE("Please set the DESIRED_QT_VERSION")
ELSE(DESIRED_QT_VERSION MATCHES 0)
  SET (QT_MT_REQUIRED 1 )
  SET(QT_USE_QT3SUPPORT 1)
  FIND_PACKAGE(Qt${DESIRED_QT_VERSION})
ENDIF(DESIRED_QT_VERSION MATCHES 0)


