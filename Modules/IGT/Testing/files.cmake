set(MODULE_TESTS
   mitkCameraVisualizationTest.cpp
   mitkClaronInterfaceTest.cpp
   mitkClaronToolTest.cpp
   mitkClaronTrackingDeviceTest.cpp
   mitkInternalTrackingToolTest.cpp
   mitkNavigationDataDisplacementFilterTest.cpp
   mitkNavigationDataLandmarkTransformFilterTest.cpp
   mitkNavigationDataObjectVisualizationFilterTest.cpp
   mitkNavigationDataTest.cpp
   mitkNavigationDataRecorderTest.cpp # see bug 16349
   mitkNavigationDataReferenceTransformFilterTest.cpp
   mitkNavigationDataSequentialPlayerTest.cpp
   mitkNavigationDataSourceTest.cpp
   mitkNavigationDataToMessageFilterTest.cpp
   mitkNavigationDataToNavigationDataFilterTest.cpp
   mitkNavigationDataToPointSetFilterTest.cpp
   mitkNavigationDataTransformFilterTest.cpp
   mitkNDIPassiveToolTest.cpp
   mitkNDIProtocolTest.cpp
   mitkNDITrackingDeviceTest.cpp
   mitkTimeStampTest.cpp
   mitkTrackingVolumeGeneratorTest.cpp
   mitkTrackingDeviceTest.cpp
   mitkTrackingToolTest.cpp
   mitkVirtualTrackingDeviceTest.cpp
   mitkNavigationDataPlayerTest.cpp # see bug 11636 (extend this test by microservices)
   mitkTrackingDeviceSourceTest.cpp
   mitkTrackingDeviceSourceConfiguratorTest.cpp
   mitkNavigationDataEvaluationFilterTest.cpp
   mitkTrackingTypesTest.cpp

   # ------------------ Navigation Tool Management Tests -------------------
   mitkNavigationToolStorageTest.cpp
   mitkNavigationToolTest.cpp
   mitkNavigationToolReaderAndWriterTest.cpp # see bug 16350
   mitkNavigationToolStorageSerializerAndDeserializerTest.cpp # see bug 16351
   # -----------------------------------------------------------------------
)

set(MODULE_CUSTOM_TESTS
  mitkNDIAuroraHardwareTest.cpp
  mitkNDIPolarisHardwareTest.cpp
  mitkClaronTrackingDeviceHardwareTest.cpp
)
