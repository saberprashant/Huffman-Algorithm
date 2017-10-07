#include<iostream>
#include<string>
#include<map>
#include<queue>
#include<fstream>

using namespace std;

class HuffmanNode {
public:
    char data;
    int count;
    HuffmanNode *left, *right;

    HuffmanNode(char data, int count)
    {
        this->data = data;
        this->count = count;
        left = right = nullptr;
    }

};

class compare_smallfreq {      // making MIN PQ compare function
public:
    bool operator()(const HuffmanNode *one, const HuffmanNode *two) {
        return (one->count > two->count);  //to convert our PQ into a Min PQ with
    }                                     // greater function of frequencies.
};



//shorter method and don't need any other functions like
//printArr() and isLeaf()

void printCodes(HuffmanNode* root, string str, map<char, string> & secretCodes)
{
    if (!root)
        return;

    if (root->data != '$')
    {
        cout << root->data << ": " << str << endl;
        secretCodes[root->data] = str;
    }

    printCodes(root->left, str + "0", secretCodes);
    printCodes(root->right, str + "1", secretCodes);
}



int main(){

    /* this pq is min heap which is based on compare_smallfreq which is making it a min heap*/
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare_smallfreq> huffman_table;
    map<char, int> letter_count;
    map<char, string> secretCodes;

    ifstream input("input.txt");
    char c;
    while(input.get(c))
    {
        cout<<c;        // test for input.txt content
        letter_count[c]++;   // filling our map
    }
    cout<<endl;    // test for input.txt content
    input.close();


    /* get the frequency count of each letter */
    //for(char c : text)   // new way of filling a map
      //  letter_count[c]++;
    /*for(int i=0; i<strlen(text); i++)   // OLD WAY
        letter_count[input[i] = letter_count[input[i] + 1;*/

    /* put the character count into the huffman priority queue*/
    for(auto entry : letter_count) {
        HuffmanNode* n = new HuffmanNode(entry.first, entry.second);
        huffman_table.push(n);
    }

    /* build the tree */
    HuffmanNode* combined = nullptr;
    while(huffman_table.size() != 1) {
        /* pull the two lowest */
        HuffmanNode *low1 = huffman_table.top();
        huffman_table.pop();

        HuffmanNode *low2 = huffman_table.top();
        huffman_table.pop();

        combined = new HuffmanNode('$', low1->count + low2->count);
        combined->left = low1;
        combined->right = low2;
        huffman_table.push(combined);
    }
    HuffmanNode* root = combined;

    // Print Huffman codes using the Huffman tree built above
    printCodes(root, "", secretCodes);     // for easier method

    cout<<endl<<endl<<endl;         // testing
    cout<<secretCodes['a']<<endl;
    cout<<secretCodes['p'];

    ifstream input_again("input.txt");
    ofstream output;
    output.open("output.txt");
    char x;
    string str;
    while(input_again.get(x))
    {
        str = secretCodes[x];
        output << str;
    }
    input_again.close();
    output.close();

}




