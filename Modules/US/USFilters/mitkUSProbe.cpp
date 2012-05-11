/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "mitkUSProbe.h"
#include <string>


mitk::USProbe::USProbe() : itk::Object()
{

}

mitk::USProbe::~USProbe()
{

}

bool mitk::USProbe::IsEqualToProbe(mitk::USProbe::Pointer probe)
{
  if(m_Name.compare(probe->GetName()) == 0) return true;
  else return false;
}