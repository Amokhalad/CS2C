#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility> // std::pair
#include <limits>  // infinity
#include <queue> // std::priority_queue
#include <algorithm> // std::reverse
using namespace std;

vector<string> read_words(const string & file_path) {
    ifstream f(file_path);
    vector<string> lines;
//    TODO: Add code if fails to open
    for (string line; getline(f, line); ) {
        lines.push_back(line);
    }
//    TODO: Throw an exception if an error happened reading from f.
    return lines;
}








/*For Dijkstra's algorithm
 * we need a directed graph
 * every edge has a weight.*/

class WeightedStringGraph {
public:
    typedef string Node;
    struct Edge {
        Node src, dst;   // source, destination
        double weight;
        Edge(Node  src, Node  dst, double weight) : src(std::move(src)), dst(std::move(dst)), weight(weight) {}
        bool operator <(const Edge & rhs) const {
            return src < rhs.src || (src == rhs.src && dst < rhs.dst);
        }
        bool operator ==(const Edge & rhs) const {
            return src == rhs.src && dst == rhs.dst;
        }
        bool operator !=(const Edge & rhs) const {
            return src != rhs.src || dst != rhs.dst;
        }
    };

    map<Node, set<Edge>> edges;  // normally this would be private, but for the sake of this example, it's public.

    void insert_node(const Node & n) {
        edges[n];
    }
    void insert_edge(const Node & src, const Node & dst, double weight) {
        // TODO: consider throwing an exception if the edge already exists.
        // Node: this addes the src Node *and* the edge.
        edges[src].emplace(src, dst, weight);
        insert_node(dst);
    }

    void print_graphviz() {
        cout << "digraph g {" << endl;
        for (const auto& node_edges_pair : edges) {
            for (const WeightedStringGraph::Edge& edge : node_edges_pair.second) {
                cout << "\t\"" << edge.src << "\" -> \""  << edge.dst << "\"\n";
            }
        }
        cout << "}\n";
    }
};

/* Word graph where if you change a single character, you can get another word.
 * Like Cat, Cap   ->   Change t into p and you get cap.
 *
 * Ex:
 * Cat, Cup, Cap
 *  Cat and Cup don't have an edge because they differ by two characters
 *  Cat -> Cap
 *  Cap -> Cup
 *
 *  Table: Map.
     *  Ca*: cat, cap
     *  Cu*: cup
     *  C*t: cat
     *  C*p: cap, cup
     *  *at: cat
     *  *up: cup
     *  *ap: cap
 * */
WeightedStringGraph word_graph(const vector<string> & words) {
    map<string , vector<string> > close_words;
    for (const string & w : words) {
        string canonical_word = w;
        for (int i = 0; i < w.size(); ++i) { // for every character in a word, add an entry with * for example, in cat we would insert, *at, c*t, ca*.
            canonical_word[i] = '*';
            close_words[canonical_word].push_back(w);
            canonical_word = w;
        }
    }
    WeightedStringGraph graph;
    for(const auto& cword_words_pair : close_words) {
        for (const string& w1 : cword_words_pair.second) {
            for (const string& w2 : cword_words_pair.second) {
                if (w1 == w2)
                    continue;

                graph.insert_edge(w1, w2, 1); // edge weights 1 because they differ by 1 character.
            }
        }
    }
    return graph;
}

struct DijkstrasQueueEntry {
    typedef WeightedStringGraph::Node Node;
    Node node;
    Node prev_node;
    double path_weight;
    DijkstrasQueueEntry(Node node, Node prev_node, double path_weight) : node(move(node)), prev_node(move(prev_node)), path_weight(path_weight) { }
    bool operator <(const DijkstrasQueueEntry & rhs) const { // flips max heap to min heap.
        return path_weight > rhs.path_weight;
    }
};
// TODO: Make graph const again, THIS IS A HACK.
vector<WeightedStringGraph::Node> dijkstras(WeightedStringGraph & graph, const WeightedStringGraph::Node & start, const WeightedStringGraph::Node & destination) {
    typedef WeightedStringGraph::Node Node;
    map<Node, double> min_weight;
    map<Node, Node> prev_node;
    // Creating Table.
    for (const auto & node_edges_pair : graph.edges) {
        const Node node = node_edges_pair.first;
        min_weight[node] = numeric_limits<double>::infinity();
        // if the prev_node[x] == node, that's how we indicate that there is no previous node.
        prev_node[node] = node;
    }
    // Priority Queue, with priority being the distance.
    priority_queue<DijkstrasQueueEntry> q;
    q.emplace(start, start, 0);
    while(!q.empty()) {
        // Get the next entry to populate
        const DijkstrasQueueEntry& entry = q.top();
        // Process that entry and adding new paths.
        // Check if the entry corresponds to a new shorter path or not.
        if (entry.path_weight < min_weight[entry.node]) {
            min_weight[entry.node] = entry.path_weight;
            prev_node[entry.node] = entry.prev_node;

            for (const WeightedStringGraph::Edge & edge : graph.edges[entry.node]) {
                q.emplace(edge.dst, entry.node, entry.path_weight + edge.weight);
            }
            if (entry.node == destination) { // we can break early.
                break;
            }
        }
        q.pop();
    }
    // At this point, min_weight and prev_node are filled out as much as we need
    // Now we back track to construct the path and return the path.
    vector<Node> reversed_path;
    reversed_path.push_back(destination);
    while(reversed_path[reversed_path.size() - 1] != start) {
        reversed_path.push_back(prev_node[reversed_path[reversed_path.size() - 1]]);
    }
    reverse(reversed_path.begin(), reversed_path.end());
    return reversed_path;
}


int main() {
    vector<string> words;
    for (const string & w : read_words("/Users/aljuboori/Desktop/words.txt")) {
        if (w.size() == 3 && w[0] == 'b') {
            words.push_back(w);
        }
    }
    WeightedStringGraph graph = word_graph(words);
    vector<string> path = dijkstras(graph, "boy", "bar");
    for (const string& w : path) {
        cout << w << endl;
    }
    return 0;
}
 