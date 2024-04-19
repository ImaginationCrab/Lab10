#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* children[26];
};
struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
int length = strlen(word);
char temp;
for(int i = 0;i<length;i++){
    temp = word[i];

    if(pTrie->children[temp-'a']==NULL){
    pTrie->children[temp-'a'] = createTrie();
    pTrie->children[temp-'a']->count++;
    }
    else{
        pTrie->children[temp-'a']->count++;
    }
    pTrie = pTrie->children[temp-'a'];
}
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    
int length = strlen(word);
char temp;
for(int i = 0;i<length;i++){
    temp = word[i];
    if(pTrie->children[temp-'a']==NULL){
        return 0;
    }
    pTrie = pTrie->children[temp-'a'];
}
int x = 0;
for(int i = 0;i<26;i++){
    if(pTrie->children[i]!=NULL){
        x+=pTrie->children[i]->count;
    }
}
return pTrie->count-x;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    free(pTrie);
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* new = calloc(1,sizeof(struct Trie));
    new->count = 0;
    for(int i = 0;i<26;i++){
        new->children[i]=NULL;
    }
    return new;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    int x = 0;
    fscanf(fp,"%d",&x);

    for(int i =0;i<x;i++){
        pInWords[i] = (char*)calloc(256,sizeof(char));
        fscanf(fp,"%s",pInWords[i]);
    }
    return x;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}