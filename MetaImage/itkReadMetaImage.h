/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkReadMetaImage.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef __itkReadMetaImage_h
#define __itkReadMetaImage_h

#include "itkFstream.h"
#include "itkImageSource.h"

namespace itk
{

/** \class ReadMetaImage
 * \brief Read image files in MetaImage format.
 *
 * ReadMetaImage reads data files in MetaImage format. This format
 * was developed at UNC by Stephen Aylward ( aylward@cs.unc.edu ).
 * It is intended to provide an intermediary representation for 
 * DICOM streams.
 *
 */
template <class TOutputImage>
class ITK_EXPORT ReadMetaImage : public ImageSource<TOutputImage>
{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef ReadMetaImage        Self;

  /**
   * Standard "Superclass" typedef.
   */
  typedef ImageSource<TOutputImage>  Superclass;

  /** 
   * Smart pointer typedef support.
   */
  typedef SmartPointer<Self>  Pointer;

  /** 
   * Run-time type information (and related methods).
   */
  itkTypeMacro(ReadMetaImage,ImageSource);

  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);  

  /**
   * typedef for Size.
   */
  typedef Size<TOutputImage::ImageDimension>  Size;

  /**
   * typedef for Region.
   */
  typedef ImageRegion<TOutputImage::ImageDimension>  Region;

  /** 
   * Specify the name of the input file.
   */
  itkSetStringMacro(FileName);
  
  /** 
   * Get the name of the input file.
   */
  itkGetStringMacro(FileName);
  
protected:
  ReadMetaImage();
  ~ReadMetaImage() {};
  ReadMetaImage(const Self&) {}; 
  void operator=(const Self&) {};
  void PrintSelf(itk::Ofstream& os, Indent indent);
  
  void GenerateData();

private:
  std::string m_FileName;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkReadMetaImage.txx"
#endif

#endif
