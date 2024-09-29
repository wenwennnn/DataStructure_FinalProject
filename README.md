# Essay Search 
*ID: 110062239 侯茹文*

## 1. Implementation

I used a `trie` to complete this project. A trie can handle both prefix search and exact search. Therefore, we can directly use a trie to perform these searches. Since a trie sets up a tree that stores the words in a document, I added a boolean value to the `trienode` to record whether this node marks the end of a word.

During the execution of a prefix search, the trie is traversed. If we reach the last letter of the prefix search, it returns `true`. The exact search is similar, but the difference is that the exact search returns the boolean value that indicates whether the node is the end of a word, ensuring it is indeed a complete word.

For the suffix search, I set up another `root` within the same trie to store the reversed order of words (by adding another loop to handle the reversed order during insertion). The suffix search then operates on this reversed `root`.

After constructing several tries, I used a vector to store all the tries of the documents, and then opened the query file. Starting with the first line of the query, I checked whether the first document met the requirements; if it did, it was added to the answer vector. This process continued until all documents were checked, and then moved on to the next query.

## 2. Challenges

The most time-consuming part for me was the suffix search. It took me a while to figure out using an inverse root, and due to some additional elements I needed to add, I kept forgetting parts, leading to quite a bit of debugging – it was a reflection of my own mistakes.

Another issue that took a lot of time was handling the cases of `""` and `**`. Initially, I deleted `""` and `**`, but I forgot that they would be processed multiple times (since the same query would be checked across `n` documents). When handling the query for the first document, `**` and `""` were removed, and thus disappeared when checking the other documents, which resulted in a bug that took me a long time to find.

## 3. References

- [Trie Implementation on LeetCode](https://haogroot.com/2021/01/07/trie-leetcode/)
- I also asked many questions on [OpenAI Chat](https://chat.openai.com/chat), which helped me a lot.
