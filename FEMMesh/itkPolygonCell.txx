/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkPolygonCell.txx
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
#ifndef _itkPolygonCell_txx
#define _itkPolygonCell_txx
#include "itkPolygonCell.h"


namespace itk
{
namespace fem
{

/**
 * Standard CellInterface:
 */
template <typename TCellTraits>
PolygonCell< TCellTraits >::CellPointer
PolygonCell< TCellTraits >
::MakeCopy(void)
{

  CellPointer newCell(Self::New());
  newCell->SetPointIds(this->PointIdsBegin(),this->PointIdsEnd());
  return newCell;
}

  
/**
 * Standard CellInterface:
 * Get the topological dimension of this cell.
 */
template <typename TCellTraits>
int
PolygonCell< TCellTraits >
::GetDimension(void) const
{
  return Self::CellDimension;
}


/**
 * Standard CellInterface:
 * Get the number of points required to define the cell.
 */
template <typename TCellTraits>
int
PolygonCell< TCellTraits >
::GetNumberOfPoints(void) const
{
  return m_PointIds.size();
}  


/**
 * Standard CellInterface:
 * Get the number of boundary features of the given dimension.
 */
template <typename TCellTraits>
PolygonCell< TCellTraits >::CellFeatureCount
PolygonCell< TCellTraits >
::GetNumberOfBoundaryFeatures(int dimension) const
{
  switch (dimension)
    {
    case 0: return this->GetNumberOfVertices();
    case 1: return this->GetNumberOfEdges();
    default: return 0;
    }
}


/**
 * Standard CellInterface:
 * Get the boundary feature of the given dimension specified by the given
 * cell feature Id.
 * The Id can range from 0 to GetNumberOfBoundaryFeatures(dimension)-1.
 */
template <typename TCellTraits>
PolygonCell< TCellTraits >::CellPointer
PolygonCell< TCellTraits >
::GetBoundaryFeature(int dimension, CellFeatureIdentifier featureId)
{
  switch (dimension)
    {
    case 0: return CellPointer(GetVertex(featureId));
    case 1: return CellPointer(GetEdge(featureId));
    default: return CellPointer(NULL);
    }
}


/**
 * Standard CellInterface:
 * Set the point id list used by the cell.  It is assumed that the given
 * iterator can be incremented and safely de-referenced enough times to 
 * get all the point ids needed by the cell.
 */ 
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::SetPointIds(int dummy, int num, PointIdConstIterator first)
{
  PointIdConstIterator ii(first);
  m_PointIds.clear();
  for(int i=0; i < num ; ++i)
    {
    m_PointIds.push_back(*ii++);
    }
  this->BuildEdges();
}

/**
 * after input the points in order, generate the edge connections
 */
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::BuildEdges(void)
{
  if( m_PointIds.size() > 0 )
    {
    m_Edges.resize(m_PointIds.size());
    for(int i = 1;i < m_PointIds.size(); i++)
      {
      m_Edges[i][0]=i-1;
      m_Edges[i][1]=i;
      }
    m_Edges[m_PointIds.size()-1][0]=m_PointIds.size()-1;
    m_Edges[m_PointIds.size()-1][1]=0;
    }
  else
    {
    m_Edges.clear();
    }
}

/**
 * Standard CellInterface:
 * Set the point id list used by the cell.  It is assumed that the given
 * iterator can be incremented and safely de-referenced enough times to 
 * get all the point ids needed by the cell.
 */ 
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::SetPointIds(PointIdConstIterator first)
{
}

/** 
 * Add one points to the points list
 */
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::AddPointId(PointIdentifier ptID)
{
  m_PointIds.push_back(ptID);
}

/**
 * clear all the point and edge informations
 */
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::ClearPoints(void)
{
  m_PointIds.clear();
  m_Edges.clear();
}

/**
 * Standard CellInterface:
 * Set the point id list used by the cell.  It is assumed that the range
 * of iterators [first, last) contains the correct number of points needed to
 * define the cell.  The position *last is NOT referenced, so it can safely
 * be one beyond the end of an array or other container.
 */ 
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::SetPointIds(PointIdConstIterator first, PointIdConstIterator last)
{
  m_PointIds.erase(m_PointIds.begin(), m_PointIds.end());
  m_PointIds.insert(m_PointIds.begin(), first, last);
  this->BuildEdges();
}

/**
 * Standard CellInterface:
 * Set an individual point identifier in the cell.
 */ 
template <typename TCellTraits>
void
PolygonCell< TCellTraits >
::SetPointId(int localId, PointIdentifier ptId)
{
  if(m_PointIds.size() < (unsigned int)(localId + 1)) {
    m_PointIds.resize( localId + 1 );
  }
  m_PointIds[localId] = ptId;
}


/**
 * Standard CellInterface:
 * Get a begin iterator to the list of point identifiers used by the cell.
 */
template <typename TCellTraits>
PolygonCell< TCellTraits >::PointIdIterator
PolygonCell< TCellTraits >
::PointIdsBegin(void)
{
  return &*(m_PointIds.begin());
}


/**
 * Standard CellInterface:
 * Get a const begin iterator to the list of point identifiers used
 * by the cell.
 */ 
template <typename TCellTraits>
PolygonCell< TCellTraits >::PointIdConstIterator
PolygonCell< TCellTraits >
::PointIdsBegin(void) const
{
  return &*(m_PointIds.begin());
}


/**
 * Standard CellInterface:
 * Get an end iterator to the list of point identifiers used by the cell.
 */ 
template <typename TCellTraits>
PolygonCell< TCellTraits >::PointIdIterator
PolygonCell< TCellTraits >
::PointIdsEnd(void)
{
  return &*(m_PointIds.end());
}


/**
 * Standard CellInterface:
 * Get a const end iterator to the list of point identifiers used
 * by the cell.
 */ 
template <typename TCellTraits>
PolygonCell< TCellTraits >::PointIdConstIterator
PolygonCell< TCellTraits >
::PointIdsEnd(void) const
{
  return &*(m_PointIds.end());
}


/**
 * Polygon-specific:
 * Get the number of vertices defining the Polygon.
 */
template <typename TCellTraits>
PolygonCell< TCellTraits >::CellFeatureCount
PolygonCell< TCellTraits >
::GetNumberOfVertices(void) const
{
  return m_PointIds.size();
}

/**
 * Polygon-specific:
 * Get the number of edges defined for the Polygon.
 */
template <typename TCellTraits>
PolygonCell< TCellTraits >::CellFeatureCount
PolygonCell< TCellTraits >
::GetNumberOfEdges(void) const
{
  return m_Edges.size();
}

/**
 * Polygon-specific:
 * Get the vertex specified by the given cell feature Id.
 * The Id can range from 0 to GetNumberOfVertices()-1.
 */ 
template <typename TCellTraits>
PolygonCell< TCellTraits >::VertexPointer
PolygonCell< TCellTraits >
::GetVertex(CellFeatureIdentifier vertexId)
{
  VertexPointer vert(Vertex::New());
  vert->SetPointId(0, m_PointIds[vertexId]);
  
  return vert;
}


/**
 * Polygon-specific:
 * Get the edge specified by the given cell feature Id.
 * The Id can range from 0 to GetNumberOfEdges()-1.
 */ 
template <typename TCellTraits>
PolygonCell< TCellTraits >::EdgePointer
PolygonCell< TCellTraits >
::GetEdge(CellFeatureIdentifier edgeId)
{
  EdgePointer edge(Edge::New());
  unsigned int max_pointId = this->GetNumberOfPoints() - 1;

  if( edgeId < max_pointId ){
    edge->SetPointId(0, m_PointIds[edgeId]);
    edge->SetPointId(1, m_PointIds[edgeId+1]);
  }
  else if( edgeId == max_pointId ) {
    edge->SetPointId(0, m_PointIds[max_pointId] );
    edge->SetPointId(1, m_PointIds[0] );
  }
  return edge;
}


} // end namespace fem
} // end namespace itk

#endif
