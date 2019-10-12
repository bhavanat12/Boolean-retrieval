#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <dirent.h>
using namespace std;
struct Node
{
	long long int data;
	long long int count;
	struct Node *next;
};
struct Permut
{
	string data;
	string term;
	struct Permut *next;
};
bool isOk(char c)
{
    if ( ispunct(c) )
        if ( c == '\'' )
            return false;
    return ispunct(c);
}
string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 
void Compute_query(string q1, string op, string q2, unordered_map <string, struct Node*> Indexing, int count);
void Calculate_Perm(vector<string> permuterm_res, unordered_map <string, struct Node*> Indexing);
void append(struct Permut** head_ref, string new_data, string Term);
void Calculate_output(vector<string> res1_t, vector<string> res2_t, string bool_q, unordered_map <string, struct Node*> Indexing, int count);
int main()
{
	unordered_map <string, struct Node*> Indexing;
	string Extension = "/Users/appletest/Desktop/Data_IR/documents/";
	vector<string> Filenames;
	DIR *dir = opendir("/Users/appletest/Desktop/Data_IR/documents");
	struct dirent *pdir;
	while((pdir = readdir(dir)) != NULL)
	{
		Filenames.push_back(pdir->d_name);
	}
	closedir(dir);
	int count = 0;
	vector <string>::iterator ptr;
	for (ptr = Filenames.begin(); ptr < Filenames.end(); ptr++)
	{
		string Name = *ptr;
		if (Name != ".." && Name != "."  && Name != ".DS_Store")
		{
			count++;
			string Text_files = Extension + Name;
			ifstream file(Text_files);
			size_t lastindex = Name.find_last_of(".");
		    string k = Name.substr(0, lastindex);
		    string word;
		    while(file >> word){
		        std::replace_if(word.begin(), word.end(), isOk, ' ');
		        istringstream ss(word);
		        word = removeSpaces(word);
		        if(Indexing.find(word) != Indexing.end())
		        {
		        	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
		        	temp = Indexing[word];
		        	int flag = 0;
		        	if(temp->data != stoi(k))
		        	{
			        	while(temp->next != NULL)
			        	{
			        		temp = temp->next;
			        		if(temp->data == stoi(k))
			        		{
			        			flag = 1;
			        			break;
			        		}
			        	}
			        	if(flag == 0)
			        	{
			        		struct Node *t = (struct Node*)malloc(sizeof(struct Node));
				        	t->data = stoi(k);
				        	t->next = NULL;
				        	temp->next = t;
				        	Indexing[word]->count++;
			        	}
			        }
		        }
		        else
		        {
		        	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
		        	temp->data = stoi(k);
		        	temp->count = 1;
		        	temp->next = NULL;
		        	Indexing[word] = temp;
		        }
		    }
		}
	}
	unordered_map <string, struct Node*>::iterator itr;
		    struct Node *q = (struct Node*)malloc(sizeof(struct Node));
		    for(itr = Indexing.begin(); itr!=Indexing.end(); itr++)
		    {
		    	q = itr->second;
		    	cout << itr->first << " (" << q->count << ") ";
		    	while(q!= NULL)
		    	{
		    		cout << " -> " << q->data;
		    		q = q->next;
		    	}
		    	cout << endl;
		    	// string Term_index = itr->first;
			    // 	string permuterm = Term_index + '$';
			    // 	for(int i=0; i<permuterm.length(); i++)
			    // 	{
			    // 		if(i!=0)
			    // 		{
				   //  		reverse(permuterm.begin(), permuterm.begin()+1);
				   //  		reverse(permuterm.begin()+1, permuterm.end());
				   //  		reverse(permuterm.begin(), permuterm.end());
				   //  	}
				   //  	cout << permuterm << endl;
			    // 	}
		    	// cout << endl;
		    }
	unordered_map <string, struct Node*>::iterator itr3;
	int n = 1;
	do
	{
		cout << "\nEnter the two query terms: " << endl;
		string q1, q2;
		cin >> q1 >> q2;
		string bool_operator;
		cout << "Enter the boolean operator - (AND) or (OR) or (AND NOT) or (OR NOT): " << endl;
		getline(cin, bool_operator);
		while(bool_operator.length() == 0)
			getline(cin, bool_operator);
		cout << "Processing the query ----- " << q1 << " " << bool_operator << " " << q2 << endl; 
		Compute_query(q1, bool_operator, q2, Indexing, count);
		cout << "-----------------Wild card queries----------------\n\n";
		cout << "\na) Enter wildcard query of the form X* or *X: \n";
		string wq;
		cin >> wq;
		string s2;
		string s1;
		int len = wq.length();
		unordered_map <string, struct Node*>::iterator itr1;
		vector <string> results_part;
		int Length;
		if(wq[0] == '*')
		{
			s2 = wq.substr(1, len-1);
			cout << "terms ending with " << s2 << ":" << endl;
			Length = len-1;
			for(itr1 = Indexing.begin(); itr1!=Indexing.end(); itr1++)
			{
				s1 = itr1->first;
				int check_len = s1.length();
				int i=0;
				int flag = 0;
				while(i < Length && i < check_len)
				{
					if(s2[Length-i-1] != s1[check_len-i-1] || Length > check_len)
					{
						flag = 1;
						break;
					}
					i++;
				}
				if(flag == 0)
					results_part.push_back(s1);
			}
		}
		else
		{
			s2 = wq.substr(0, len-1);
			cout << "terms starting with " << s2 << ":" << endl;
			Length = len-1;
			for(itr1 = Indexing.begin(); itr1!=Indexing.end(); itr1++)
			{
				s1 = itr1->first;
				int check_len = s1.length();
				int i=0;
				int flag = 0;
				while(i < Length && i < check_len)
				{
					if(s2[i] != s1[i] || Length > check_len)
					{
						flag = 1;
						break;
					}
					i++;
				}
				if(flag == 0)
					results_part.push_back(s1);
			}
		}
		Calculate_Perm(results_part, Indexing);
		
		cout << "\n\nPress :\n1 - to give more queries\n0 - to exit\n";
		cin >> n;
	}while(n);
	return 0;
}
void Compute_query(string q1, string op, string q2, unordered_map <string, struct Node*> Indexing, int count)
{
	struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
	if(Indexing.find(q1)==Indexing.end() || Indexing.find(q2) == Indexing.end())
	{
		cout << "One or more of the query terms entered is not present in the documents\n";
		return;
	}
	temp1 = Indexing[q1];
	struct Node *temp2 = (struct Node*)malloc(sizeof(struct Node));
	temp2 = Indexing[q2];
	if(op == "AND NOT" || op == "OR NOT")
	{
		int count_1 = temp1->count;
		int count_2 = count - (temp2->count);
		struct Node *Temp2 = (struct Node*)malloc(sizeof(struct Node));
		int first = 0;
		for(int i=1; i<=count; i++)
		{
			if(temp2 == NULL || temp2->data != i)
			{
				if(first == 0)
				{
					Temp2->data = i;
					Temp2->next = NULL;
					first = 1;
				}
				else
				{
					struct Node *cat = (struct Node*)malloc(sizeof(struct Node));
					cat->data = i;
					cat->next = Temp2;
					Temp2 = cat;
				}
			}
			else
				temp2 = temp2->next;
		}
		struct Node *main_temp2 = (struct Node*)malloc(sizeof(struct Node));
		main_temp2->data = Temp2->data;
		main_temp2->next = NULL;
		Temp2 = Temp2->next;
		while(Temp2)
		{
			struct Node *s = (struct Node*)malloc(sizeof(struct Node));
			s->data = Temp2->data;
			s->next = main_temp2;
			main_temp2 = s;
			Temp2 = Temp2->next;
		}
		main_temp2->count = count_2;
		if(count_1 > count_2)
		{
			struct Node *Temp = (struct Node*)malloc(sizeof(struct Node));
			Temp = temp1;
			temp1 = main_temp2;
			main_temp2 = Temp;
		}
		vector <int> Output;
		if(op == "AND NOT")
		{
			while(temp1 != NULL && main_temp2 != NULL)
			{
				if(temp1->data == main_temp2->data)
				{
					Output.push_back(temp1->data);
					temp1 = temp1->next;
					main_temp2 = main_temp2->next;
				}
				else if(temp1->data < main_temp2->data)
					temp1 = temp1->next;
				else
					main_temp2 = main_temp2->next;
			}
			for(auto ir = Output.begin(); ir != Output.end(); ++ir)
				cout << *ir << " ";
			cout << endl;
		}
		else
		{
			while(temp1 != NULL && main_temp2 != NULL)
			{
				if(temp1->data < main_temp2->data)
				{
					Output.push_back(temp1->data);
					temp1 = temp1->next;
				}
				else if(temp1->data > main_temp2->data)
				{
					Output.push_back(main_temp2->data);
					main_temp2 = main_temp2->next;
				}
				else
				{
					Output.push_back(temp1->data);
					temp1 = temp1->next;
					main_temp2 = main_temp2->next;
				}
			}
			if(temp1 != NULL)
				Output.push_back(temp1->data);
			if(main_temp2 != NULL)
				Output.push_back(main_temp2->data);
			for(auto ir = Output.begin(); ir != Output.end(); ++ir)
				cout << *ir << " ";
			cout << endl;
		}
		return;
	}
	int count_1 = temp1->count;
	int count_2 = temp2->count;
	if(count_1 > count_2)
	{
		struct Node *Temp = (struct Node*)malloc(sizeof(struct Node));
		Temp = temp1;
		temp1 = temp2;
		temp2 = Temp;
	}
	vector <int> Output;
	if(op == "AND")
	{
		while(temp1 != NULL && temp2 != NULL)
		{
			if(temp1->data == temp2->data)
			{
				Output.push_back(temp1->data);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else if(temp1->data < temp2->data)
				temp1 = temp1->next;
			else
				temp2 = temp2->next;
		}
		for(auto ir = Output.begin(); ir != Output.end(); ++ir)
			cout << *ir << " ";
		cout << endl;
	}
	else if(op == "OR")
	{
		while(temp1 != NULL && temp2 != NULL)
		{
			if(temp1->data < temp2->data)
			{
				Output.push_back(temp1->data);
				temp1 = temp1->next;
			}
			else if(temp1->data > temp2->data)
			{
				Output.push_back(temp2->data);
				temp2 = temp2->next;
			}
			else
			{
				Output.push_back(temp1->data);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		while(temp1 != NULL)
		{
			Output.push_back(temp1->data);
			temp1 = temp1->next;
		}
		while(temp2 != NULL)
		{
			Output.push_back(temp2->data);
			temp2 = temp2->next;
		}
		for(auto ir = Output.begin(); ir != Output.end(); ++ir)
			cout << *ir << " ";
		cout << endl;
	}
	return;
}
void Calculate_Perm(vector<string> permuterm_res, unordered_map <string, struct Node*> Indexing)
{

			if(permuterm_res.size() == 0)
			{
				cout << "No documents present has substring of that format. \n";
				return;
			}
			for(int i=0; i<permuterm_res.size(); i++)
		    {
		    	cout << "( " << permuterm_res[i] << " ) ";
		    	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
		    	p = Indexing[permuterm_res[i]];
		    	while(p)
		    	{
		    		cout << " -> " << p->data;
		    		p = p->next; 
		    	}
		    	cout << endl;
		    }
			if(permuterm_res.size() == 1)
			{
				struct Node *one = (struct Node*)malloc(sizeof(struct Node));
				one = Indexing[permuterm_res[0]];
				cout << "Result is:\n";
				while(one!=NULL)
				{
					cout << one->data << " ";
		    		one = one->next;
				}
				cout << endl;
			}
			else
			{
				string b = permuterm_res[0];
				struct Node *first = (struct Node*)malloc(sizeof(struct Node));
				first = Indexing[b];
				vector <int> first_list;
				while(first!=NULL)
				{
					first_list.push_back(first->data);
					first = first->next;
				}
				string c = permuterm_res[1];
				struct Node *second = (struct Node*)malloc(sizeof(struct Node));
				second = Indexing[c];
				vector <int> second_list;
				while(second!=NULL)
				{
					second_list.push_back(second->data);
					second = second->next;
				}
				vector <int> Output;
				int n1 = 0;
				int n2 = 0;
				while(n1 < first_list.size() && n2 < second_list.size())
				{
					if(first_list[n1] < second_list[n2])
					{
						Output.push_back(first_list[n1]);
						n1++;
					}
					else if(first_list[n1] > second_list[n2])
					{
						Output.push_back(second_list[n2]);
						n2++;
					}
					else
					{
						Output.push_back(first_list[n1]);
						n1++;
						n2++;
					}
				}
				while(n1 < first_list.size())
				{
					Output.push_back(first_list[n1]);
					n1++;
				}
				while(n2 < second_list.size())
				{
					Output.push_back(second_list[n2]);
					n2++;
				}
				for(int i = 2; i<permuterm_res.size(); i++)
				{ 
					struct Node *traversal = (struct Node*)malloc(sizeof(struct Node));
					traversal = Indexing[permuterm_res[i]];
					vector <int> mod_temp;
					while(traversal)
					{
						mod_temp.push_back(traversal->data);
						traversal = traversal->next;
					}
					vector <int> Final_result;
					n1 = 0;
					n2 = 0;
					while(n1 < Output.size() && n2 < mod_temp.size())
					{
						if(Output[n1] < mod_temp[n2])
						{
							Final_result.push_back(Output[n1]);
							n1++;
						}
						else if(Output[n1] > mod_temp[n2])
						{
							Final_result.push_back(mod_temp[n2]);
							n2++;
						}
						else
						{
							Final_result.push_back(Output[n1]);
							n1++;
							n2++;
						}
					}
					while(n1 < Output.size())
					{
						Final_result.push_back(Output[n1]);
						n1++;
					}
					while(n2 < mod_temp.size())
					{
						Final_result.push_back(mod_temp[n2]);
						n2++;
					}
					Output = Final_result;
				}
				cout << "Final output : \n";
				for(int i=0; i<Output.size(); i++)
					cout << Output[i] << " ";
				cout << endl;
			}
	return;
}
void append(struct Permut** head_ref, string new_data, string Term)
{
	struct Permut* new_node = (struct Permut*)malloc(sizeof(struct Permut));
	struct Permut* last = *head_ref;
	new_node->data = new_data;
	new_node->term = Term;
	new_node->next = NULL;
	if(*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}
	while(last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}
void Calculate_output(vector<string> res1_t, vector<string> res2_t, string op, unordered_map <string, struct Node*> Indexing, int count)
{
	vector<int> res1;
	vector<int> res2;
	vector<string> permuterm_res;
	permuterm_res = res1_t;
	if(permuterm_res.size() == 0)
	{
		cout << "No documents present has substring of that format. \n";
		return;
	}
	for(int i=0; i<permuterm_res.size(); i++)
	{
		cout << "( " << permuterm_res[i] << " ) ";
		struct Node *p = (struct Node*)malloc(sizeof(struct Node));
		p = Indexing[permuterm_res[i]];
		while(p)
		{
		    cout << " -> " << p->data;
		    p = p->next; 
		}
		cout << endl;
	}
    if(permuterm_res.size() == 1)
	{
		struct Node *one = (struct Node*)malloc(sizeof(struct Node));
		one = Indexing[permuterm_res[0]];
		cout << "Result is:\n";
		while(one!=NULL)
		{
			cout << one->data << " ";
		    one = one->next;
		}
		cout << endl;
	}
	else
	{
		string b = permuterm_res[0];
		struct Node *first = (struct Node*)malloc(sizeof(struct Node));
		first = Indexing[b];
		vector <int> first_list;
		while(first!=NULL)
		{
			first_list.push_back(first->data);
			first = first->next;
		}
		string c = permuterm_res[1];
		struct Node *second = (struct Node*)malloc(sizeof(struct Node));
		second = Indexing[c];
		vector <int> second_list;
		while(second!=NULL)
		{
			second_list.push_back(second->data);
			second = second->next;
		}
		int n1 = 0;
		int n2 = 0;
		while(n1 < first_list.size() && n2 < second_list.size())
		{
			if(first_list[n1] < second_list[n2])
			{
				res1.push_back(first_list[n1]);
				n1++;
			}
			else if(first_list[n1] > second_list[n2])
			{
				res1.push_back(second_list[n2]);
				n2++;
			}
			else
			{
				res1.push_back(first_list[n1]);
				n1++;
				n2++;
			}
		}
		while(n1 < first_list.size())
		{
			res1.push_back(first_list[n1]);
			n1++;
		}
		while(n2 < second_list.size())
		{
			res1.push_back(second_list[n2]);
			n2++;
		}
		for(int i = 2; i<permuterm_res.size(); i++)
		{ 
			struct Node *traversal = (struct Node*)malloc(sizeof(struct Node));
			traversal = Indexing[permuterm_res[i]];
			vector <int> mod_temp;
			while(traversal)
			{
				mod_temp.push_back(traversal->data);
				traversal = traversal->next;
			}
			vector <int> Final_result;
			n1 = 0;
			n2 = 0;
			while(n1 < res1.size() && n2 < mod_temp.size())
			{
				if(res1[n1] < mod_temp[n2])
				{
					Final_result.push_back(res1[n1]);
					n1++;
				}
				else if(res1[n1] > mod_temp[n2])
				{
					Final_result.push_back(mod_temp[n2]);
					n2++;
				}
				else
				{
					Final_result.push_back(res1[n1]);
					n1++;
					n2++;
				}
			}
			while(n1 < res1.size())
			{
				Final_result.push_back(res1[n1]);
				n1++;
			}
			while(n2 < mod_temp.size())
			{
				Final_result.push_back(mod_temp[n2]);
				n2++;
			}
			res1 = Final_result;
		}
		cout << "Temp output : \n";
		for(int i=0; i<res1.size(); i++)
			cout << res1[i] << " ";
		cout << endl;
	}
	permuterm_res = res2_t;
	if(permuterm_res.size() == 0)
	{
		cout << "No documents present has substring of that format. \n";
		return;
	}
	for(int i=0; i<permuterm_res.size(); i++)
	{
		cout << "( " << permuterm_res[i] << " ) ";
		struct Node *p = (struct Node*)malloc(sizeof(struct Node));
		p = Indexing[permuterm_res[i]];
		while(p)
		{
		    cout << " -> " << p->data;
		    p = p->next; 
		}
		cout << endl;
    }
	if(permuterm_res.size() == 1)
    {
		struct Node *one = (struct Node*)malloc(sizeof(struct Node));
		one = Indexing[permuterm_res[0]];
		cout << "Result is:\n";
	    while(one!=NULL)
	    {
		    cout << one->data << " ";
		    one = one->next;
		}
	    cout << endl;
	}
	else
	{
		string b = permuterm_res[0];
		struct Node *first = (struct Node*)malloc(sizeof(struct Node));
		first = Indexing[b];
	    vector <int> first_list;
		while(first!=NULL)
	    {
			first_list.push_back(first->data);
			first = first->next;
		}
		string c = permuterm_res[1];
	    struct Node *second = (struct Node*)malloc(sizeof(struct Node));
		second = Indexing[c];
		vector <int> second_list;
		while(second!=NULL)
		{
			second_list.push_back(second->data);
			second = second->next;
		}
		int n1 = 0;
		int n2 = 0;
		while(n1 < first_list.size() && n2 < second_list.size())
		{
			if(first_list[n1] < second_list[n2])
			{
				res2.push_back(first_list[n1]);
				n1++;
			}
			else if(first_list[n1] > second_list[n2])
		    {
				res2.push_back(second_list[n2]);
				n2++;
			}
			else
			{
				res2.push_back(first_list[n1]);
				n1++;
				n2++;
			}
		}
		while(n1 < first_list.size())
	    {
			res2.push_back(first_list[n1]);
			n1++;
		}
		while(n2 < second_list.size())
		{
		    res2.push_back(second_list[n2]);
			n2++;
		}
		for(int i = 2; i<permuterm_res.size(); i++)
		{ 
			struct Node *traversal = (struct Node*)malloc(sizeof(struct Node));
			traversal = Indexing[permuterm_res[i]];
			vector <int> mod_temp;
			while(traversal)
			{
				mod_temp.push_back(traversal->data);
				traversal = traversal->next;
			}
			vector <int> Final_result1;
			n1 = 0;
			n2 = 0;
			while(n1 < res2.size() && n2 < mod_temp.size())
			{
				if(res2[n1] < mod_temp[n2])
				{
					Final_result1.push_back(res2[n1]);
					n1++;
				}
				else if(res2[n1] > mod_temp[n2])
				{
					Final_result1.push_back(mod_temp[n2]);
					n2++;
				}
				else
				{
					Final_result1.push_back(res2[n1]);
					n1++;
					n2++;
				}
			}
			while(n1 < res2.size())
			{
				Final_result1.push_back(res2[n1]);
				n1++;
			}
			while(n2 < mod_temp.size())
			{
				Final_result1.push_back(mod_temp[n2]);
				n2++;
			}
			res2 = Final_result1;
		}
		cout << "\nTemp output : \n";
		for(int i=0; i<res2.size(); i++)
			cout << res2[i] << " ";
		cout << endl;
	}
	vector <int> Output;
	int i=0;
	int j=0;
	if(op == "AND")
	{
		while(i<res1.size() && j<res2.size())
		{
			if(res1[i]==res2[j])
			{
				Output.push_back(res1[i]);
				i++;
				j++;
			}
			else if(res1[i] < res2[j])
				i++;
			else
				j++;
		}
		for(auto ir = Output.begin(); ir != Output.end(); ++ir)
			cout << *ir << " ";
		cout << endl;
	}
	else if(op == "OR")
	{
		while(i<res1.size() && j<res2.size())
		{
			if(res1[i] < res2[j])
			{
				Output.push_back(res1[i]);
				i++;
			}
			else if(res1[i] > res2[j])
			{
				Output.push_back(res2[j]);
				j++;
			}
			else
			{
				Output.push_back(res1[i]);
				i++;
				j++;
			}
		}
		while(i<res1.size())
		{
			Output.push_back(res1[i]);
			i++;
		}
		while(j<res2.size())
		{
			Output.push_back(res2[j]);
			j++;
		}
		cout << "\nFinal Output\n";
		for(auto ir = Output.begin(); ir != Output.end(); ++ir)
			cout << *ir << " ";
		cout << endl;
	}
	return;
}