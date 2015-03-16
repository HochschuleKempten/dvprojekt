////////////////////////////////////////////////////
/// @file FileWavefront.h
/// @author Benedikt Walser
/// @author Kim Werner
/// ** Copyright (c) Humanics GbR **
////////////////////////////////////////////////////

#pragma once

namespace Vektoria
{

class CTriangleList;

class CFileWavefront
{
  public:
    CFileWavefront();
    ~CFileWavefront();
    CTriangleList * LoadGeo(char * pcPath);
  private:
    CTriangleList * m_pTriangleList;
};

}