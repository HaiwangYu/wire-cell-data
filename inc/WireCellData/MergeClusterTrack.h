#ifndef MergeClusterTrack_h
#define MergeClusterTrack_h

#include "WireCellData/MergeSpaceCell.h"
#include "WireCellData/ClusterTrack.h"

namespace WireCell{
  class MergeClusterTrack{
  public:
    MergeClusterTrack(ClusterTrack *ctrack);
    ~MergeClusterTrack();
    
    void Add(ClusterTrack *ctrack);

    
    MergeSpaceCellSelection& Get_allmcells(){return all_mcells;};
    void Update();
    MergeSpaceCell* Get_FirstMSCell(){return all_mcells.front();};
    MergeSpaceCell* Get_LastMSCell(){return all_mcells.back();};

  protected:
    ClusterTrackSelection ctracks; // save merged clusters ... 
    MergeSpaceCellSelection all_mcells; // save all the merged cells
    MergeSpaceCellList all_mcells_list; // temporary one ... 

  };
}

#endif
