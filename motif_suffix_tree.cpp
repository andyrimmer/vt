/* The MIT License

   Copyright (c) 2014 Adrian Tan <atks@umich.edu>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "motif_suffix_tree.h"

#define A 0
#define C 1
#define G 2
#define T 3

/**
 * Constructs a MotifSuffixTreeNode.
 */
MotifSuffixTreeNode::MotifSuffixTreeNode()
{
    parent = NULL;
    for (size_t b = A; A<=T; ++b)
    {
        children[b] = NULL;
    }
    this->suffix = "";
    count = 0;
};

/**
 * Constructs a MotifSuffixTreeNode and initialize it with a parent and a suffix.
 */
MotifSuffixTreeNode::MotifSuffixTreeNode(MotifSuffixTreeNode* parent, std::string& suffix)
{
    parent = parent;
    for (size_t b = A; A<=T; ++b)
    {
        children[b] = NULL;
    }
    this->suffix = suffix;
    count = 0;
};

/**
 * Constructs an MotifSuffixTreeNode.
 */
MotifSuffixTreeNode::~MotifSuffixTreeNode()
{
    for (size_t b = A; A<=T; ++b)
    {
        if (children[b])
        {
            delete children[b];
        }

        children[b] = NULL;
    }

    parent = NULL;
};

/**
 * Constructor.
 */
MotifSuffixTree::MotifSuffixTree()
{
    root = NULL;
};

/**
 * Destructor.
 */
MotifSuffixTree::~MotifSuffixTree()
{
    if (root) delete root;
    root = NULL;
};

/**
 * Construct suffix tree based on sequence.
 */
void MotifSuffixTree::set_sequence(char* sequence)
{
    set_sequence(sequence, strlen(sequence));
};

/**
 * Construct suffix tree based on sequence up to max_motif_len.
 */
void MotifSuffixTree::set_sequence(char* sequence, int32_t max_motif_len)
{
    if (!root)
    {
        root = new MotifSuffixTreeNode();
    }

    size_t len = strlen(sequence);

    //i is starting
    for (size_t i=0; i<len; ++i)
    {
        add_suffix(sequence, i, i+max_motif_len-1);
    }
};

/**
 * Gets candidate motifs up to max_motif_len.
 */
void MotifSuffixTree::get_candidate_motifs(std::vector<CandidateMotif*>& candidate_motifs, int32_t max_motif_len)
{
};

/**
 * Adds a suffix of sequence from start to end.
 */
void MotifSuffixTree::add_suffix(char* sequence, int32_t start, int32_t end)
{
    MotifSuffixTreeNode* node = root;

    for (size_t i = start; i<=end; ++i)
    {
        char base = sequence[i];

        if (base==0) break;

        if (node->children[base]==NULL)
        {
            node->children[base] = new MotifSuffixTreeNode(node, node->suffix.append(1,base));
            node->count = 0;
        }

        node = node->children[base];
        ++node->count;
    }
};

#undef A
#undef C
#undef G
#undef T