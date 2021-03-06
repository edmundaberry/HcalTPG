#include "baseClass.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


baseClass::~baseClass(){}
baseClass::baseClass( const std::string & fileList, 
		      const std::string & treeList,
		      const std::string & outFileName ):
  m_fileList     ( fileList ),
  m_treeList     ( treeList ),
  m_outFileName  ( outFileName )
{
  loadFileList();
  loadTreeList();
  loadOutFile ();
}

void baseClass::loadFileList(){
  std::ifstream infile(m_fileList);
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string file_name;
    if (!(iss >> file_name)) break;
    m_file_names.push_back(file_name);
  }
}

void baseClass::loadTreeList(){
  std::ifstream infile(m_treeList);
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string tree_name;
    std::string tree_path;
    if (!(iss >> tree_name >> tree_path)) break;
    if ( m_treeMap.find ( tree_name ) == m_treeMap.end() ){
      m_treeMap[tree_name] = tree_path;
    } else { 
      std::cout << "Error: Your tree list contains two identical keys." << std::endl;
      std::cout << "List is here:" << std::endl;
      std::cout << m_treeList << std::endl;
      std::cout << "Repeated key is this one: " << tree_name << std::endl;
      exit(0);
    }
  }
}

void baseClass::loadOutFile(){
  m_outFile = new TFile (m_outFileName.c_str(), "RECREATE");
}

TChain* baseClass::getChain(std::string tree_name){
  TChain * chain = new TChain(tree_name.c_str());
  std::vector<std::string>::iterator i_file_name   = m_file_names.begin();
  std::vector<std::string>::iterator end_file_name = m_file_names.end();
  for (; i_file_name != end_file_name; ++i_file_name){
    chain -> Add (i_file_name->c_str());
  }
  return chain;
}

TH1F* baseClass::makeTH1F(const char * name, int nbins, float xmin, float xmax ){
  TH1F* hist = new TH1F(name, name, nbins, xmin, xmax );
  m_objects.push_back(hist);
  return hist;
}

TH2F* baseClass::makeTH2F(const char * name, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax){
  TH2F* hist = new TH2F(name, name, nbinsx, xmin, xmax, nbinsy, ymin, ymax );
  m_objects.push_back(hist);
  return hist;
}

void baseClass::write(){
  m_outFile -> cd();
  std::vector<TH1*>::iterator i_object   = m_objects.begin();
  std::vector<TH1*>::iterator end_object = m_objects.end  ();
  for (; i_object != end_object; ++i_object)
    (*i_object) -> Write();
}

void baseClass::print(){
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
  std::cout << "Analyzing these files (" << m_fileList << "):" << std::endl;
  std::vector<std::string>::iterator i_file   = m_file_names.begin();
  std::vector<std::string>::iterator end_file = m_file_names.end();
  for (; i_file != end_file; ++i_file)
    std::cout << "\t" << *i_file << std::endl;

  std::cout << "Using these trees (" << m_treeList << "):" << std::endl;
  std::map<std::string,std::string>::iterator i_tree   = m_treeMap.begin();
  std::map<std::string,std::string>::iterator end_tree = m_treeMap.end();
  for (; i_tree != end_tree; ++i_tree)
    std::cout << "\t" << i_tree -> second << "\t(" << i_tree -> first << ")" << std::endl;
  
  std::cout << "Writing output here:" << std::endl;
  std::cout << "\t" << m_outFileName << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;

}

void baseClass::run(){
  print();
  loop ();
  write();
}
