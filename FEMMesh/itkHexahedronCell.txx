/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkHexahedronCell.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkHexahedronCell_txx
#define _itkHexahedronCell_txx
#include "itkHexahedronCell.h"

namespace itk
{
namespace fem
{

/**
 * Standard CellInterface:
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::CellPointer
HexahedronCell< TCellTraits >
::MakeCopy(void)
{
  CellPointer newCell(Self::New());
  newCell->SetPointIds(this->GetPointIds());
  return newCell;
}

/**
 * Standard CellInterface:
 * Get the topological dimension of this cell.
 */
template <typename TCellTraits>
int
HexahedronCell< TCellTraits >
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
HexahedronCell< TCellTraits >
::GetNumberOfPoints(void) const
{
  return Self::NumberOfPoints;
}  

/**
 * Standard CellInterface:
 * Get the number of boundary features of the given dimension.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::CellFeatureCount
HexahedronCell< TCellTraits >
::GetNumberOfBoundaryFeatures(int dimension) const
{
  switch (dimension)
    {
    case 0: return GetNumberOfVertices();
    case 1: return GetNumberOfEdges();
    case 2: return GetNumberOfFaces();
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
HexahedronCell< TCellTraits >::CellPointer
HexahedronCell< TCellTraits >
::GetBoundaryFeature(int dimension, CellFeatureIdentifier featureId)
{
  switch (dimension)
    {
    case 0: return CellPointer(GetVertex(featureId));
    case 1: return CellPointer(GetEdge(featureId));
    case 2: return CellPointer(GetFace(featureId));
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
HexahedronCell< TCellTraits >
::SetPointIds(PointIdConstIterator first)
{
  PointIdConstIterator ii(first);
  for(int i=0; i < Self::NumberOfPoints ; ++i)
    {   
    m_PointIds[i] = *ii++;
    }
}

/**
 * Standard CellInterface:
 * Set the point id list used by the cell.  It is assumed that the range
 * of iterators [first, last) contains the correct number of points needed to
 * define the cell.  The position *last is NOT referenced, so it can safely
 * be one beyond the end of an array or other container.
 */
template < typename TCellTraits>
void
HexahedronCell< TCellTraits >
::SetPointIds(PointIdConstIterator first, PointIdConstIterator last)
{
  int localId=0;
  PointIdConstIterator ii(first);
  
  while(ii != last)
    {
    m_PointIds[localId++] = *ii++;
    }
}

/**
 * Standard CellInterface:
 * Set an individual point identifier in the cell.
 */
template <typename TCellTraits>
void
HexahedronCell< TCellTraits >
::SetPointId(int localId, PointIdentifier ptId)
{
  m_PointIds[localId] = ptId;
}

/**
 * Standard CellInterface:
 * Get a begin iterator to the list of point identifiers used by the cell.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::PointIdIterator
HexahedronCell< TCellTraits >
::PointIdsBegin(void)
{
  return &m_PointIds[0];
}

/**
 * Standard CellInterface:
 * Get a const begin iterator to the list of point identifiers used
 * by the cell.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::PointIdConstIterator
HexahedronCell< TCellTraits >
::PointIdsBegin(void) const
{
  return &m_PointIds[0];
}

/**
 * Standard CellInterface:
 * Get an end iterator to the list of point identifiers used by the cell.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::PointIdIterator
HexahedronCell< TCellTraits >
::PointIdsEnd(void)
{
  return &m_PointIds[Self::NumberOfPoints];
}

/**
 * Standard CellInterface:
 * Get a const end iterator to the list of point identifiers used
 * by the cell.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::PointIdConstIterator
HexahedronCell< TCellTraits >
::PointIdsEnd(void) const
{
  return &m_PointIds[Self::NumberOfPoints];
}

/**
 * Hexahedron-specific:
 * Get the number of vertices defining the hexahedron.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::CellFeatureCount
HexahedronCell< TCellTraits >
::GetNumberOfVertices(void) const
{
  return Self::NumberOfVertices;
}

/**
 * Hexahedron-specific:
 * Get the number of edges defined for the hexahedron.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::CellFeatureCount
HexahedronCell< TCellTraits >
::GetNumberOfEdges(void) const
{
  return Self::NumberOfEdges;
}

/**
 * Hexahedron-specific:
 * Get the number of faces defined for the hexahedron.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::CellFeatureCount
HexahedronCell< TCellTraits >
::GetNumberOfFaces(void) const
{
  return Self::NumberOfFaces;
}

/**
 * Hexahedron-specific:
 * Get the vertex specified by the given cell feature Id.
 * The Id can range from 0 to GetNumberOfVertices()-1.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::VertexPointer
HexahedronCell< TCellTraits >
::GetVertex(CellFeatureIdentifier vertexId)
{
  Vertex::Pointer vert(Vertex::New());
  vert->SetPointId(0, m_PointIds[vertexId]);
  
  return vert;
}


/**
 * Hexahedron-specific:
 * Get the edge specified by the given cell feature Id.
 * The Id can range from 0 to GetNumberOfEdges()-1.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::EdgePointer
HexahedronCell< TCellTraits >
::GetEdge(CellFeatureIdentifier edgeId)
{
  Edge::Pointer edge(Edge::New());

  for(int i=0; i < Edge::NumberOfPoints; ++i)
    {
    edge->SetPointId(i, m_PointIds[ m_Edges[edgeId][i] ]);
    }
  
  return edge;
}

/**
 * Hexahedron-specific:
 * Get the face specified by the given cell feature Id.
 * The Id can range from 0 to GetNumberOfFaces()-1.
 */
template <typename TCellTraits>
HexahedronCell< TCellTraits >::FacePointer
HexahedronCell< TCellTraits >
::GetFace(CellFeatureIdentifier faceId)
{
  Face::Pointer face(Face::New());
  
  for(int i=0; i < Face::NumberOfPoints; ++i)
    {
    face->SetPointId(i, m_PointIds[ m_Faces[faceId][i] ]);
    }
  
  return face;
}

/**
 * The hexahedron's topology data: Edges.
 */
template <typename TCellTraits>
const int
HexahedronCell< TCellTraits >
::m_Edges[12][2] = { {0,1}, {1,2}, {3,2}, {0,3}, 
                     {4,5}, {5,6}, {7,6}, {4,7},
                     {0,4}, {1,5}, {3,7}, {2,6} };

/**
 * The hexahedron's topology data: Faces.
 */
template <typename TCellTraits>
const int
HexahedronCell< TCellTraits >
::m_Faces[6][4] = { {0,4,7,3}, {1,2,6,5},
                    {0,1,5,4}, {3,7,6,2},
                    {0,3,2,1}, {4,5,6,7} };


} // end namespace fem
} // end namespace itk

#endif
