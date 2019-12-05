// Pre-condition
// a[lo..hi] contains defined Items

//   lo         p       i       j        q      hi
//   +-+-------+-------+---------+-------+-------+
// a |v|  = v  |  < v  |   ???   |  > v  |  = v  |
//   +-+-------+-------+---------+-------+-------+

v = a[lo];  // could use median-of-3
i = p = lo+1;
j = q = hi;

for (;;) {
	// shift i up to next a[i] >= v
	while (less(a[i],v) && i < j) i++;

	// shift j down to next a[j] <= v
	while (less(v,a[j]) && j >= i) j--;

	// if i and j cross over, done
	if (i >= j) break;

	// swap a[i] and a[j]
	swap(a, i, j);

	// if a[i] == v, move to p region
	if (eq(a[i],v)) { swap(a,p,i); p++; }

	// if a[j] == v, move to q region
	if (eq(a[j],v)) { swap(a,q,j); q--; }
}
// move pivot into position (at a[i])
k = less(a[i],v) ? i : i+1;
swap(a,lo,k);

// move equal values from p region to just below a[i]
// note: p region is from a[lo+1..p-1]

// move equal values from q region to just above a[i]
// note: q region is from a[q+1..hi]

// Post-condition
// a[lo..j] < x && a[j+1..i-1] == x && a[i..hi] > x


