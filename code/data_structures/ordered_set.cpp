// find_by_order returns an iterator to the element at a given position
// order_of_key returns the position of a given element
// If the element isn't in the set, we get the position that the element would have
// O(log n)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;

#include <ext/pb_ds/tree_policy.hpp>
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

// Patricia tree implementation
#include <ext/pb_ds/trie_policy.hpp>
typedef trie< string, null_type, trie_string_access_traits<>,
pat_trie_tag, trie_prefix_search_node_update> pref_trie;
//example( ?prefix list all words with it +word add word ) 10000 limit on operations
while( cin >> x ){
	if( x[0] == '?' ) {
		cout << x.substr(1) << endl;
		auto range=base.prefix_range( x.substr( 1 ) );
		int t=0;
		for( auto it = range.first ; t < 20 && it != range.second ; ++it, ++t )
			cout<<"  "<<*it<<endl;
	}
	else base.insert(x.substr(1));
}
