#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/incremental_components.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/random/random_number_generator.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <time.h>
#include <fstream>
<<<<<<< HEAD
=======
//#include <omp.h>
>>>>>>> 5614ab8e4805b8faee2368b3d7359ed698168961

using namespace boost;

int main(int argc, char* argv[]) 
{
  typedef adjacency_list <vecS, vecS, undirectedS> Graph;
  typedef graph_traits<Graph>::vertex_descriptor Vertex;
  typedef graph_traits<Graph>::vertices_size_type VertexIndex;

  const int VERTEX_COUNT = 20;
  Graph graph(VERTEX_COUNT);

  std::vector<VertexIndex> rank(num_vertices(graph));
  std::vector<Vertex> parent(num_vertices(graph));

  typedef VertexIndex* Rank;
  typedef Vertex* Parent;

  disjoint_sets<Rank, Parent> ds(&rank[0], &parent[0]);

  initialize_incremental_components(graph, ds);
  incremental_components(graph, ds);

  graph_traits<Graph>::edge_descriptor edge;
  bool flag;

  typedef component_index<VertexIndex> Components;
<<<<<<< HEAD

  for(int i = 0; i < 10; i++)
  {
  	random::mt19937 gen{static_cast<std::uint32_t>(rand())};
  	random::mt19937 gen1{static_cast<std::uint32_t>(rand())};
	  Vertex a = random_vertex(graph, gen);
	  Vertex b = random_vertex(graph, gen1);
	
	  boost::tie(edge, flag) = add_edge(a, b, graph);
  	ds.union_set(a,b);

    std::cout << i << std::endl;
  	//Components components(parent.begin(), parent.end());
   //  std::cout << a << " - " << b << std::endl;
  	
  	// if(components.size() == 1)
  	// {
  	// 	std::cout << "Graph fully connected after adding " << i << " edges." << std::endl << std::endl;;
   //    std::ofstream outfile;
   //    outfile.open("results.txt", std::ios_base::app);
   //    outfile << i << "\n"; 
  	// 	break;
  	// } 
  }

  std::cout << std::endl;
=======
  
 // #pragma omp parallel for(4)
  //{
    for(int i = 0; i < 10000; i++)
    {
    	random::mt19937 gen{static_cast<std::uint32_t>(rand())};
    	random::mt19937 gen1{static_cast<std::uint32_t>(rand())};
  	  Vertex a = random_vertex(graph, gen);
  	  Vertex b = random_vertex(graph, gen1);
  	
  	  boost::tie(edge, flag) = add_edge(a, b, graph);
    	ds.union_set(a,b);
     	incremental_components(graph, ds);
    	Components components(parent.begin(), parent.end());
      std::cout << a << " - " << b << std::endl;
    	
    	if(components.size() == 1)
    	{
    		std::cout << "Graph fully connected after adding " << i << " edges." << std::endl;
        std::ofstream outfile;
        outfile.open("results.txt", std::ios_base::app);
        outfile << i << "\n"; 
    		break;
    	} 
    }
  //}
>>>>>>> 5614ab8e4805b8faee2368b3d7359ed698168961
    
   BOOST_FOREACH(Vertex current_vertex, vertices(graph)) {
   std::cout << "representative[" << current_vertex << "] = " <<
   ds.find_set(current_vertex) << std::endl;
  }

  std::cout << std::endl;

  Components components(parent.begin(), parent.end());

  BOOST_FOREACH(VertexIndex current_index, components) {
    std::cout << "component " << current_index << " contains: ";

    BOOST_FOREACH(VertexIndex child_index,
                  components[current_index]) {
      std::cout << child_index << " ";
    }

    std::cout << std::endl;
  }
  return (0);
}