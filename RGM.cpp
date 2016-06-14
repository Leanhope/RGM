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
#include <boost/progress.hpp>
#include <chrono>
#include <fstream>

using namespace boost;

int main(int argc, char* argv[]) 
{  
  typedef adjacency_list <vecS, vecS, undirectedS> Graph;
  typedef graph_traits<Graph>::vertex_descriptor Vertex;
  typedef graph_traits<Graph>::vertices_size_type VertexIndex;

  int VERTEX_COUNT;
  int EDGE_COUNT;

  std::cout << "Number of vertices: ";
  std::cin >> VERTEX_COUNT;
  std::cout << "Number of edges: " ;
  std::cin >> EDGE_COUNT;  

		auto start = std::chrono::steady_clock::now();

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

		boost::progress_display show_progress(EDGE_COUNT);
		srand(time(NULL));

		  for(int i = 0; i < EDGE_COUNT; i++)
		  {
		  	random::taus88 gen(rand());
		  	random::taus88 gen1(rand());
			  Vertex a = random_vertex(graph, gen);
			  Vertex b = random_vertex(graph, gen1);
			
			  boost::tie(edge, flag) = add_edge(a, b, graph);
			  if(ds.find_set(a) == ds.find_set(b))
			  	{
			  		std::cout << std::endl << "Cycle found after " << i << " edges." << std::endl;
		  			std::ofstream outfile;
					  outfile.open("results.txt", std::ios_base::app);
					  outfile << "Edges to Cycle: " << i << std::endl;
			  		break;
			  	}
		  	ds.union_set(a,b);
		  	++show_progress;
		    //std::cout << a << " - " << b << std::endl;
		  	
		  // 	if(components.size() == 1)
		  // 	{
		  // 		std::cout << "Graph fully connected after adding " << i << " edges." << std::endl;
		  //     std::ofstream outfile;
		  //     outfile.open("results.txt", std::ios_base::app);
		  //     outfile << i << "\n"; 
		  // 		break;
		  // 	} 
		  }
		  
		// BOOST_FOREACH(Vertex current_vertex, vertices(graph)) {
		// std::cout << "representative[" << current_vertex << "] = " <<
		// ds.find_set(current_vertex) << std::endl;
		//}

		std::cout << std::endl;

		Components components(parent.begin(), parent.end());

		// BOOST_FOREACH(VertexIndex current_index, components) {
		//   std::cout << "component " << current_index << " contains: ";

		//   BOOST_FOREACH(VertexIndex child_index,
		//                 components[current_index]) {
		//     std::cout << child_index << " ";
		//   }

		//   std::cout << std::endl;
		// }

		std::chrono::duration<double> diff = std::chrono::steady_clock::now() - start;

		std::cout << diff.count() << " seconds needed." << std::endl;
		// std::ofstream outfile;
		//   outfile.open("results.txt", std::ios_base::app);
		//   outfile << "V: " << VERTEX_COUNT << " E: " << EDGE_COUNT << " TiS " << diff.count() <<"\n"; 
		return (0);
}