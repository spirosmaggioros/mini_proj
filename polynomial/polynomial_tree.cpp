#include <bits/stdc++.h>

using namespace std;

struct node{
	int coeff;
	int expon;
	node *right , *left;
};


node *new_node(const int &coefficient , const int &exponent){
	node*p = new node;
	p -> coeff = coefficient;
	p -> expon = exponent;
	p -> right = p -> left = nullptr;
	return p;
}

node *insert(node *root ,const int &coefficient , const int &exponent){
	if(!root){return new_node(coefficient  , exponent);}
	if(root -> expon > exponent){
		root -> left = insert(root -> left  , coefficient , exponent);
	}
	else if(root -> expon < exponent){
		root -> right = insert(root -> right , coefficient , exponent);
	}
	else
	{
		root -> coeff += coefficient;
		return root;
	}
	return root;
}

double evaluate(node *root,const double &p){
	if(!root){return 0.0;}
	if(!root){return 0.0;}
	stack<node*> s;
	double sum = 0;
	s.push(root);
	while(!s.empty()){
		node *current = s.top();
		sum += current -> coeff * (pow(p , current -> expon));
		s.pop();
		if(current -> right){s.push(current -> right);}
		if(current -> left){s.push(current -> left);}
	}
	return sum;
}

void inorder__(ostream &out , node *root){
	if(root){
		inorder__(out , root -> right);
		out << root -> coeff << "x^" << root -> expon << " ";
		inorder__(out , root -> left);
	}
}

node *derivative(node *root){
	node *p = nullptr;
	if(!root){return root;}
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node *current = q.front();
		int coeff = current -> coeff * current -> expon;
		int exp = current -> expon - 1;
		p = insert(p , coeff , exp);
		q.pop();
		if(current -> right){q.push(current -> right);}
		if(current -> left){q.push(current -> left);}
	}
	return p;
}

node *double_derivative(node *root){
	node *p = derivative(root);
	if(!root){return root;}
	node *ans = nullptr;
	queue<node*> q;
	q.push(p);
	while(!q.empty()){
		node *current = q.front();
		int coeff = current -> coeff * current -> expon;
		int exp = current -> expon - 1;
		ans = insert(ans , coeff , exp);
		q.pop();
		if(current -> right){q.push(current -> right);}
		if(current -> left){q.push(current -> left);}
	}
	return ans;
}

string find_min_max(node *root ,const int &a ,const int &b){
	int mini = min(a, b);
	int maxi = max(a, b);
	vector<long double> evaluate_ans; 
	for(int i = mini; i <= maxi; i++){
		evaluate_ans.push_back(evaluate(root , i));
	}
	sort(evaluate_ans.begin() , evaluate_ans.end());
	string first = to_string(evaluate_ans[0]);
	string last = to_string(evaluate_ans[evaluate_ans.size() - 1]);
	return "Max , : " + last + " Min , : " + first;
}

int max_power(node *root){
	if(!root){return -1;}
	while(root){
		root = root -> right;
	}
	return root -> expon;
}

int min_power(node *root){
	if(!root){return -1;}
	while(root){
		root = root -> left;
	}
	return root -> expon;
}

ostream & operator << (ostream &out , node *root){
	if(!root){out << ""; return out;}
	inorder__(out , root);
	return out;
}


node* add__(node *root1 , node *root2){
	if((!root1 && !root2) || (root1 && !root2)){
		return root1;
	}
	else if(!root1 && root2){return root2;}
	node *root = nullptr;
	stack<node*> s;
	s.push(root1);
	while(!s.empty()){
		node *current = s.top();
		root = insert(root , current -> coeff , current -> expon);
		s.pop();
		if(current -> right){s.push(current -> right);}
		if(current -> left){s.push(current -> left);}
	}
	stack<node*> p;
	s.push(root2);
	while(!s.empty()){
		node *current = s.top();
		root = insert(root , current -> coeff , current -> expon);
		s.pop();
		if(current -> right){s.push(current -> right);}
		if(current -> left){s.push(current -> left);}
	}
	return root;
}

node *multipy__(node *root1 , node *root2){
	if(!root1 || !root2){return nullptr;}
	node *root = nullptr;
	vector<pair<int , int> > list_node;
	stack<node*> s;
	s.push(root1);
	while(!s.empty()){
		node *current = s.top();
		list_node.push_back(make_pair(current -> coeff , current -> expon));
		s.pop();
		if(current -> left){s.push(current -> left);}
		if(current -> right){s.push(current -> right);}
	}
	vector<pair<int , int > > ans;
	for(int i = 0; i<list_node.size(); i++){
		stack<node*> p;
		p.push(root2);
		while(!p.empty()){
			node *current = p.top();
			ans.push_back(make_pair(list_node[i].first * current -> coeff , list_node[i].second + current -> expon));
			p.pop();
			if(current -> left){p.push(current -> left);}
			if(current -> right){p.push(current -> right);}
		}
	}
	for(const auto & x : ans){
		root = insert(root , x.first , x.second);
	}
	return root;
}

int main(){
 	node *p = nullptr;
 	int a; cin >> a;//power
 	for(int i=0; i<a; i++){
 		int b , c; cin >> b >> c;
 		p = insert(p , b , c);
 	}
 	node *q = nullptr;
 	int b; cin >> b;
 	for(int i = 0; i<b; i++){
 		int c , d; cin >> c >> d;
 		q = insert(q , c , d);
 	}
 	cout << multipy__(p, q) << '\n';
 	cout << add__(p , q) << '\n';
 	cout << find_min_max(p, -10, 10) << '\n';
 	cout << derivative(p) << '\n';
}
