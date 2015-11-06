cmake_minimum_required(VERSION 2.6)

project( CenterImage )

FIND_PACKAGE ( ITK )
IF ( ITK_FOUND )
       INCLUDE( ${USE_ITK_FILE} )
ENDIF( ITK_FOUND )

add_executable( CenterImage CenterImage.cpp )

TARGET_LINK_LIBRARIES( CenterImage
  ITKIO ITKBasicFilters ITKNumerics ITKCommon
  )
