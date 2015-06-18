/*
 * main.cpp
 *
 *  Created on: 18-jun-2015
 *      Author: M. El-Kebir
 */

#include "utils.h"
#include "bronkerbosch.h"
#include <fstream>

using namespace bk;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " <EDGE_LIST>" << std::endl;
    return 1;
  }
  
  std::ifstream inFile(argv[1]);
  if (!inFile.good())
  {
    std::cerr << "Unable to open '" << argv[1]
              << "' for reading" << std::endl;
    return 1;
  }
  
  Graph g;
  StringNodeMap nodeToLabel(g);
  StringToNodeMap labelToNode;
  if (!readGraph(inFile, g, nodeToLabel, labelToNode))
  {
    return 1;
  }
  
  BronKerbosch bkAlg(g);
  bkAlg.run(BronKerbosch::BK_PIVOT_DEGENERACY);
  
  const std::vector<BronKerbosch::NodeVector>& cliques = bkAlg.getMaxCliques();
  for (size_t i = 0; i < cliques.size(); ++i)
  {
    const BronKerbosch::NodeVector& C = cliques[i];
    for (size_t j = 0; j < C.size(); ++j)
    {
      std::cout << nodeToLabel[C[j]] << " ";
    }
    std::cout << std::endl;
  }
  
  return 0;
}