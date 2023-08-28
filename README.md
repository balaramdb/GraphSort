# GraphSort: Sorting an array using the topological sort of a corresponding comparison graph

The quest for efficient sorting is ongoing, and we will explore a graph-based stable sorting strategy, in particular employing comparison graphs. We use the topological sort to map the comparison graph to a linear domain, and we can manipulate our graph such that the resulting topological sort is the sorted array. By taking advantage of the many relations between Hamiltonian paths and topological sorts in comparison graphs, we design a Divide-and-Conquer algorithm that runs in the optimal $O(log(n))$ time. In the process, we construct a new merge process for graphs with relevant invariant properties for our use. Furthermore, this method is more space-efficient than the famous MergeSort since we modify our fixed graph only.

https://doi.org/10.1016/j.tcs.2020.09.004
