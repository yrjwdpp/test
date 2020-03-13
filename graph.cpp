#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//解依赖
class Edge;

class Node 
{
public:
	int value;
	int in;
	int out;
	list<Node*> next;
	list<Edge*> edges;
	Node(int value) 
	{
		this->value = value;
		in = 0;
		out = 0;
	}
};

class Edge 
{
public:
	int weight;
	Node* from;
	Node* to;
	Edge(int weight, Node* from, Node* to) 
	{
		this->weight = weight;
		this->from = from;
		this->to = to;
	}
};
class Graph 
{
public:
	unordered_map<int, Node*> nodes;
	unordered_set<Edge*> edges;
};

class GraphGenerator 
{
public:
	Graph createGraph(int matrix[][3], int rows, int col) 
	{
		Graph graph;
		for (int i = 0; i < rows; i++) 
		{
			int weight = matrix[i][0];
			int from = matrix[i][1];       //表示节点的value
			int to = matrix[i][2];         //表示节点的value
			if (graph.nodes.find(from) == graph.nodes.end())
			{
				graph.nodes[from] = new Node(from);
			}
			if (graph.nodes.find(to) == graph.nodes.end()) 
			{
				graph.nodes[to] = new Node(to);
			}
			//以上两个if操作后，必能找到 from 好人to节点
			//Node* fromNode = graph.nodes.find(from)->second;   //迭代器->first=key,迭代器->secend=value
			//Node* toNode = graph.nodes.find(to)->second;

			Node* fromNode = graph.nodes[from];   
			Node* toNode = graph.nodes[to];
			//为 graph 和 from所在的node 准备 一条边
			Edge* newEdge = new Edge(weight, fromNode, toNode);
			//对于新增的一条边， 被指向节点的入度+1
			toNode->in++;
			//对于新增的一条边， 指向节点的出度+1，所指向的节点确定，指向该节点的边确定
			fromNode->out++;

			fromNode->next.push_back(toNode);
			fromNode->edges.push_back(newEdge);
			//两个if会保证建立节点，这里保证 边的存在。
			graph.edges.insert(newEdge);
		}
		return graph;
	}
};
//广度优先遍历
void bfs(Node* node)
{
	if (node == nullptr)
		return;
	queue<Node*> queue;
	unordered_set<Node*> set;   //相当邻接表和邻接矩阵的visit数组

	Node* help;
	queue.push(node);
	set.insert(node);

	while (!queue.empty())
	{
		help = queue.front();
		queue.pop();
		cout << help->value << endl;
		//用出队的当前节点来找进栈节点
		for (auto node : help->next)  //遍历next
		{
			if (set.find(node) == set.end()) 
			{
				queue.push(node);
				set.insert(node);
			}
		}
	}
}
//深度优先遍历
void dfs(Node* node) 
{
	stack<Node*> stack;
	unordered_set<Node*> set;
	Node* help;
	//一进来就入栈并打印
	stack.push(node);
	set.insert(node);
	cout << node->value << endl;
	while (!stack.empty())
	{
		help = stack.top();
		stack.pop();
		//对出栈的元素进行判断，若该节点的关联节点都被打印过了 或者该节点没其他关联接点，那么这个元素就ok了
		//若该节点还有其他关联节点没被访问，则直接访问后，再把弹出节点和访问节点都入栈
		for (auto node : help->next)
		{
			if (set.find(node) == set.end()) 
			{
				cout << node->value << endl;
				stack.push(help);
				stack.push(node);
				set.insert(node);
				break;                 
			}
		}  
	}
}

int main() 
{
	GraphGenerator g;
	// int matrix[][3]= {{1,1,2},{2,2,3},{3,3,1}};
	int matrix[][3] = { {0,1,2},{0,2,7} ,{0,1,4},{0,2,3}, {0,1,3},{0,7,3},
				{0,3,5},{0,4,6} };
	int length = sizeof(matrix) / sizeof(matrix[0]);
	Graph graph = g.createGraph(matrix, length, 3);
	//test for list
	// Node* node = graph.nodes.find(1)->second;
	// for(auto node : node->next)
	//{
	// 	cout<< node->value<<endl;
	// }

	//生成的三个节点没问题
	// cout << graph.nodes.find(1)->second->value;
	// cout << graph.nodes.find(2)->second->value;
	// cout << graph.nodes.find(3)->second->value<<endl;

	// unordered_set<Edge*>::iterator ite = graph.edges.begin();
	// while(ite != graph.edges.end()){
	// 	cout << "这条边的权重为 "<<(*ite)->weight <<endl;

	// 	cout<< "from:" <<(*ite)->from->value << "to: "<<(*ite)->to->value<<endl; 
	// 	ite++;
	// }

	Node* node = graph.nodes.find(1)->second;
	// bfs(node);
	dfs(node);

	return 0;
}
