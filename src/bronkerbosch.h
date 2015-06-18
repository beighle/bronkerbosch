/*
 * bronkerbosch.h
 *
 *  Created on: 21-jan-2014
 *      Author: M. El-Kebir
 */

#ifndef BRONKERBOSCH_H
#define BRONKERBOSCH_H

#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <boost/dynamic_bitset.hpp>
#include "utils.h"

namespace bk {
  
class BronKerbosch
{
public:
  typedef enum
  {
    BK_CLASSIC,
    BK_PIVOT,
    BK_PIVOT_DEGENERACY
  } SolverType;

  typedef std::vector<Node> NodeVector;
  
protected:
  typedef typename Graph::template NodeMap<size_t> BitNodeMap;
  typedef boost::dynamic_bitset<> BitSet;
  typedef typename Graph::template NodeMap<BitSet> BitSetNodeMap;
  typedef std::list<Node> NodeList;
  typedef std::vector<NodeList> NodeListVector;

public:
  BronKerbosch(const Graph& g);

  virtual void run(SolverType type);

  void print(std::ostream& out) const;

  size_t getNumberOfMaxCliques() const { return _cliques.size(); }

  const std::vector<NodeVector>& getMaxCliques() const { return _cliques; }

protected:
  const Graph& _g;
  const size_t _n;
  std::vector<NodeVector> _cliques;
  std::vector<Node> _bitToNode;
  BitNodeMap _nodeToBit;
  BitSetNodeMap _bitNeighborhood;

  size_t computeDegeneracy(NodeList& order);

  void report(const BitSet& R);

  void printBitSet(const BitSet& S, std::ostream& out) const;

private:
  /// Classic Bron-Kerbosch algorithm without pivoting
  ///
  /// Reports maximal cliques in P \cup R (but not in X)
  void bkClassic(BitSet P, BitSet R, BitSet X);
  void bkPivot(BitSet P, BitSet R, BitSet X);
  void bkDegeneracy(const NodeList& order);
};

} // namespace bk

#endif // BRONKERBOSCH_H
