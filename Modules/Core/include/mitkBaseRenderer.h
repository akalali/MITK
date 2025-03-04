/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef BASERENDERER_H_HEADER_INCLUDED_C1CCA0F4
#define BASERENDERER_H_HEADER_INCLUDED_C1CCA0F4

#include "mitkCameraRotationController.h"
#include "mitkDataStorage.h"
#include "mitkPlaneGeometry.h"
#include "mitkPlaneGeometryData.h"
#include "mitkSliceNavigationController.h"
#include "mitkTimeGeometry.h"

#include "mitkBindDispatcherInteractor.h"
#include "mitkDispatcher.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <map>
#include <set>

// DEPRECATED
#include <mitkTimeSlicedGeometry.h>

namespace mitk
{
  class NavigationController;
  class SliceNavigationController;
  class CameraRotationController;
  class CameraController;
  class DataStorage;
  class Mapper;
  class BaseLocalStorageHandler;
  class KeyEvent;

  //##Documentation
  //## @brief Organizes the rendering process
  //##
  //## Organizes the rendering process. A Renderer contains a reference to a
  //## DataStorage and asks the mappers of the data objects to render
  //## the data into the renderwindow it is associated to.
  //##
  //## \#Render() checks if rendering is currently allowed by calling
  //## RenderWindow::PrepareRendering(). Initialization of a rendering context
  //## can also be performed in this method.
  //##
  //## The actual rendering code has been moved to \#Repaint()
  //## Both \#Repaint() and \#Update() are declared protected now.
  //##
  //## Note: Separation of the Repaint and Update processes (rendering vs
  //## creating a vtk prop tree) still needs to be worked on. The whole
  //## rendering process also should be reworked to use VTK based classes for
  //## both 2D and 3D rendering.
  //## @ingroup Renderer
  class MITKCORE_EXPORT BaseRenderer : public itk::Object
  {
  public:
    typedef std::map<vtkRenderWindow *, BaseRenderer *> BaseRendererMapType;
    static BaseRendererMapType baseRendererMap;

    static BaseRenderer *GetInstance(vtkRenderWindow *renWin);
    static void AddInstance(vtkRenderWindow *renWin, BaseRenderer *baseRenderer);
    static void RemoveInstance(vtkRenderWindow *renWin);

    static BaseRenderer *GetByName(const std::string &name);
    static vtkRenderWindow *GetRenderWindowByName(const std::string &name);

#pragma GCC visibility push(default)
    itkEventMacro(RendererResetEvent, itk::AnyEvent);
#pragma GCC visibility pop

    /** Standard class typedefs. */
    mitkClassMacroItkParent(BaseRenderer, itk::Object);

    BaseRenderer(const char *name = nullptr, vtkRenderWindow *renWin = nullptr);

    //##Documentation
    //## @brief MapperSlotId defines which kind of mapper (e.g. 2D or 3D) should be used.
    typedef int MapperSlotId;

    enum StandardMapperSlot
    {
      Standard2D = 1,
      Standard3D = 2
    };

    //##Documentation
    //## @brief Possible view directions for render windows.
    enum class ViewDirection
    {
      AXIAL = 0,
      SAGITTAL,
      CORONAL,
      THREE_D
    };

    virtual void SetDataStorage(DataStorage *storage); ///< set the datastorage that will be used for rendering

    //##Documentation
    //## return the DataStorage that is used for rendering
    virtual DataStorage::Pointer GetDataStorage() const { return m_DataStorage.GetPointer(); }
    //##Documentation
    //## @brief Access the RenderWindow into which this renderer renders.
    vtkRenderWindow *GetRenderWindow() const { return m_RenderWindow; }
    vtkRenderer *GetVtkRenderer() const { return m_VtkRenderer; }
    //##Documentation
    //## @brief Returns the Dispatcher which handles Events for this BaseRenderer
    Dispatcher::Pointer GetDispatcher() const;

    //##Documentation
    //## @brief Default mapper id to use.
    static const MapperSlotId defaultMapper;

    //##Documentation
    //## @brief Do the rendering and flush the result.
    virtual void Paint();

    //##Documentation
    //## @brief Initialize the RenderWindow. Should only be called from RenderWindow.
    virtual void Initialize();

    //##Documentation
    //## @brief Called to inform the renderer that the RenderWindow has been resized.
    virtual void Resize(int w, int h);

    //##Documentation
    //## @brief Initialize the renderer with a RenderWindow (@a renderwindow).
    virtual void InitRenderer(vtkRenderWindow *renderwindow);

    //##Documentation
    //## @brief Set the initial size. Called by RenderWindow after it has become
    //## visible for the first time.
    virtual void InitSize(int w, int h);

    //##Documentation
    //## @brief Draws a point on the widget.
    //## Should be used during conferences to show the position of the remote mouse
    virtual void DrawOverlayMouse(Point2D &p2d);

    //##Documentation
    //## @brief Set/Get the WorldGeometry (m_WorldGeometry) for 3D and 2D rendering, that describing the
    //## (maximal) area to be rendered.
    //##
    //## Depending of the type of the passed BaseGeometry more or less information can be extracted:
    //## \li if it is a PlaneGeometry (which is a sub-class of BaseGeometry), m_CurrentWorldPlaneGeometry is
    //## also set to point to it. m_WorldTimeGeometry is set to nullptr.
    //## \li if it is a TimeGeometry, m_WorldTimeGeometry is also set to point to it.
    //## If m_WorldTimeGeometry contains instances of SlicedGeometry3D, m_CurrentWorldPlaneGeometry is set to
    //## one of geometries stored in the SlicedGeometry3D according to the value of m_Slice;  otherwise
    //## a PlaneGeometry describing the top of the bounding-box of the BaseGeometry is set as the
    //## m_CurrentWorldPlaneGeometry.
    //## \li otherwise a PlaneGeometry describing the top of the bounding-box of the BaseGeometry
    //## is set as the m_CurrentWorldPlaneGeometry. m_WorldTimeGeometry is set to nullptr.
    //## @todo add calculation of PlaneGeometry describing the top of the bounding-box of the BaseGeometry
    //## when the passed BaseGeometry is not sliced.
    //## \sa m_WorldGeometry
    //## \sa m_WorldTimeGeometry
    //## \sa m_CurrentWorldPlaneGeometry
    virtual void SetWorldGeometry3D(const BaseGeometry *geometry);
    virtual void SetWorldTimeGeometry(const mitk::TimeGeometry *geometry);

    /**
    * \deprecatedSince{2013_09} Please use TimeGeometry instead of TimeSlicedGeometry. For more information see
    * http://www.mitk.org/Development/Refactoring%20of%20the%20Geometry%20Classes%20-%20Part%201
    */
    DEPRECATED(void SetWorldGeometry3D(TimeSlicedGeometry *geometry));

    itkGetConstObjectMacro(WorldTimeGeometry, TimeGeometry)

      //##Documentation
      //## @brief Get the current 3D-worldgeometry (m_CurrentWorldGeometry) used for 3D-rendering
      itkGetConstObjectMacro(CurrentWorldGeometry, BaseGeometry)

      //##Documentation
      //## @brief Get the current 2D-worldgeometry (m_CurrentWorldPlaneGeometry) used for 2D-rendering
      itkGetConstObjectMacro(CurrentWorldPlaneGeometry, PlaneGeometry)
      /**
      * \deprecatedSince{2014_10} Please use GetCurrentWorldPlaneGeometry
      */
      DEPRECATED(const PlaneGeometry *GetCurrentWorldGeometry2D())
    {
      return GetCurrentWorldPlaneGeometry();
    };

    //##Documentation
    //## Calculates the bounds of the DataStorage (if it contains any valid data),
    //## creates a geometry from these bounds and sets it as world geometry of the renderer.
    //##
    //## Call this method to re-initialize the renderer to the current DataStorage
    //## (e.g. after loading an additional dataset), to ensure that the view is
    //## aligned correctly.
    //## \warn This is not implemented yet.
    virtual bool SetWorldGeometryToDataStorageBounds() { return false; }
    //##Documentation
    //## @brief Set/Get m_Slice which defines together with m_TimeStep the 2D geometry
    //## stored in m_WorldTimeGeometry used as m_CurrentWorldPlaneGeometry
    //##
    //## \sa m_Slice
    virtual void SetSlice(unsigned int slice);

    itkGetConstMacro(Slice, unsigned int)

      //##Documentation
      //## @brief Set/Get m_TimeStep which defines together with m_Slice the 2D geometry
      //## stored in m_WorldTimeGeometry used as m_CurrentWorldPlaneGeometry
      //##
      //## \sa m_TimeStep
      virtual void SetTimeStep(unsigned int timeStep);

    itkGetConstMacro(TimeStep, unsigned int)

      //##Documentation
      //## @brief Get the time-step of a BaseData object which
      //## exists at the time of the currently displayed content
      //##
      //## Returns -1 or mitk::BaseData::m_TimeSteps if there
      //## is no data at the current time.
      //## \sa GetTimeStep, m_TimeStep
      int GetTimeStep(const BaseData *data) const;

    //##Documentation
    //## @brief Get the time in ms of the currently displayed content
    //##
    //## \sa GetTimeStep, m_TimeStep
    ScalarType GetTime() const;

    //##Documentation
    //## @brief SetWorldGeometry is called according to the geometrySliceEvent,
    //## which is supposed to be a SliceNavigationController::GeometrySendEvent
    virtual void SetGeometry(const itk::EventObject &geometrySliceEvent);

    //##Documentation
    //## @brief UpdateWorldGeometry is called to re-read the 2D geometry from the
    //## slice navigation controller
    virtual void UpdateGeometry(const itk::EventObject &geometrySliceEvent);

    //##Documentation
    //## @brief SetSlice is called according to the geometrySliceEvent,
    //## which is supposed to be a SliceNavigationController::GeometrySliceEvent
    virtual void SetGeometrySlice(const itk::EventObject &geometrySliceEvent);

    //##Documentation
    //## @brief SetTimeStep is called according to the geometrySliceEvent,
    //## which is supposed to be a SliceNavigationController::GeometryTimeEvent
    virtual void SetGeometryTime(const itk::EventObject &geometryTimeEvent);

    //##Documentation
    //## @brief Get a DataNode pointing to a data object containing the current 2D-worldgeometry
    // m_CurrentWorldPlaneGeometry (for 2D rendering)
    itkGetObjectMacro(CurrentWorldPlaneGeometryNode, DataNode)
      /**
      * \deprecatedSince{2014_10} Please use GetCurrentWorldPlaneGeometryNode
      */
      DEPRECATED(DataNode *GetCurrentWorldGeometry2DNode())
    {
      return GetCurrentWorldPlaneGeometryNode();
    };

    //##Documentation
    //## @brief Sets timestamp of CurrentWorldPlaneGeometry and forces so reslicing in that renderwindow
    void SendUpdateSlice();

    //##Documentation
    //## @brief Get timestamp of last call of SetCurrentWorldPlaneGeometry
    unsigned long GetCurrentWorldPlaneGeometryUpdateTime() { return m_CurrentWorldPlaneGeometryUpdateTime; }
    /**
    * \deprecatedSince{2014_10} Please use GetCurrentWorldPlaneGeometryUpdateTime
    */
    DEPRECATED(unsigned long GetCurrentWorldGeometry2DUpdateTime())
    {
      return GetCurrentWorldPlaneGeometryUpdateTime();
    };
    //##Documentation
    //## @brief Get timestamp of last change of current TimeStep
    unsigned long GetTimeStepUpdateTime() { return m_TimeStepUpdateTime; }
    //##Documentation
    //## @brief Perform a picking: find the x,y,z world coordinate of a
    //## display x,y coordinate.
    //## @warning Has to be overwritten in subclasses for the 3D-case.
    //##
    //## Implemented here only for 2D-rendering
    virtual void PickWorldPoint(const Point2D &diplayPosition, Point3D &worldPosition) const = 0;

    /** \brief Determines the object (mitk::DataNode) closest to the current
    * position by means of picking
    *
    * \warning Implementation currently empty for 2D rendering; intended to be
    * implemented for 3D renderers */
    virtual DataNode *PickObject(const Point2D & /*displayPosition*/, Point3D & /*worldPosition*/) const
    {
      return nullptr;
    }

    //##Documentation
    //## @brief Get the MapperSlotId to use.
    itkGetMacro(MapperID, MapperSlotId) itkGetConstMacro(MapperID, MapperSlotId)

      //##Documentation
      //## @brief Set the MapperSlotId to use.
      itkSetMacro(MapperID, MapperSlotId)

        virtual int *GetSize() const;
    virtual int *GetViewportSize() const;

    void SetSliceNavigationController(SliceNavigationController *SlicenavigationController);
    itkGetObjectMacro(CameraController, CameraController)
      itkGetObjectMacro(SliceNavigationController, SliceNavigationController)
        itkGetObjectMacro(CameraRotationController, CameraRotationController)

          itkGetMacro(EmptyWorldGeometry, bool)

      //##Documentation
      //## @brief Tells if the displayed region is shifted and rescaled if the render window is resized.
      itkGetMacro(KeepDisplayedRegion, bool)
      //##Documentation
      //## @brief Tells if the displayed region should be shifted and rescaled if the render window is resized.
      itkSetMacro(KeepDisplayedRegion, bool)

      //##Documentation
      //## @brief get the name of the Renderer
      //## @note
      const char *GetName() const
    {
      return m_Name.c_str();
    }

    //##Documentation
    //## @brief get the x_size of the RendererWindow
    //## @note
    int GetSizeX() const { return GetSize()[0]; }
    //##Documentation
    //## @brief get the y_size of the RendererWindow
    //## @note
    int GetSizeY() const { return GetSize()[1]; }
    const double *GetBounds() const;

    void RequestUpdate();
    void ForceImmediateUpdate();

    /** Returns number of mappers which are visible and have level-of-detail
    * rendering enabled */
    unsigned int GetNumberOfVisibleLODEnabledMappers() const;

    //##Documentation
    //## @brief This method converts a display point to the 3D world index
    //## using the geometry of the renderWindow.
    void DisplayToWorld(const Point2D &displayPoint, Point3D &worldIndex) const;

    //##Documentation
    //## @brief This method converts a display point to the 2D world index, mapped onto the display plane
    //## using the geometry of the renderWindow.
    void DisplayToPlane(const Point2D &displayPoint, Point2D &planePointInMM) const;

    //##Documentation
    //## @brief This method converts a 3D world index to the display point
    //## using the geometry of the renderWindow.
    void WorldToDisplay(const Point3D &worldIndex, Point2D &displayPoint) const;

    //##Documentation
    //## @brief This method converts a 3D world index to the point on the viewport
    //## using the geometry of the renderWindow.
    void WorldToView(const Point3D &worldIndex, Point2D &viewPoint) const;

    //##Documentation
    //## @brief This method converts a 2D plane coordinate to the display point
    //## using the geometry of the renderWindow.
    void PlaneToDisplay(const Point2D &planePointInMM, Point2D &displayPoint) const;

    //##Documentation
    //## @brief This method converts a 2D plane coordinate to the point on the viewport
    //## using the geometry of the renderWindow.
    void PlaneToView(const Point2D &planePointInMM, Point2D &viewPoint) const;


    double GetScaleFactorMMPerDisplayUnit() const;

    Point2D GetDisplaySizeInMM() const;
    Point2D GetViewportSizeInMM() const;

    Point2D GetOriginInMM() const;

    itkGetConstMacro(ConstrainZoomingAndPanning, bool) virtual void SetConstrainZoomingAndPanning(bool constrain);

    /**
    * \brief Provides (1) world coordinates for a given mouse position and (2)
    * translates mousePosition to Display coordinates
    * \deprecated Map2DRendererPositionTo3DWorldPosition is deprecated. Please use DisplayToWorld instead.
    */
    DEPRECATED(virtual Point3D Map2DRendererPositionTo3DWorldPosition(const Point2D &mousePosition) const);

  protected:
    ~BaseRenderer() override;

    //##Documentation
    //## @brief Call update of all mappers. To be implemented in subclasses.
    virtual void Update() = 0;

    vtkRenderWindow *m_RenderWindow;
    vtkRenderer *m_VtkRenderer;

    //##Documentation
    //## @brief MapperSlotId to use. Defines which kind of mapper (e.g., 2D or 3D) shoud be used.
    MapperSlotId m_MapperID;

    //##Documentation
    //## @brief The DataStorage that is used for rendering.
    DataStorage::Pointer m_DataStorage;

    //##Documentation
    //## @brief Timestamp of last call of Update().
    unsigned long m_LastUpdateTime;

    //##Documentation
    //## @brief CameraController for 3D rendering
    //## @note preliminary.
    itk::SmartPointer<CameraController> m_CameraController;
    SliceNavigationController::Pointer m_SliceNavigationController;
    CameraRotationController::Pointer m_CameraRotationController;

    //##Documentation
    //## @brief Sets m_CurrentWorldPlaneGeometry
    virtual void SetCurrentWorldPlaneGeometry(const PlaneGeometry *geometry2d);
    /**
    * \deprecatedSince{2014_10} Please use SetCurrentWorldPlaneGeometry
    */
    DEPRECATED(void SetCurrentWorldGeometry2D(PlaneGeometry *geometry2d)) { SetCurrentWorldPlaneGeometry(geometry2d); };
    //##Documentation
    //## @brief Sets m_CurrentWorldGeometry
    virtual void SetCurrentWorldGeometry(const BaseGeometry *geometry);

  private:
    //##Documentation
    //## m_WorldTimeGeometry is set by SetWorldGeometry if the passed BaseGeometry is a
    //## TimeGeometry (or a sub-class of it). If it contains instances of SlicedGeometry3D,
    //## m_Slice and m_TimeStep (set via SetSlice and SetTimeStep, respectively) define
    //## which 2D geometry stored in m_WorldTimeGeometry (if available)
    //## is used as m_CurrentWorldPlaneGeometry.
    //## \sa m_CurrentWorldPlaneGeometry
    TimeGeometry::ConstPointer m_WorldTimeGeometry;

    //##Documentation
    //## Pointer to the current 3D-worldgeometry.
    BaseGeometry::ConstPointer m_CurrentWorldGeometry;

    //##Documentation
    //## Pointer to the current 2D-worldgeometry. The 2D-worldgeometry
    //## describes the maximal area (2D manifold) to be rendered in case we
    //## are doing 2D-rendering.
    //## It is const, since we are not allowed to change it (it may be taken
    //## directly from the geometry of an image-slice and thus it would be
    //## very strange when suddenly the image-slice changes its geometry).
    PlaneGeometry::Pointer m_CurrentWorldPlaneGeometry;

    //##Documentation
    //## Defines together with m_Slice which 2D geometry stored in m_WorldTimeGeometry
    //## is used as m_CurrentWorldPlaneGeometry: m_WorldTimeGeometry->GetPlaneGeometry(m_Slice, m_TimeStep).
    //## \sa m_WorldTimeGeometry
    unsigned int m_Slice;
    //##Documentation
    //## Defines together with m_TimeStep which 2D geometry stored in m_WorldTimeGeometry
    //## is used as m_CurrentWorldPlaneGeometry: m_WorldTimeGeometry->GetPlaneGeometry(m_Slice, m_TimeStep).
    //## \sa m_WorldTimeGeometry
    unsigned int m_TimeStep;

    //##Documentation
    //## @brief timestamp of last call of SetWorldGeometry
    itk::TimeStamp m_CurrentWorldPlaneGeometryUpdateTime;

    //##Documentation
    //## @brief timestamp of last change of the current time step
    itk::TimeStamp m_TimeStepUpdateTime;

    //##Documentation
    //## @brief Helper class which establishes connection between Interactors and Dispatcher via a common DataStorage.
    BindDispatcherInteractor *m_BindDispatcherInteractor;

    //##Documentation
    //## @brief Tells if the displayed region should be shifted or rescaled if the render window is resized.
    bool m_KeepDisplayedRegion;

  protected:
    void PrintSelf(std::ostream &os, itk::Indent indent) const override;

    //##Documentation
    //## Data object containing the m_CurrentWorldPlaneGeometry defined above.
    PlaneGeometryData::Pointer m_CurrentWorldPlaneGeometryData;

    //##Documentation
    //## DataNode objects containing the m_CurrentWorldPlaneGeometryData defined above.
    DataNode::Pointer m_CurrentWorldPlaneGeometryNode;

    //##Documentation
    //## @brief test only
    unsigned long m_CurrentWorldPlaneGeometryTransformTime;

    std::string m_Name;

    double m_Bounds[6];

    bool m_EmptyWorldGeometry;

    typedef std::set<Mapper *> LODEnabledMappersType;

    /** Number of mappers which are visible and have level-of-detail
    * rendering enabled */
    unsigned int m_NumberOfVisibleLODEnabledMappers;

    // Local Storage Handling for mappers

  protected:
    std::list<mitk::BaseLocalStorageHandler *> m_RegisteredLocalStorageHandlers;

    bool m_ConstrainZoomingAndPanning;

  public:
    void RemoveAllLocalStorages();
    void RegisterLocalStorageHandler(mitk::BaseLocalStorageHandler *lsh);
    void UnregisterLocalStorageHandler(mitk::BaseLocalStorageHandler *lsh);
  };
} // namespace mitk

#endif /* BASERENDERER_H_HEADER_INCLUDED_C1CCA0F4 */
