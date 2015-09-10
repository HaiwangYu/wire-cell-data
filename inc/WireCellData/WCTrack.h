#ifndef WCTrack_h
#define WCTrack_h

#include "WireCellData/MergeClusterTrack.h"
//#include "WireCellData/WCVertex.h"
#include <vector>
#include <map>

namespace WireCell {
  class WCTrack{
  public:
    WCTrack(MergeClusterTrack& mct);
    ~WCTrack();
    MergeClusterTrack& get_mct(){return mct;};
    int TrackType(MergeSpaceCell& cell);
    MergeSpaceCellSelection& get_end_scells(){return end_scells;};
    MergeSpaceCellSelection& get_all_cells(){return all_cells;};

    MergeSpaceCell* replace_end_scells(MergeSpaceCell* cell, MergeSpaceCellSelection* cells=0);
    void ModifyCells();
    void ReplaceEndCell(MergeSpaceCell *cell1, MergeSpaceCell *cell2);
    bool Grow(MergeSpaceCell *cell, int flag = 1); 

    bool fine_tracking(int ntrack_p1, Point &p1, double ky1, double kz1, 
		       int ntrack_p2, Point &p2, double ky2, double kz2);

    PointVector& get_centerVP(){return centerVP;};
    MergeSpaceCellSelection& get_centerVP_cells(){return centerVP_cells;};
    std::vector<double>& get_centerVP_theta(){return centerVP_theta;};
    std::vector<double>& get_centerVP_phi(){return centerVP_phi;};


    int get_fine_tracking_flag(){return fine_tracking_flag;};
    
    bool IsContained(MergeSpaceCell *mcell);
    bool IsBadTrack();
    void reset_fine_tracking();

    double dist(MergeSpaceCell*mcell,SpaceCell *cell);
    double dist_proj(MergeSpaceCell *mcell, SpaceCell *cell);
    
    double get_range(){return range;};

  protected:
    MergeClusterTrack& mct;
    MergeSpaceCellSelection end_scells;
    MergeSpaceCellSelection all_cells;

    PointVector centerVP;
    MergeSpaceCellSelection centerVP_cells;
    std::vector<double> centerVP_theta;
    std::vector<double> centerVP_phi;
    std::vector<float> centerVP_energy;
    std::vector<float> centerVP_dedx;
    
    Point fp1;
    Point fp2;
    int ntrack_fp1;
    int ntrack_fp2;

    double range;

    int fine_tracking_flag;

  };

  typedef std::vector<WCTrack*> WCTrackSelection;
  typedef std::map<WCTrack*,int> WCTrackCounter;
  typedef std::map<MergeClusterTrack*,WCTrack*> MCT_WCT_Map;
  //typedef std::map<WCTrack*, WCVertexSelection> WCT_WCV_Map;
}

#endif
