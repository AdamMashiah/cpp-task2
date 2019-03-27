namespace ariel {
	class BST
	{
	private:

		struct node
		{
			int key;
			node* left;
			node* right;
		};

		node* Root;
		void addleafprivate(int key, node* ptr);
		void printinorderprivate(node* ptr);
		node* returnodeprivate(int key, node* ptr);
		int findsmallestprivate(node* ptr);
		void removenodeprivate(int key, node* ptr);
		void removerootmatch();
		void removematch(node* ptr, node* mch, bool left);
		void removesubtree(node* ptr);
		bool containsprivate(node* ptr, int key);
		int sizeprivate(node* ptr);
		int parentprivate(node* ptr, int key);
	public:

		BST();
		~BST();
		int left(int key);
		int right(int key);
		void remove(int key);
		node* CreateLeaf(int key);
		void insert(int key);
		void print();
		node* returnode(int key);
		int root();
		void printchildren(int key);
		int findsmallest();
		bool contains(int key);
		int size();
		int parent(int key);
	};
}

