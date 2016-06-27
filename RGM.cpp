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
	std::vector<int> results;
	
	int graph_count;
	int vertex_count;
	int edge_count;

	std::cout << "Number of vertices: ";
	std::cin >> vertex_count;
	std::cout << "Number of edges: " ;
	std::cin >> edge_count;
	std::cout << "Number of graphs: " ;
	std::cin >> graph_count;

	srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());	

	boost::progress_display show_progress(graph_count);

	for (int i = 0; i < graph_count; ++i)
	{
		typedef adjacency_list <vecS, vecS, undirectedS> Graph;
		typedef graph_traits<Graph>::vertex_descriptor Vertex;
		typedef graph_traits<Graph>::vertices_size_type VertexIndex;

		auto start = std::chrono::steady_clock::now();

		Graph graph(vertex_count);

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

		for(int i = 0; i < edge_count; i++)
		{
			random::taus88 gen(rand());
			random::taus88 gen1(rand());
			Vertex a = random_vertex(graph, gen);
			Vertex b = random_vertex(graph, gen1);

			if(a != b)
			{
				boost::tie(edge, flag) = add_edge(a, b, graph);
				if(ds.find_set(a) == ds.find_set(b))
				{
					results.push_back(i);
					//std::cout << std::endl << "Cycle found after " << i << " edges." << std::endl;
					break;
				}
				ds.union_set(a,b);
				//++show_progress;
			}
		}
			
		// BOOST_FOREACH(Vertex current_vertex, vertices(graph)) {
		// std::cout << "representative[" << current_vertex << "] = " <<
		// ds.find_set(current_vertex) << std::endl;
		//}

		//std::cout << std::endl;

		Components components(parent.begin(), parent.end());

		// BOOST_FOREACH(VertexIndex current_index, components) {
		//   std::cout << "component " << current_index << " contains: ";

		//   BOOST_FOREACH(VertexIndex child_index,
		//                 components[current_index]) {
		//     std::cout << child_index << " ";
		//   }

		//   std::cout << std::endl;
		// }

		//std::chrono::duration<double> diff = std::chrono::steady_clock::now() - start;

		//std::cout << diff.count() << " seconds needed." << std::endl;
		// std::ofstream outfile;
		//   outfile.open("results.txt", std::ios_base::app);
		//   outfile << "V: " << vertex_count << " E: " << edge_count << " TiS " << diff.count() <<"\n"; 
		
		++show_progress;	
	}
	std::ofstream outfile;
	outfile.open("results.txt", std::ios_base::app);
	for (std::vector<int>::iterator i = results.begin(); i != results.end(); ++i)
	{
		outfile << "," << *i << std::endl;	
	}
	return (0);	
}