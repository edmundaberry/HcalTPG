#ifndef baseClass_h
#define baseClass_h

#include <map>
#include <string>
#include <iostream>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1.h"

class baseClass {
  
 public:
  ~baseClass();
  baseClass( const std::string & inputList, const std::string & treeList, const std::string & out_file );
  void run();

  TH1F* makeTH1F(const char * name, int nbins , float xmin, float xmax);
  TH2F* makeTH2F(const char * name, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax);

  template<typename T> T* getTree(std::string tree_name){
    if ( m_treeMap.find ( tree_name ) == m_treeMap.end() ){
      std::cout << "Error: Your tree list does not contain the key you're asking for" << std::endl;
      std::cout << "List is here:" << std::endl;
      std::cout << m_treeList << std::endl;
      std::cout << "Requested key is this one: " << tree_name << std::endl;
      exit(0);
    } 
    std::string tree_path = m_treeMap[tree_name];
    T * tree = new T(getChain(tree_path));
    return tree;
    
  }
  
 private:
  
  TChain* getChain(std::string tree_name);
  void loadFileList();
  void loadTreeList();
  void loadOutFile ();
  void write();
  void print();
  virtual void loop() = 0;
  
  const std::string m_fileList;
  const std::string m_treeList;
  const std::string m_outFileName;
  
  std::vector<std::string> m_file_names;
  std::vector<std::string> m_tree_names;
  
  std::vector<TH1*> m_objects;
  
  TFile * m_outFile;
  
  std::map<std::string, std::string> m_treeMap;

};


#endif

