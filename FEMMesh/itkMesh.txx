/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkMesh.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkMesh_txx
#define _itkMesh_txx

#include "itkMesh.h"
#include "itkObjectFactory.h"
#include "itkProcessObject.h"
#include <algorithm>

namespace itk
{
namespace fem
{
  
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Number Of Points: " 
     << ((m_PointsContainer.GetPointer()) ?  m_PointsContainer->Size() : 0) << std::endl;
    os << indent << "Number Of Cell Links: " 
       << ((m_CellLinksContainer) ?  m_CellLinksContainer->Size() : 0) << std::endl;
    os << indent << "Number Of Cells: " 
       << ((m_CellsContainer) ?  m_CellsContainer->Size() : 0) << std::endl;
    os << indent << "Size of Cell Data Container: " 
       << ((m_CellDataContainer) ?  m_CellDataContainer->Size() : 0) << std::endl;
    os << indent << "Size of boundary container vector: " << m_BoundariesContainers.size() << std::endl;
    os << indent << "Size of boundaries data container vector: " 
       << m_BoundaryDataContainers.size() << std::endl;
    os << indent << "Number of explicet cell boundary assignments: " 
       << m_BoundaryAssignmentsContainers.size() << std::endl;

  os << indent << "Requested Number Of Regions: " 
  << m_RequestedNumberOfRegions << std::endl;
  os << indent << "Requested Region: " << m_RequestedRegion << std::endl;
  os << indent << "Maximum Number Of Regions: " 
     << m_MaximumNumberOfRegions << std::endl;

}


/**
 * Access routine to set the cell links container.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetCellLinks(CellLinksContainer* cellLinks)
{
  itkDebugMacro("setting CellLinks container to " << cellLinks);
  if(m_CellLinksContainer != cellLinks)
    {
    m_CellLinksContainer = cellLinks;
    this->Modified();
    }
}

/**
 * Access routine to get the cell links container.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::CellLinksContainerPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCellLinks(void)
{
  itkDebugMacro("returning CellLinks container of "
                << m_CellLinksContainer );
  return m_CellLinksContainer;
}


/**
 * Access routine to set the cells container.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetCells(CellsContainer* cells)
{
  itkDebugMacro("setting Cells container to " << cells);
  if(m_CellsContainer != cells)
    {
    m_CellsContainer = cells;
    this->Modified();
    }
}


/**
 * Access routine to get the cells container.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::CellsContainerPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCells(void)
{
  itkDebugMacro("returning Cells container of " << m_CellsContainer );
  return m_CellsContainer;
}


/**
 * Access routine to set the cell data container.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetCellData(CellDataContainer* cellData)
{
  itkDebugMacro("setting CellData container to " << cellData);
  if(m_CellDataContainer != cellData)
    {
    m_CellDataContainer = cellData;
    this->Modified();
    }
}


/**
 * Access routine to get the cell data container.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::CellDataContainerPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCellData(void)
{
  itkDebugMacro("returning CellData container of "
                << m_CellDataContainer );
  return m_CellDataContainer;
}


/**
 * Access routine to set the boundaries container for a given dimension.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetBoundaries(int dimension, BoundariesContainer* boundaries)
{
  itkDebugMacro("setting Boundaries[" << dimension
                << "] container to " << boundaries);
  if(m_BoundariesContainers[dimension] != boundaries)
    {
    m_BoundariesContainers[dimension] = boundaries;
    this->Modified();
    }
}



/**
 * Access routine to get the boundaries container for a given dimension.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::BoundariesContainerPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetBoundaries(int dimension)
{
  itkDebugMacro("returning Boundaries[" << dimension
                << "] container of "
                << m_BoundariesContainers[dimension]);
  return m_BoundariesContainers[dimension];
}


/**
 * Access routine to set the boundary data container for a given dimension.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetBoundaryData(int dimension, BoundaryDataContainer* boundaryData)
{
  itkDebugMacro("setting BoundaryData[" << dimension
                << "] container to " << boundaryData);
  if(m_BoundaryDataContainers[dimension] != boundaryData)
    {
    m_BoundaryDataContainers[dimension] = boundaryData;
    this->Modified();
    }
}


/**
 * Access routine to get the boundary data container for a given dimension.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::BoundaryDataContainerPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetBoundaryData(int dimension)
{
  itkDebugMacro("returning BoundaryData[" << dimension
                << "] container of "
                << m_BoundaryDataContainers[dimension]);
  return m_BoundaryDataContainers[dimension];
}


/**
 * Access routine to set the boundary assignment container for a given
 * dimension.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetBoundaryAssignments(
  int dimension,
  BoundaryAssignmentsContainer* boundaryAssignments)
{
  itkDebugMacro("setting BoundaryAssignments[" << dimension
                << "] container to " << boundaryAssignments);
  if(m_BoundaryAssignmentsContainers[dimension] != boundaryAssignments)
    {
    m_BoundaryAssignmentsContainers[dimension] = boundaryAssignments;
    this->Modified();
    }
}


/**
 * Access routine to get the boundary assignment container for a given
 * dimension.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::BoundaryAssignmentsContainerPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetBoundaryAssignments(int dimension)
{
  itkDebugMacro("returning BoundaryAssignments[" << dimension
                << "] container of "
                << m_BoundaryAssignmentsContainers[dimension]);
  return m_BoundaryAssignmentsContainers[dimension];
}


/**
 * Assign a cell to a cell identifier.  If a spot for the cell identifier
 * does not exist, it will be created automatically.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetCell(CellIdentifier cellId, Cell* cell)
{
  /**
   * Make sure a cells container exists.
   */
  if( !m_CellsContainer )
    {
    this->SetCells(CellsContainer::New());
    }
  
  /**
   * Insert the cell into the container with the given identifier.
   */
  m_CellsContainer->InsertElement(cellId, cell);
}


/**
 * Check if a cell exists for a given cell identifier.  If a spot for
 * the cell identifier exists, "cell" is set, and true is returned.
 * Otherwise, false is returned, and "cell" is not modified.
 * If "cell" is NULL, then it is never set, but the existence of the cell
 * is still returned.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCell(CellIdentifier cellId, CellPointer* cell) const
{
  /**
   * If the cells container doesn't exist, then the cell doesn't exist.
   */
  if( m_CellsContainer == 0 )
    return false;
  
  /**
   * Ask the container if the cell identifier exists.
   */
  return m_CellsContainer->GetElementIfIndexExists(cellId, cell);
}


/**
 * Assign data to a cell identifier.  If a spot for the cell identifier
 * does not exist, it will be created automatically.  There is no check if
 * a cell with the same identifier exists.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetCellData(CellIdentifier cellId, CellPixelType data)
{
  /**
   * Make sure a cell data container exists.
   */
  if( !m_CellDataContainer )
    {
    this->SetCellData(CellDataContainer::New());
    }

  /**
   * Insert the cell data into the container with the given identifier.
   */
  m_CellDataContainer->InsertElement(cellId, data);
}


/**
 * Check if cell data exists for a given cell identifier.  If a spot for
 * the cell identifier exists, "data" is set, and true is returned.
 * Otherwise, false is returned, and "data" is not modified.
 * If "data" is NULL, then it is never set, but the existence of the cell
 * data is still returned.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCellData(CellIdentifier cellId, CellPixelType* data) const
{
  /**
   * If the cell data container doesn't exist, then the cell data doesn't
   * either.
   */
  if( !m_CellDataContainer )
    return false;
  
  /**
   * Ask the container if the cell identifier exists.
   */
  return m_CellDataContainer->GetElementIfIndexExists(cellId, data);
}


/**
 * Assign a boundary to a boundary identifier.  If a spot for the boundary
 * identifier does not exist, it will be created automatically.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetBoundary(int dimension, BoundaryIdentifier boundaryId, 
                             BoundaryType* boundary)
{
  /**
   * Make sure a boundaries container exists.
   */
  if( !m_BoundariesContainers[dimension] )
    {
    this->SetBoundaries(dimension, BoundariesContainer::New());
    }
  
  /**
   * Insert the boundary into the container with the given identifier.
   */
  m_BoundariesContainers[dimension]->InsertElement(boundaryId, boundary);
}


/**
 * Check if a boundary exists for a given boundary identifier.  If a spot for
 * the boundary identifier exists, "boundary" is set, and true is returned.
 * Otherwise, false is returned, and "boundary" is not modified.
 * If "boundary" is NULL, then it is never set, but the existence of the
 * boundary is still returned.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::GetBoundary(int dimension, BoundaryIdentifier boundaryId,
              BoundaryPointer* boundary) const
{
  /**
   * If the boundaries container doesn't exist, then the boundary
   * doesn't exist.
   */
  if( !m_BoundariesContainers[dimension] )
    return false;
  
  /**
   * Ask the container if the boundary identifier exists.
   */
  return m_BoundariesContainers[dimension]->
    GetElementIfIndexExists(boundaryId, boundary);
}


/**
 * Assign data to a boundary identifier.  If a spot for the boundary identifier
 * does not exist, it will be created automatically.  There is no check if
 * a boundary with the same identifier exists.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetBoundaryData(int dimension, BoundaryIdentifier boundaryId, CellPixelType data)
{
  /**
   * Make sure a boundary data container exists.
   */
  if( !m_BoundaryDataContainers[dimension] )
    {
    this->SetBoundaryData(dimension, BoundaryDataContainer::New());
    }

  /**
   * Insert the boundary data into the container with the given identifier.
   */
  m_BoundaryDataContainers[dimension]->InsertElement(boundaryId, data);
}


/**
 * Check if boundary data exists for a given boundary identifier.  If a spot
 * for the boundary identifier exists, "data" is set, and true is returned.
 * Otherwise, false is returned, and "data" is not modified.
 * If "data" is NULL, then it is never set, but the existence of the boundary
 * data is still returned.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::GetBoundaryData(int dimension, BoundaryIdentifier boundaryId,
                  CellPixelType* data) const
{
  /**
   * If the boundary data container doesn't exist, then the boundary
   * data doesn't either.
   */
  if( !m_BoundaryDataContainers[dimension] )
    return false;
  
  /**
   * Ask the container if the boundary identifier exists.
   */
  return m_BoundaryDataContainers[dimension]->GetElementIfIndexExists(boundaryId, data);
}


/**
 * Create an explicit boundary assignment.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::SetBoundaryAssignment(int dimension, CellIdentifier cellId,
                        CellFeatureIdentifier featureId,
                        BoundaryIdentifier boundaryId)
{
  BoundaryAssignmentIdentifier assignId(cellId, featureId);
    
  /**
   * Make sure a boundary assignment container exists for the given dimension.
   */
  if( !m_BoundaryAssignmentsContainers[dimension] )
    {
    this->SetBoundaryAssignments(
      dimension, BoundaryAssignmentsContainer::New());
    }

  /**
   * Insert the boundary assignment into the container with the given
   * assignment identifier in the given dimension.
   */
  m_BoundaryAssignmentsContainers[dimension]->InsertElement(assignId, boundaryId);
}


/**
 * Check if an explicit boundary assignment exists.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::GetBoundaryAssignment(int dimension, CellIdentifier cellId,
                        CellFeatureIdentifier featureId,
                        BoundaryIdentifier* boundaryId) const
{
  BoundaryAssignmentIdentifier assignId(cellId, featureId);  

  /**
   * If the boundary assignments container for the given dimension doesn't
   * exist, then the boundary assignment doesn't either.
   */
  if( !m_BoundaryAssignmentsContainers[dimension] )
    return false;
  
  /**
   * Ask the container if the boundary assignment exists.
   */
  return m_BoundaryAssignmentsContainers[dimension]->
    GetElementIfIndexExists(assignId, boundaryId);
}


/**
 * Remove an explicit boundary assignment if it exists.
 * Returns whether the assignment was found at all.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::RemoveBoundaryAssignment(int dimension, CellIdentifier cellId,
                           CellFeatureIdentifier featureId)
{
  BoundaryAssignmentIdentifier assignId(cellId, featureId);

  /**
   * If the boundary assignments container for the given dimension doesn't
   * exist, then the boundary assignment doesn't either.
   */
  if( !m_BoundaryAssignmentsContainers[dimension] )
    return false;
  
  /**
   * Ask the container if the boundary assignment exists, and delete it if
   * so.
   */
  if(m_BoundaryAssignmentsContainers[dimension]->IndexExists(assignId))
    {
    m_BoundaryAssignmentsContainers[dimension]->DeleteIndex(assignId);
    return true;
    }
  else return false;  
}


/**
 * Get the number of cell boundary features of the given topological dimension
 * on the cell with the given identifier.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::CellFeatureCount 
Mesh<TPixelType, VDimension, TMeshTraits>
::GetNumberOfCellBoundaryFeatures(int dimension, CellIdentifier cellId) const
{
  /**
   * Make sure the cell container exists and contains the given cell Id.
   */
  if( !m_CellsContainer ) return 0;
  if(!m_CellsContainer->IndexExists(cellId)) return 0;
  
  /**
   * Ask the cell for its boundary count of the given dimension.
   */
  return m_CellsContainer->GetElement(cellId)->GetNumberOfBoundaryFeatures(dimension);
}


/**
 * Copy the geometric and topological structure of the given input mesh.
 * The copying is done via reference counting.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::PassStructure(Self* in_mesh)
{
  // IMPLEMENT ME
}


/**
 * Get the number of cells in the CellsContainer.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
unsigned long
Mesh<TPixelType, VDimension, TMeshTraits>
::GetNumberOfCells(void)
{  
  if ( ! m_CellsContainer )
    {
    return 0;
    }
  else
    {
    return m_CellsContainer->Size();
    }
}


/**
 * Get the bounding box of the cell with the given identifier.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::BoundingBoxPointer 
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCellBoundingBox(CellIdentifier cellId, Mesh<TPixelType, VDimension, TMeshTraits>::BoundingBoxPointer bbox)
{
  bbox->SetPoints(this->GetPoints());
  return bbox;
}


/**
 * Given the geometric coordinates of a point and a squared tolerance,
 * locate .....COMMENT ME.....
 */
#if 0
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::FindCell(CoordRep coords[PointDimension], ..FINISH ME..)
#endif

/**
 * Restore the Mesh to its initial state.  Useful for data pipeline updates
 * without memory re-allocation.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::Initialize(void)
{
  Superclass::Initialize();

  m_CellsContainer = 0;
  m_CellDataContainer = 0;
  m_CellLinksContainer = 0;
  
}
  
  
/**
 * Get the boundary feature of the given dimension of the given cell
 * corresponding to the given feature identifier.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>::BoundaryPointer
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCellBoundaryFeature(int dimension, CellIdentifier cellId,
                         CellFeatureIdentifier featureId) const
{
  /**
   * First check if the boundary has been explicitly assigned.
   */
  BoundaryType::Pointer boundary;
  if(GetAssignedCellBoundaryIfOneExists(dimension, cellId, featureId, &boundary))
    {
    return boundary;
    }
  
  /**
   * It was not explicitly assigned, so ask the cell to construct it.
   */
  if((m_CellsContainer != 0) && m_CellsContainer->IndexExists(cellId))
    {
    return m_CellsContainer->GetElement(cellId)->
      GetBoundaryFeature(dimension, featureId);
    }
  
  /**
   * The cell did not exist, so just give up.
   */
  return CellPointer(0);
}


/**
 * Get the set of cells neighboring the given cell across the given boundary
 * feature.  Returns the number of neighbors found.  If cellSet is not
 * NULL, the set of cell pointers is filled in with identifiers of the
 * neighboring cells.
 *
 * NOTE: We would like to change this to use an "output iterator"
 * (in STL fashion) instead of an actual container to return the neighbor
 * identifiers.  This requires templated member support by the compiler,
 * though, and we are not sure how wide-spread this support is.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
unsigned long
Mesh<TPixelType, VDimension, TMeshTraits>
::GetCellBoundaryFeatureNeighbors(int dimension, CellIdentifier cellId,
                                  CellFeatureIdentifier featureId,
                                  std::set<CellIdentifier>* cellSet)
{
  /**
   * Sanity check on mesh status.
   */
  if( !m_PointsContainer || !m_CellsContainer ||
     (!m_CellsContainer->IndexExists(cellId)))
    {
    /**
     * TODO: Throw EXCEPTION here?
     */
    return 0;
    }
  
  /**
   * First check if the boundary has been explicitly assigned.
   */
  BoundaryPointer boundary;
  if(this->GetAssignedCellBoundaryIfOneExists(
    dimension, cellId, featureId, &boundary))
    {
    /**
     * Explicitly assigned boundary found.  Loop through its UsingCells,
     * and put them in the output set except for the cell through which the
     * request was made.  First we empty the output set.
     */
    if(cellSet != 0)
      {
      cellSet->erase(cellSet->begin(), cellSet->end());
      
      for(BoundaryType::UsingCellsContainerIterator usingCell = 
            boundary->UsingCellsBegin() ;
          usingCell != boundary->UsingCellsEnd() ; ++usingCell)
        {
        if((*usingCell) != cellId)
          {
          cellSet->insert(*usingCell);
          }
        }
      }
    /**
     * The number of neighboring cells is the number of cells using the
     * boundary less one for the cell through which the request was made.
     */
    return (boundary->GetNumberOfUsingCells()-1);
    }
  
  /**
   * An explicit assignment for the boundary was not found.  We use set
   * operations through point neighboring information to get the neighbors.
   * This requires that the CellLinks be built.
   */
  if( !m_CellLinksContainer )
    {
    this->BuildCellLinks();
    }
  else if((m_PointsContainer->GetMTime() > m_CellLinksContainer->GetMTime()) ||
          (m_CellsContainer->GetMTime()  > m_CellLinksContainer->GetMTime()))
    {
    this->BuildCellLinks();
    }
  
  /**
   * Cell links are up to date. We can proceed with the set operations.
   * We need to intersect the CellLinks sets for each point on the boundary
   * feature.
   */
  
  /**
   * First, ask the cell to construct the boundary feature so we can look
   * at its points.
   */
  boundary =
    m_CellsContainer->GetElement(cellId)->GetBoundaryFeature(dimension, featureId);
  
  /**
   * Now get the cell links for the first point.  Also allocate a second set
   * for temporary storage during set intersections below.
   */
  BoundaryType::PointIdConstIterator pointId = boundary->PointIdsBegin();
  PointCellLinksContainer*  currentCells =
    new PointCellLinksContainer(m_CellLinksContainer->GetElement(*pointId++));
  PointCellLinksContainer*  tempCells = new PointCellLinksContainer();
  
  /**
   * Next, loop over the other points, and intersect their cell links with
   * the current result.  We maintain "currentCells" as a pointer to the
   * current cell set instead of a set itself to prevent an extra copy of
   * the temporary set after each intersection.
   */
  while(pointId != boundary->PointIdsEnd())
    {
    /**
     * Clean out temporary cell set from previous iteration.
     */
    tempCells->erase(tempCells->begin(), tempCells->end());
    
    /**
     * Perform the intersection.
     */
    std::set_intersection(m_CellLinksContainer->CreateElementAt(*pointId).begin(),
                          m_CellLinksContainer->CreateElementAt(*pointId).end(),
                          currentCells->begin(),
                          currentCells->end(),
                          std::inserter(*tempCells, tempCells->begin()));
    
    /**
     * Switch the cell set pointers to make the intersection result the
     * current set.
     */
    std::swap(currentCells, tempCells);
    
    /**
     * Move on to the next point.
     */
    ++pointId;
    }
  
  /**
   * Don't need the second set anymore.
   */
  delete tempCells;
  
  /**
   * Now we have a set of all the cells which share all the points on the
   * boundary feature.  We simply need to copy this set to the output cell
   * set, less the cell through which the request was made.
   */
  currentCells->erase(cellId);
  if(cellSet != 0)
    {
    *cellSet = *currentCells;    
    }
  
  /**
   * Don't need the cell set anymore.
   */
  delete currentCells;
  
  /**
   * Return the number of neighboring cells that were put into the set.
   */
  return cellSet->size();
}


/**
 * Check if there is an explicitly assigned boundary feature for the
 * given dimension and cell- and cell-feature-identifiers.  If there is,
 * a pointer to it is given back through "boundary" (if it isn't 0) and
 * true is returned.  Otherwise, false is returned.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool
Mesh<TPixelType, VDimension, TMeshTraits>
::GetAssignedCellBoundaryIfOneExists(int dimension, CellIdentifier cellId,
                                     CellFeatureIdentifier featureId,
                                     BoundaryPointer* boundary) const
{
  if((m_BoundaryAssignmentsContainers[dimension] != 0) &&
     (m_BoundariesContainers[dimension] != 0))
    {
    BoundaryAssignmentIdentifier assignId(cellId, featureId);
    BoundaryIdentifier boundaryId;
    
    if(m_BoundaryAssignmentsContainers[dimension]->
       GetElementIfIndexExists(assignId, &boundaryId))
      {
      return m_BoundariesContainers[dimension]->
        GetElementIfIndexExists(boundaryId, boundary);
      }
    }
  
  /**
   * An explicitly assigned boundary was not found.
   */
  return false;
}

/**
 * Dynamically build the links from points back to their using cells.  This
 * information is stored in the cell links container, not in the points.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::Accept(CellMultiVisitorType* mv)
{
  if(!m_CellsContainer)
    {
    return;
    }
  for(CellsContainerIterator i = m_CellsContainer->Begin();
      i != m_CellsContainer->End(); ++i)
    {
    if(i->Value().GetPointer())
      {
      i->Value()->Accept(i->Index(), mv);
      }
    else
      {
      itkDebugMacro("Null cell at " << i->Index());
      }
    }
}


/**
 * Dynamically build the links from points back to their using cells.  This
 * information is stored in the cell links container, not in the points.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
Mesh<TPixelType, VDimension, TMeshTraits>
::BuildCellLinks(void)
{
  /**
   * Make sure we have a cells and a points container.
   */
  if( !m_PointsContainer || !m_CellsContainer )
    {
    /**
     * TODO: Throw EXCEPTION here?
     */
    return;
    }
      
  /**
   * Make sure the cell links container exists.
   */
  if( !m_CellLinksContainer )
    {
    this->SetCellLinks(CellLinksContainer::New());
    }

  /**
   * Loop through each cell, and add its identifier to the CellLinks of each
   * of its points.
   */
  for(CellsContainerIterator cellItr = m_CellsContainer->Begin() ;
      cellItr != m_CellsContainer->End() ; ++cellItr)
    {
    CellIdentifier cellId = cellItr->Index();
    Cell::Pointer cell    = cellItr->Value();
    
    /**
     * For each point, make sure the cell links container has its index,
     * and then insert the cell ID into the point's set.
     */
    for(Cell::PointIdConstIterator pointId = cell->PointIdsBegin() ;
        pointId != cell->PointIdsEnd() ; ++pointId)
      {
      (m_CellLinksContainer->CreateElementAt(*pointId)).insert(cellId);
      }
    }
}


/******************************************************************************
 * PROTECTED METHOD DEFINITIONS
 *****************************************************************************/

/**
 * A protected default constructor allows the New() routine to create an
 * instance of Mesh.  All the containers are initialized to non-existent.
 */
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
Mesh<TPixelType, VDimension, TMeshTraits>
::Mesh():
  m_CellsContainer(0),
  m_CellDataContainer(0),
  m_CellLinksContainer(0),
  m_BoundariesContainers(BoundariesContainerVector(MaxTopologicalDimension)),
  m_BoundaryDataContainers(BoundaryDataContainerVector(MaxTopologicalDimension)),
  m_BoundaryAssignmentsContainers(
    BoundaryAssignmentsContainerVector(MaxTopologicalDimension))
{

}


//----------------------------------------------------------------------------
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void 
Mesh<TPixelType, VDimension, TMeshTraits>
::UpdateOutputInformation()
{
  if (this->GetSource())
    {
    this->GetSource()->UpdateOutputInformation();
    }
  
  // Now we should know what our largest possible region is. If our 
  // requested region was not set yet, (or has been set to something 
  // invalid - with no data in it ) then set it to the largest 
  // possible region.
  if ( m_RequestedRegion == -1 && m_RequestedNumberOfRegions == 0 )
    {
    this->SetRequestedRegionToLargestPossibleRegion();
    }
  
  m_LastRequestedRegionWasOutsideOfTheBufferedRegion = 0;
}

//----------------------------------------------------------------------------
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void 
Mesh<TPixelType, VDimension, TMeshTraits>
::SetRequestedRegionToLargestPossibleRegion()
{
  m_RequestedNumberOfRegions     = 1;
  m_RequestedRegion           = 0;
}

//----------------------------------------------------------------------------
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void 
Mesh<TPixelType, VDimension, TMeshTraits>
::CopyInformation(const DataObject *data)
{
  const Mesh *mesh;
  
  mesh = dynamic_cast<const Mesh*>(data);

  if (mesh)
    {
    m_MaximumNumberOfRegions = mesh->GetMaximumNumberOfRegions();
    }
  else
    {
    // pointer could not be cast back down
    itkExceptionMacro(<< "itk::Mesh::CopyInformation() cannot cast "
                  << typeid(data).name() << " to "
                  << typeid(Mesh*).name() );
    }
}

//----------------------------------------------------------------------------
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void 
Mesh<TPixelType, VDimension, TMeshTraits>
::SetRequestedRegion(DataObject *data)
{
  Mesh *mesh;
  
  mesh = dynamic_cast<Mesh*>(data);

  if (mesh)
    {
    m_RequestedRegion = mesh->m_RequestedRegion;
    m_RequestedNumberOfRegions = mesh->m_RequestedNumberOfRegions;
    }
  else
    {
    // pointer could not be cast back down
    itkExceptionMacro(<< "itk::Mesh::SetRequestedRegion(DataObject*) cannot cast "
                  << typeid(data).name() << " to "
                  << typeid(Mesh*).name() );
    }
}


//----------------------------------------------------------------------------
template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool 
Mesh<TPixelType, VDimension, TMeshTraits>
::RequestedRegionIsOutsideOfTheBufferedRegion()
{
  if ( m_RequestedRegion != m_BufferedRegion ||
       m_RequestedNumberOfRegions != m_NumberOfRegions )
    {
    return true;
    }

  return false;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
bool 
Mesh<TPixelType, VDimension, TMeshTraits>
::VerifyRequestedRegion()
{
  bool retval = true;

  // Are we asking for more regions than we can get?
  if ( m_RequestedNumberOfRegions > m_MaximumNumberOfRegions )
    {
    itkExceptionMacro( << "Cannot break object into " 
                   << m_RequestedNumberOfRegions << ". The limit is " 
                   << m_MaximumNumberOfRegions );
    retval = false;
    }

  if ( m_RequestedRegion >= m_RequestedNumberOfRegions ||
       m_RequestedRegion < 0 )
    {
    itkExceptionMacro( << "Invalid update region " << m_RequestedRegion
                   << ". Must be between 0 and " 
                   << m_RequestedNumberOfRegions - 1);
    retval = false;
    }

  return retval;
}

} // end namespace fem
} // end namespace itk

#endif
