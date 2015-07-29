#include "WireCellData/ClusterTrack.h"
#include "TVector3.h"

using namespace WireCell;


ClusterTrack::ClusterTrack(MergeSpaceCell *cell){
  all_mcells.push_back(cell);
  hough = new TH2F("","",180,0.,3.1415926,360,-3.1415926,3.1415926);
}

ClusterTrack::~ClusterTrack(){
  delete hough;
}

Point ClusterTrack::SC_IterativeHough(Point &p, float dis){
  // do three times Hough
  //first hough
  SC_Hough(p,dis);
  float theta = Get_Theta();
  float phi = Get_Phi();
  Point p1;
  p1.x = p.x + dis * sin(theta) * cos(phi);
  p1.y = p.y + dis * sin(theta) * sin(phi);
  p1.z = p.z + dis * cos(theta);

  //second hough
  SC_Hough(p1,p,dis);
  theta = Get_Theta();
  phi = Get_Phi();
  p1.x = p1.x + dis * sin(theta) * cos(phi);
  p1.y = p1.y + dis * sin(theta) * sin(phi);
  p1.z = p1.z + dis * cos(theta);

  //third hough
  SC_Hough(p1,p,dis);
  theta = Get_Theta();
  phi = Get_Phi();
  p1.x = p1.x + dis * sin(theta) * cos(phi);
  p1.y = p1.y + dis * sin(theta) * sin(phi);
  p1.z = p1.z + dis * cos(theta);

    
  return p1;
}

int ClusterTrack::CrossNum(Point &p, float theta, float phi){
  int result = 0;

  float x1 = p.x;
  float y1 = p.y;
  float z1 = p.z;
 
  float x2 = x1 + sin(theta) * cos(phi);
  float y2 = y1 + sin(theta) * sin(phi);
  float z2 = z1 + cos(theta);

  
 
  for (int i=0;i!=all_mcells.size();i++){
    MergeSpaceCell *mcell = all_mcells.at(i);

    bool result1 = false;
    
    double min_dis = 1e9;
  
    for (int j=0;j!=mcell->Get_all_spacecell().size();j++){
      SpaceCell *cell = mcell->Get_all_spacecell().at(j);
      

      float x,y,z;
      x = cell->x();
      y = cell->y();
      z = cell->z();

      double dis;
      
      TVector3 v1(x-x1,y-y1,z-z1);
      TVector3 v2(x-x2,y-y2,z-z2);
      TVector3 v3(x2-x1,y2-y1,z2-z1);
      TVector3 v4 = v1.Cross(v2);
      dis = v4.Mag()/v3.Mag();
      
      if (dis < min_dis ) min_dis = dis;
      //std::cout << "Xin1: " << dis/units::mm << std::endl;

     
      if (dis < 3*units::mm){
	result1 = true;
	break;
      }
    }
    
    //std::cout << i << " " << result1 << " " << min_dis/units::mm << std::endl;
    if (result1)
      result ++;
    
  }
  
  return result;
}


void ClusterTrack::AddMSCell(MergeSpaceCell *cell){
  all_mcells.push_back(cell);
}

void ClusterTrack::SC_Hough(Point&p1, Point&p, float dis){
  hough->Reset();
  double x0 = p.x;
  double y0 = p.y;
  double z0 = p.z;
  
  double x1 = p1.x;
  double y1 = p1.y;
  double z1 = p1.z;

  double x,y,z,q;
  for (int i=0;i!=all_mcells.size();i++){
    MergeSpaceCell *mcell = all_mcells.at(i);
    for (int j=0;j!=mcell->Get_all_spacecell().size();j++){
      SpaceCell *cell = mcell->Get_all_spacecell().at(j);
      
      x = cell->x();
      y = cell->y();
      z = cell->z();
      q = cell->q();
      
      
      
      TVector3 vec(x-x1,y-y1,z-z1);
      // sc_theta.push_back(vec.Theta());
      // sc_phi.push_back(vec.Phi());
      // sc_q.push_back(q);
      if (dis <= 0){
	hough->Fill(vec.Theta(),vec.Phi(),q);
      }else{
	if (sqrt(pow(x-x0,2)+pow(y-y0,2)+pow(z-z0,2))<dis)
	  hough->Fill(vec.Theta(),vec.Phi(),q);
      }
    }
  }
  
}


void ClusterTrack::SC_Hough(Point& p, float dis){
  hough->Reset();
  double x0 = p.x;
  double y0 = p.y;
  double z0 = p.z;
  double x,y,z,q;
  for (int i=0;i!=all_mcells.size();i++){
    MergeSpaceCell *mcell = all_mcells.at(i);
    for (int j=0;j!=mcell->Get_all_spacecell().size();j++){
      SpaceCell *cell = mcell->Get_all_spacecell().at(j);
      
      x = cell->x();
      y = cell->y();
      z = cell->z();
      q = cell->q();
      
      
      
      TVector3 vec(x-x0,y-y0,z-z0);
      // sc_theta.push_back(vec.Theta());
      // sc_phi.push_back(vec.Phi());
      // sc_q.push_back(q);
      if (dis <= 0){
	hough->Fill(vec.Theta(),vec.Phi(),q);
      }else{
	if (sqrt(pow(x-x0,2)+pow(y-y0,2)+pow(z-z0,2))<dis)
	  hough->Fill(vec.Theta(),vec.Phi(),q);
      }
    }
  }
}

float ClusterTrack::Get_Theta(){
  int maxbin = hough->GetMaximumBin();
  int a,b,c;
  hough->GetBinXYZ(maxbin,a,b,c);
  return hough->GetXaxis()->GetBinCenter(a);
}


float ClusterTrack::Get_Phi(){
  int maxbin = hough->GetMaximumBin();
  int a,b,c;
  hough->GetBinXYZ(maxbin,a,b,c);
  return hough->GetYaxis()->GetBinCenter(b);
}


float ClusterTrack::Get_CTheta(Point &p){
  double x0 = p.x;
  double y0 = p.y;
  double z0 = p.z;

  Point p1 = all_mcells.front()->Get_Center();
  Point p2 = all_mcells.back()->Get_Center();
  
  double x,y,z;
  
  if (sqrt(pow(p1.x-x0,2)+pow(p1.y-y0,2)+pow(p1.z-z0,2))<
      sqrt(pow(p2.x-x0,2)+pow(p2.y-y0,2)+pow(p2.z-z0,2))){
    x = p2.x;
    y = p2.y;
    z = p2.z;
  }else{
    x = p1.x;
    y = p1.y;
    z = p1.z;
  }
  TVector3 vec(x-x0,y-y0,z-z0);
  return vec.Theta();
  
  
}

float ClusterTrack::Get_CPhi(Point &p){
  double x0 = p.x;
  double y0 = p.y;
  double z0 = p.z;

  Point p1 = all_mcells.front()->Get_Center();
  Point p2 = all_mcells.back()->Get_Center();
  
  double x,y,z;
  
  if (sqrt(pow(p1.x-x0,2)+pow(p1.y-y0,2)+pow(p1.z-z0,2))<
      sqrt(pow(p2.x-x0,2)+pow(p2.y-y0,2)+pow(p2.z-z0,2))){
    x = p2.x;
    y = p2.y;
    z = p2.z;
  }else{
    x = p1.x;
    y = p1.y;
    z = p1.z;
  }
  TVector3 vec(x-x0,y-y0,z-z0);
  return vec.Phi();
}
