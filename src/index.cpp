#include "road_network.h"

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
using namespace road_network;

void preprocess_json(std::string filename,std::string output_name){
    Graph g;
    cout << endl << "reading graph from " << filename << endl;
    fstream fs(filename.c_str());
    //read_graph(g, std::cin);
    read_graph(g,fs);
    fs.close();
    vector<Edge> redundant_edges;
    g.get_redundant_edges(redundant_edges);
    for (Edge e : redundant_edges)
        g.remove_edge(e.a, e.b);
    vector<Neighbor> closest;
    g.contract(closest);
#ifdef NDEBUG
    srand(time(nullptr));
    g.randomize();
#endif
    // construct index
    vector<CutIndex> ci;
    g.create_cut_index(ci, 0.2);
    ContractionIndex con_index(ci, closest);
    // write index
    //json ? con_index.write_json(std::cout) : con_index.write(std::cout);
    //ofstream index_file;
    //index_file.open (output_name, ios::out | ios::app );
    //con_index.write_json(index_file);
    //con_index.write_json_v2(index_file);
    //index_file.close();
}
int main(int argc, char** argv)
{
    std::cout<<"run index"<<std::endl;
    return 0;
    bool json = false;
    if (argc > 1)
    {
        if (strcmp(argv[1], "-json") == 0)
            json = true;
        else
        {
            cerr << "Syntax: " << argv[0] << " [-json]" << endl;
            exit(0);
        }
    }

    if(json){
        std::string filename="/scratch1/zhou822/road_source/USA-road-d.NY.gr";
        std::string outputname ="NY_Label_json.hl";
        preprocess_json(filename,outputname);
    }
    // read graph
/*
    Graph g;
    const char* filename = "/scratch1/zhou822/road_source/USA-road-d.NY.gr";
    cout << endl << "reading graph from " << filename << endl;
    fstream fs(filename);
    //read_graph(g, std::cin);
    read_graph(g,fs);
    fs.close();
    vector<Edge> redundant_edges;
    g.get_redundant_edges(redundant_edges);
    for (Edge e : redundant_edges)
        g.remove_edge(e.a, e.b);
    vector<Neighbor> closest;
    g.contract(closest);
#ifdef NDEBUG
    srand(time(nullptr));
    g.randomize();
#endif
    // construct index
    vector<CutIndex> ci;
    g.create_cut_index(ci, 0.2);
    ContractionIndex con_index(ci, closest);
    // write index
    //json ? con_index.write_json(std::cout) : con_index.write(std::cout);
    ofstream index_file;
    index_file.open ("NY_Label_test.hl", ios::out | ios::app );
    //con_index.write_json(std::cout);
    //con_index.write_json(index_file);
    con_index.write(index_file);
    index_file.close();
    */

    /*
    ifstream index_file_in;
    index_file_in.open("NY_Label.hl", ios::in);
    ContractionIndex ic2(index_file_in);
    index_file_in.close();*/
    return 0;
}
