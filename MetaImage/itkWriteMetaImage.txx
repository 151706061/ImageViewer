/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkWriteMetaImage.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#include "itkWriteMetaImage.h"
#include "itkObjectFactory.h"
#include <fstream>
#include <MetaImageLib/MetaImageLib.h>

namespace itk
{

/**
 *
 */
template <class TInputImage>
WriteMetaImage<TInputImage>
::WriteMetaImage()
{
  m_FileName = "";
}





/**
 *
 */
template <class TInputImage>
void 
WriteMetaImage<TInputImage>
::GenerateData(void)
{
  this->WriteData();  
}





/**
 *
 */
template <class TInputImage>
void 
WriteMetaImage<TInputImage>
::WriteData(void)
{
  
  const unsigned int BitsPerPixel = 
                          8*sizeof( PixelType );

  const unsigned int dimension = TInputImage::ImageDimension;

  typename TInputImage::Pointer m_InputImage( GetInput() );

  int dimSize[ dimension ];

  const typename TInputImage::Size& size = 
        m_InputImage->GetBufferedRegion().GetSize();
        
  const float         *spacing = m_InputImage->GetSpacing();                

  for(unsigned int i=0; i<dimension; i++) 
  {
    dimSize[i] = size[i];
  }

  typedef typename TInputImage::PixelType PixelType;
  
  PixelType *yetAnotherBuffer = new PixelType[ 
            m_InputImage->GetOffsetTable()[dimension] ];

  typedef itk::ImageRegionSimpleIterator< TInputImage > IteratorType;
  
  IteratorType it(	m_InputImage, 
                    m_InputImage->GetBufferedRegion() );

  
  PixelType * destination = yetAnotherBuffer;
  it.Begin();
  while( !it.IsAtEnd() ) 
  {
    *destination++ = it.Get(); 
    ++it;
  }

  MetaImage saver(  dimension,
                    dimSize,
                    GetTypeCode(),
                    spacing,
                    BitsPerPixel,
                    MET_SYSTEM_BYTE_ORDER_MSB,
                    yetAnotherBuffer  );


  saver.Save( this->m_FileName.c_str(),0,1);

  delete [] yetAnotherBuffer;

  if(saver.Error())  {
    std::cerr << "Unable to open file:" << m_FileName << std::endl;
    return;
  }

}






/**
 *
 */
template <class TInputImage>
void 
WriteMetaImage<TInputImage>
::PrintSelf(std::ostream& os, Indent indent)
{
  Superclass::PrintSelf(os,indent);
  os << indent << "Meta Image file format writer";
}







} // end namespace itk
