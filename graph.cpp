#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//������
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
			int from = matrix[i][1];       //��ʾ�ڵ��value
			int to = matrix[i][2];         //��ʾ�ڵ��value
			if (graph.nodes.find(from) == graph.nodes.end())
			{
				graph.nodes[from] = new Node(from);
			}
			if (graph.nodes.find(to) == graph.nodes.end()) 
			{
				graph.nodes[to] = new Node(to);
			}
			//��������if�����󣬱����ҵ� from ����to�ڵ�
			//Node* fromNode = graph.nodes.find(from)->second;   //������->first=key,������->secend=value
			//Node* toNode = graph.nodes.find(to)->second;

			Node* fromNode = graph.nodes[from];   
			Node* toNode = graph.nodes[to];
			//Ϊ graph �� from���ڵ�node ׼�� һ����
			Edge* newEdge = new Edge(weight, fromNode, toNode);
			//����������һ���ߣ� ��ָ��ڵ�����+1
			toNode->in++;
			//����������һ���ߣ� ָ��ڵ�ĳ���+1����ָ��Ľڵ�ȷ����ָ��ýڵ�ı�ȷ��
			fromNode->out++;

			fromNode->next.push_back(toNode);
			fromNode->edges.push_back(newEdge);
			//����if�ᱣ֤�����ڵ㣬���ﱣ֤ �ߵĴ��ڡ�
			graph.edges.insert(newEdge);
		}
		return graph;
	}
};
//������ȱ���
void bfs(Node* node)
{
	if (node == nullptr)
		return;
	queue<Node*> queue;
	unordered_set<Node*> set;   //�൱�ڽӱ���ڽӾ����visit����

	Node* help;
	queue.push(node);
	set.insert(node);

	while (!queue.empty())
	{
		help = queue.front();
		queue.pop();
		cout << help->value << endl;
		//�ó��ӵĵ�ǰ�ڵ����ҽ�ջ�ڵ�
		for (auto node : help->next)  //����next
		{
			if (set.find(node) == set.end()) 
			{
				queue.push(node);
				set.insert(node);
			}
		}
	}
}
//������ȱ���
void dfs(Node* node) 
{
	stack<Node*> stack;
	unordered_set<Node*> set;
	Node* help;
	//һ��������ջ����ӡ
	stack.push(node);
	set.insert(node);
	cout << node->value << endl;
	while (!stack.empty())
	{
		help = stack.top();
		stack.pop();
		//�Գ�ջ��Ԫ�ؽ����жϣ����ýڵ�Ĺ����ڵ㶼����ӡ���� ���߸ýڵ�û���������ӵ㣬��ô���Ԫ�ؾ�ok��
		//���ýڵ㻹�����������ڵ�û�����ʣ���ֱ�ӷ��ʺ��ٰѵ����ڵ�ͷ��ʽڵ㶼��ջ
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

	//���ɵ������ڵ�û����
	// cout << graph.nodes.find(1)->second->value;
	// cout << graph.nodes.find(2)->second->value;
	// cout << graph.nodes.find(3)->second->value<<endl;

	// unordered_set<Edge*>::iterator ite = graph.edges.begin();
	// while(ite != graph.edges.end()){
	// 	cout << "�����ߵ�Ȩ��Ϊ "<<(*ite)->weight <<endl;

	// 	cout<< "from:" <<(*ite)->from->value << "to: "<<(*ite)->to->value<<endl; 
	// 	ite++;
	// }

	Node* node = graph.nodes.find(1)->second;
	// bfs(node);
	dfs(node);

	return 0;
}
