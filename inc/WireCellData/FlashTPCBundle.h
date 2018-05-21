#ifndef WIRECELL_FLASHTPCBUNDLE_H
#define WIRECELL_FLASHTPCBUNDLE_H

#include "WireCellData/PR3DCluster.h"
#include "WireCellData/Opflash.h"

namespace WireCell{
  class FlashTPCBundle{
  public:
    FlashTPCBundle(Opflash* flash, PR3DCluster *main_cluster, int flash_index_id, int cluster_index_id);
    ~FlashTPCBundle();

    void set_flag_close_to_PMT(bool value){flag_close_to_PMT = value;};
    void set_flag_at_x_boundary(bool value){flag_at_x_boundary = value;};
    
    bool get_flag_close_to_PMT(){return flag_close_to_PMT;};
    bool get_flag_at_x_boundary(){return flag_at_x_boundary;};

    std::vector<double>& get_pred_pmt_light(){return pred_pmt_light;};
    Opflash* get_flash(){return flash;};
    
    PR3DCluster* get_main_cluster(){return main_cluster;};
    PR3DClusterSelection& get_other_clusters(){return other_clusters;};
    PR3DClusterSelection& get_more_clusters(){return more_clusters;};

    bool examine_bundle(Double_t *cos_pe_low, Double_t *cos_pe_mid);
    bool examine_bundle(FlashTPCBundle* bundle, Double_t *cos_pe_low, Double_t *cos_pe_mid);
    
    double get_chi2(){return chi2;};
    int get_ndf(){return ndf;};
    double get_ks_dis(){return ks_dis;};
    void set_consistent_flag(bool value){flag_high_consistent = value;};
    bool get_consistent_flag(){return flag_high_consistent;};

    void set_spec_end_flag(bool value){flag_spec_end = value;};
    bool get_spec_end_flag(){return flag_spec_end;};
    bool get_potential_bad_match_flag(){return flag_potential_bad_match;};

    double get_strength(){return strength;};
    void set_strength(double value){ strength = value;};
    
  private:
    Opflash *flash;
    PR3DCluster *main_cluster;

    double strength;
    
    int cluster_index_id;
    int flash_index_id;

    bool flag_close_to_PMT;
    bool flag_at_x_boundary;
    bool flag_spec_end;

    bool flag_potential_bad_match;
    
    std::vector<double> pred_pmt_light; // prediction

    double ks_dis;
    double chi2;
    int ndf;
    bool flag_high_consistent;
    
    PR3DClusterSelection other_clusters; // save every other one 
    PR3DClusterSelection more_clusters;  // save ones satisfying the cut    
  };

  typedef std::vector<FlashTPCBundle*> FlashTPCBundleSelection;
  typedef std::set<FlashTPCBundle*> FlashTPCBundleSet;
  typedef std::map<Opflash*, FlashTPCBundleSelection> Flash_bundles_map;
  typedef std::map<PR3DCluster*, FlashTPCBundleSelection> Cluster_bundles_map;
  
}


#endif
