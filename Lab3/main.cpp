
#include "Dictionary.cpp"
#include "ring.cpp"
#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

void SimpleTests();
void testAll();
void constructorTests();
void insertTests();
void testDiccionaryAllBooks();
void testRingWithBook();
void testRingSimple();
void SplitString(string s, vector<string> &v);
string removeSymbols(string lineString);
Dictionary <string, int>& counter (const string& fileName);
Ring <int, string>&  listing (const Dictionary <string, int>& Dict);
Ring <int, string>&  listingWithString (const Dictionary <string, int>& Dict);
Ring <int, string>&  listingWithVectors (const Dictionary <string, int>& Dict);


int main() {
    testRingWithBook();
  //  testAll();
  // insertTests();
  //testRingSimple();
    return 0;
}
 Dictionary <string, int>& counter (const string& fileName) {

    static Dictionary<string, int> tree;
    string myText;

// Read from the text file
    ifstream MyReadFile(fileName);

// Use a while loop together with the getline() function to read the file line by line
    if (MyReadFile.is_open())
    {
        while ( getline (MyReadFile,myText) )
        {
            string line = removeSymbols(myText);

            vector<string>words;

            SplitString(line, words);

            for(string word : words){
                if (word==" " || word==""|| isdigit(word[0])){

                }else{
                    if (tree.search(word)){
                        int newinfo= tree.getInfo(word) + 1;
                        tree.setInfo(word,newinfo);
                    }else {
                        tree.insert(word, 1);
                        //cout<<word<<" ";
                    }
                }
            }
         //   cout<<endl;

        }
        MyReadFile.close();
    }

    else cout << "Unable to open file";

    return tree;



}
string removeSymbols(string lineString){


    for (int i = 0; i < lineString.size(); i++) {

        // Finding the character whose
        // ASCII value fall under this
        // range
        if (!isalnum(lineString[i]) && lineString[i] != ' ')
        {
            // erase function to erase
            // the character
            lineString.erase(i, 1);
            i--;
        }
    }
    return lineString;

    /*
    string ret;

    string chars = "#!,.?¿¡-_')(:;";

    for (char c: chars) {
        lineString.erase(std::remove(lineString.begin(), lineString.end(), c), lineString.end());
    }

    std::cout << lineString;

    return lineString;
*/

}
void SplitString(string s, vector<string> &v){

    string temp = "";
    for(int i=0;i<s.length();++i){

        if(s[i]==' '){
            v.push_back(temp);
            temp = "";
        }
        else{
            temp.push_back(s[i]);
        }

    }
    v.push_back(temp);

}

Ring <int,string>&  listing (const Dictionary <string,int>& Dict){


    static Ring<int,string> ret;
    map<string,int> dicmap= Dict.getMap();

    map<string, int>::iterator it;

    for (it = dicmap.begin(); it != dicmap.end(); it++) {



        typename Ring<int, string>::Iterator itRing;
        itRing = ret.begin(true);
        typename Ring<int, string>::Iterator fin;
        fin = ret.end(true);
        typename Ring<int, string>::Iterator head;
        head = ret.begin(true);
        if (itRing.isEmpty()) {
            ret.insertAtBeg(it->second, it->first, true);
        } else {
            while (itRing.getKey() < it->second && itRing.operator!=(fin)) {

                itRing++;
            }
            if (itRing.getKey() == it->second) {

                while (itRing.getInfo() < it->first && itRing.operator!=(fin) && itRing.getKey() == it->second) {

                    itRing++;
                }
                if (itRing.operator==(fin)) {
                    if (itRing.getKey() > it->second) {
                        if (itRing.operator==(head)) {
                            ret.insertAtBeg(it->second, it->first, true);
                        } else {
                            ret.insertBefore(it->second, it->first, itRing, true);
                        }
                    } else {
                        ret.insertAtEnd(it->second, it->first, true);
                    }

                } else {
                    if (itRing.operator==(head)) {
                        ret.insertAtBeg(it->second, it->first, true);
                    } else {
                        ret.insertBefore(it->second, it->first, itRing, true);
                    }

                }

            } else {
                if (itRing.operator==(fin)) {
                    if (itRing.getKey() > it->second) {
                        if (itRing.operator==(head)) {
                            ret.insertAtBeg(it->second, it->first, true);
                        } else {
                            ret.insertBefore(it->second, it->first, itRing, true);
                        }


                    } else {
                        ret.insertAtEnd(it->second, it->first, true);

                    }

                } else {
                    if (itRing.operator==(head)) {
                        ret.insertAtBeg(it->second, it->first, true);
                    } else {
                        ret.insertBefore(it->second, it->first, itRing, true);
                    }

                }
            }

        }

    }


    return ret;
}
Ring <int, string>&  listingWithString (const Dictionary <string, int>& Dict){

    static Ring<int,string> ret;
    vector<string> dicvect= Dict.getVectorString();


    for (int i = 0; i < dicvect.size() ; i++) {

        string s = dicvect[i];
        string delimiter = ",";

        size_t pos = 0;
        string key;
        pos = s.find(delimiter);

        key = s.substr(0, pos);

        s.erase(0, pos + delimiter.length());
        int info= stoi(s);




        typename Ring<int, string>::Iterator itRing;
        itRing = ret.begin(true);
        typename Ring<int, string>::Iterator fin;
        fin = ret.end(true);
        typename Ring<int, string>::Iterator head;
        head = ret.begin(true);
        if (itRing.isEmpty()) {
            ret.insertAtBeg(info, key, true);
        } else {
            while (itRing.getKey() < info && itRing.operator!=(fin)) {

                itRing++;
            }
            if (itRing.getKey() == info) {

                while (itRing.getInfo() < key && itRing.operator!=(fin) && itRing.getKey() == info) {

                    itRing++;
                }
                if (itRing.operator==(fin)) {
                    if (itRing.getKey() > info) {
                        if (itRing.operator==(head)) {
                            ret.insertAtBeg(info, key, true);
                        } else {
                            ret.insertBefore(info, key, itRing, true);
                        }
                    } else {
                        ret.insertAtEnd(info, key, true);
                    }

                } else {
                    if (itRing.operator==(head)) {
                        ret.insertAtBeg(info, key, true);
                    } else {
                        ret.insertBefore(info, key, itRing, true);
                    }

                }

            } else {
                if (itRing.operator==(fin)) {
                    if (itRing.getKey() > info) {
                        if (itRing.operator==(head)) {
                            ret.insertAtBeg(info, key, true);
                        } else {
                            ret.insertBefore(info, key, itRing, true);
                        }


                    } else {
                        ret.insertAtEnd(info, key, true);

                    }

                } else {
                    if (itRing.operator==(head)) {
                        ret.insertAtBeg(info, key, true);
                    } else {
                        ret.insertBefore(info, key, itRing, true);
                    }

                }
            }

        }

    }


    return ret;
}

Ring <int, string>&  listingWithVectors (const Dictionary <string, int>& Dict){

    static Ring<int,string> ret;
    vector<string> dicVectKey= Dict.getVectorKey();
    vector<int> dicVectInfo= Dict.getVectorInfo();


    for (int i = 0; i < dicVectKey.size() ; i++) {





        typename Ring<int, string>::Iterator itRing;
        itRing = ret.begin(true);
        typename Ring<int, string>::Iterator fin;
        fin = ret.end(true);
        typename Ring<int, string>::Iterator head;
        head = ret.begin(true);
        if (itRing.isEmpty()) {
            ret.insertAtBeg(dicVectInfo[i], dicVectKey[i], true);
        } else {
            while (itRing.getKey() < dicVectInfo[i] && itRing.operator!=(fin)) {

                itRing++;
            }
            if (itRing.getKey() == dicVectInfo[i]) {

                while (itRing.getInfo() < dicVectKey[i] && itRing.operator!=(fin) && itRing.getKey() == dicVectInfo[i]) {

                    itRing++;
                }
                if (itRing.operator==(fin)) {
                    if (itRing.getKey() > dicVectInfo[i]) {
                        if (itRing.operator==(head)) {
                            ret.insertAtBeg(dicVectInfo[i], dicVectKey[i], true);
                        } else {
                            ret.insertBefore(dicVectInfo[i], dicVectKey[i], itRing, true);
                        }
                    } else {
                        ret.insertAtEnd(dicVectInfo[i], dicVectKey[i], true);
                    }

                } else {
                    if (itRing.operator==(head)) {
                        ret.insertAtBeg(dicVectInfo[i], dicVectKey[i], true);
                    } else {
                        ret.insertBefore(dicVectInfo[i], dicVectKey[i], itRing, true);
                    }

                }

            } else {
                if (itRing.operator==(fin)) {
                    if (itRing.getKey() > dicVectInfo[i]) {
                        if (itRing.operator==(head)) {
                            ret.insertAtBeg(dicVectInfo[i], dicVectKey[i], true);
                        } else {
                            ret.insertBefore(dicVectInfo[i], dicVectKey[i], itRing, true);
                        }


                    } else {
                        ret.insertAtEnd(dicVectInfo[i], dicVectKey[i], true);

                    }

                } else {
                    if (itRing.operator==(head)) {
                        ret.insertAtBeg(dicVectInfo[i], dicVectKey[i], true);
                    } else {
                        ret.insertBefore(dicVectInfo[i], dicVectKey[i], itRing, true);
                    }
                }
            }

        }

    }


    return ret;
}

void testAll(){

    SimpleTests();
    constructorTests();
    testRingSimple();
    testRingWithBook();


}
void SimpleTests()
{
    Dictionary<int,int> avlt;

    assert(avlt.isEmpty() && "FAILED: New tree isn't empty\n");
    cout << "A new tree should be empty: PASSED\n";

    assert(avlt.height() == 0 && "FAILED: New tree height isn't 0\n");
    cout << "A new tree's height is zero: PASSED\n";


    assert(avlt.numberOfElements() == 0 && "FAILED: New tree should have no nodes\n");
    cout << "A new tree should have no nodes: PASSED\n";

    int entry = 137;

    assert(avlt.insert(entry,1) && "FAILED: Should be able to add an entry\n");
    cout << "Should be able to add a new entry to the empty tree: PASSED\n";

    //assert(avlt.getInfo(entry) == 1 && "FAILED: Should be able to get the item\n");
    cout << "Should be able to get an item from the tree: PASSED\n";

    assert(avlt.search(entry) && "FAILED: Should be able see if the tree contains an added item\n");
    cout << "Should be able to see if the tree contains an added item: PASSED\n";

    assert(avlt.height() == 1 && "FAILED: The height of a tree with one entry should be 1\n");
    cout << "The height of a tree with one entry should be one: PASSED\n";



    assert(avlt.remove(entry) && "FAILED: Should be able to remove an entry\n");
    cout << "Should be able to remove an entry: PASSED\n";

    assert(!avlt.search(entry) && "FAILED: Should be able see if the tree doesn't contain a removed item\n");
    cout << "Should be able to see if the tree doesn't contain a removed item: PASSED\n";



    assert(!avlt.search(entry) && "FAILED: Entry should not be in tree\n");
    cout << "Removed entries should not be in tree: PASSED\n";

    assert(avlt.isEmpty() && "FAILED: An empty tree should be empty\n");
    cout << "An empty tree should be empty: PASSED\n";

    assert(avlt.height() == 0 && "FAILED: An empty tree should have a height of 0\n");
    cout << "An empty tree should have a height of 0: PASSED\n";

}
void constructorTests(){
    Dictionary<string,int> tree;

    assert(tree.isEmpty() && "FAILED\n");
    cout <<"Empty tree: PASSED\n";


    // Testing the Copy Constructor
    cout << "\nNow testing the copy constructor.\n";
    cout << "-- First with an initializing declaration: "
            "Dictionary<int> copy = intDictionary;\n";
    Dictionary<int,int> intDictionary;
    intDictionary.insert(2,1);

    Dictionary<int,int> copy = intDictionary;
    cout << "-- Inorder traversal of copy:\n";
    copy.inorderTraversal();
    cout << "\n\n-- Now by passing intDictionary to a value parameter:\n";
//I dont know why i need this function, because the copy constructor is called directly.
//makeCopy(intDictionary);
    cout << "\n--Check that original Dictionary hasn't been changed.\n"
            "-- Inorder traversal of original:\n";
    intDictionary.inorderTraversal();
    cout << endl;
//---- END PART 3 ----*/
// ---- PART 4 ----
// Testing the Assignment Operator
    cout << "\nNow testing the assignment constructor with the statement:\n";

    Dictionary<int,int> anotherDictionary2;
    copy = anotherDictionary2 = intDictionary;
    cout << "\n-- Inorder traversal of intDictionary:\n";
    intDictionary.inorderTraversal();
    cout << endl;
    cout << "\n-- Inorder traversal of anotherDictionary:\n";
    anotherDictionary2.inorderTraversal();
    cout << endl;
    cout << "\n-- Inorder traversal of copy:\n";
    copy.inorderTraversal();
    cout << endl;
    cout << " Now testing self-assignment with: copy = copy;\n";
    copy = copy;
    cout << endl;
    cout << "\n-- Inorder traversal of copy:\n";
    copy.inorderTraversal();
    cout << endl;




}
void insertTests(){

    Dictionary<int,int> intDictionary;
// test the class constructor
    cout << "Constructing empty Dictionary\n";
    cout << "Dictionary " << (intDictionary.isEmpty() ? "is" : "is not") << " empty\n";
// Testing inorder
    cout << "Inorder Traversal of Dictionary: \n";
    intDictionary.inorderTraversal();
    // Testing insert
    cout << "\nNow insert a bunch of integers into the Dictionary."
            "\nTry items not in the Dictionary and some that are in it:\n";
    int number;
    for (;;)
    {
        cout << "Item to insert (-999 to stop): ";
        cin >> number;
        if (number == -999) break;
        intDictionary.insert(number,1);
    }
    // intDictionary.graph(cout);
    cout << "Dictionary " << (intDictionary.isEmpty() ? "is" : "is not") << " empty\n";
    cout << "Inorder Traversal of Dictionary: \n";
    intDictionary.inorderTraversal();
    cout << endl;
// Testing search()
    cout << "\n\nNow testing the search() operation."
            "\nTry both items in the Dictionary and some not in it:\n";
    for (;;)
    {
        cout << "Item to find (-999 to stop): ";
        cin >> number;
        if (number == -999) break;
        cout << (intDictionary.search(number) ? "Found" : "Not found") << endl;
    }
// Testing remove()
    cout << "\nNow testing the remove() operation."
            "\nTry both items in the Dictionary and some not in it:\n";
    for (;;)
    {
        cout << "Item to remove (-999 to stop): ";
        cin >> number;
        if (number == -999) break;
        intDictionary.remove(number);
        //   intDictionary.graph(cout);
    }
    cout << "\nInorder Traversal of Dictionary: \n";
    intDictionary.inorderTraversal();
    intDictionary.preOrder2();
    intDictionary.preorderTraversal();
    cout << endl;

    cout << "\nInorder Traversal of Dictionary: \n";
    intDictionary.inorderTraversal();
    cout << "\nPreorder Traversal of Dictionary: \n";
    intDictionary.inorderTraversal();
    cout << "\nPostorder Traversal of Dictionary: \n";
    intDictionary.preorderTraversal();
    cout << endl;
}

void testDiccionaryAllBooks(){
    Dictionary<string,int>& tree = counter("Text books/Academic Regulations at the Warsaw University of Technology (ANSI).txt");
    tree.preOrder2();
    tree.printGraph();

    cout<<endl;
    cout<<endl;
    cout<<endl;

    Dictionary<string,int>& tree2 = counter("Text books/The Jungle Book by Rudyard Kipling (ANSI).txt");
    tree2.preOrder2();
    tree2.printGraph();

    cout<<endl;
    cout<<endl;
    cout<<endl;

    Dictionary<string,int>& tree3 = counter("Text books/Wuthering Heights by Emily Brontë (ANSI).txt");
    tree3.preOrder2();
    tree3.printGraph();
}
void testRingSimple(){
    Dictionary<string,int> tree;
    tree.insert("c",1);
    tree.insert("a",2);

    tree.insert("x",6);

    tree.insert("d",1);
    tree.insert("e",3);

    tree.insert("f",1);
    tree.insert("h",1);

    tree.insert("m",5);




    tree.printGraph();


    Ring<int,string>& ring= listing(tree);

    ring.print2(true);
}
void testRingWithBook(){

    Dictionary<string,int>& tree = counter("Text books/Academic Regulations at the Warsaw University of Technology (ANSI).txt");
  //  Dictionary<string,int>& tree = counter("Text books/Wuthering Heights by Emily Brontë (ANSI).txt");
   //  Dictionary<string,int>& tree = counter("Text books/The Jungle Book by Rudyard Kipling (ANSI).txt");
    tree.preOrder2();
    tree.printGraph();


    Ring<int,string>& ring= listing(tree);
   // Ring<int,string>& ring= listingWithString(tree);


    ring.print2(true);


}


