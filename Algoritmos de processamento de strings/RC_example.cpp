void preRc(char *x, int m, int h[],
           int rcBc[ASIZE][XSIZE], int rcGs[]) {
   int a, i, j, k, q, r, s,
       hmin[XSIZE], kmin[XSIZE], link[XSIZE],
       locc[ASIZE], rmin[XSIZE];
 
   /* Computation of link and locc */
   for (a = 0; a < ASIZE; ++a)
      locc[a] = -1;
   link[0] = -1;
   for (i = 0; i < m - 1; ++i) {
      link[i + 1] = locc[x[i]];
      locc[x[i]] = i;
   }
 
   /* Computation of rcBc */
   for (a = 0; a < ASIZE; ++a)
      for (s = 1; s <= m; ++s) {
         i = locc[a];
         j = link[m - s];
         while (i - j != s && j >= 0)
            if (i - j > s)
               i = link[i + 1];
            else
               j = link[j + 1];
         while (i - j > s)
            i = link[i + 1];
         rcBc[a][s] = m - i - 1;
      }
 
   /* Computation of hmin */
   k = 1;
   i = m - 1;
   while (k <= m) {
      while (i - k >= 0 && x[i - k] == x[i])
         --i;
      hmin[k] = i;
      q = k + 1;
      while (hmin[q - k] - (q - k) > i) {
         hmin[q] = hmin[q - k];
         ++q;
      }
      i += (q - k);
      k = q;
      if (i == m)
         i = m - 1;
   }
 
   /* Computation of kmin */
   memset(kmin, 0, m * sizeof(int));
   for (k = m; k > 0; --k)
      kmin[hmin[k]] = k;
 
   /* Computation of rmin */
   for (i = m - 1; i >= 0; --i) {
      if (hmin[i + 1] == i)
         r = i + 1;
      rmin[i] = r;
   }
 
   /* Computation of rcGs */
   i = 1;
   for (k = 1; k <= m; ++k)
      if (hmin[k] != m - 1 && kmin[hmin[k]] == k) {
         h[i] = hmin[k];
         rcGs[i++] = k;
      }
   i = m-1;
   for (j = m - 2; j >= 0; --j)
      if (kmin[j] == 0) {
         h[i] = j;
         rcGs[i--] = rmin[j];
      }
   rcGs[m] = rmin[0];
}
 
 
void RC(char *x, int m, char *y, int n) {
   int i, j, s, rcBc[ASIZE][XSIZE], rcGs[XSIZE], h[XSIZE];
 
   /* Preprocessing */
   preRc(x, m, h, rcBc, rcGs);
 
   /* Searching */
   j = 0;
   s = m;
   while (j <= n - m) {
      while (j <= n - m && x[m - 1] != y[j + m - 1]) {
         s = rcBc[y[j + m - 1]][s];
         j += s;
      }
      for (i = 1; i < m && x[h[i]] == y[j + h[i]]; ++i);
      if (i >= m)
         OUTPUT(j);
      s = rcGs[i];
      j += s;
   }
}
