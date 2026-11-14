# Independent verification of OEIS A262181 — 2026-11-15

Source repository: `iwasborninbali/oeis-A262181-unsubmitted`, starting commit `7f15dfa522deeb98baf1f21865c5b5ad109a9587`. Examined `README.md`, `CERTIFICATE.md`, `PRIOR-ART.md`; the supplied archive contains no pre-existing `verification/` files. I did not author or rely on the certificate. This report distinguishes mathematical correctness from novelty.

## Claim

Exact `CERTIFICATE.md` claim: **"Poonen and Rubinstein's Lemma 2 implies that each admissible prime-sided polygon in A262181 is regular."**

The README further interprets this as `a(p)=1` for every prime `p>=3`, with no change of terms and no new theorem claimed by the lab.

## Source check

**Primary source read:** Bjorn Poonen and Michael Rubinstein, *The Number of Intersection Points Made by the Diagonals of a Regular Polygon*, *SIAM J. Discrete Math.* **11** (1998), 135–156, DOI `10.1137/S0895480195281246`, arXiv `math/9508209`. Direct author/coauthor-hosted copy: https://www.math.uwaterloo.ca/~mrubinst/publications/ngon.pdf ; arXiv: https://arxiv.org/abs/math/9508209 . The MIT-hosted PDF linked by the README timed out; the coauthor-hosted paper and arXiv transcription were available.

**Exact location:** Section 3, **Lemma 2, printed page 8 (PDF page 8, zero-based PDF index 7)**, not page 7 as the README says. Short verbatim quotation: "The only minimal relations (up to rotation) involving only the 2p-th roots of unity, for p prime, are R2 and Rp." The paper defines relations, minimality, and `R_p = 1+zeta_p+...+zeta_p^(p-1)=0` in Section 3, **page 6**, equation (4) and following paragraphs. Its Lemma 2 proof is on page 8.

**Support: exact implication, not an explicit polygon statement.** For an OEIS-admissible convex equilateral `p`-gon, write its interior angles as `m_i*pi/p`, `1<=m_i<=p`, including `m_i=p` (straight angles). Unit side vectors `v_i` turn through `(p-m_i)*pi/p`; hence, after a common rotation, each is a `2p`-th root of unity and `sum(v_i)=0`. This is a positive relation of **weight p**, including multiplicities. Decompose it into minimal relations using the paper's definition. Lemma 2 permits only weights 2 (`R_2`) or `p` (`R_p`). Because `p` is odd, weight `p` cannot be partitioned solely into 2's; an `R_p` must use all `p` sides. Thus the side directions are equally spaced, each occurring once. Convex cyclic ordering (allowing zero turns) forces the regular `p`-gon; its reflection is congruent to it. Existence gives `a(p)=1`.

The OEIS offset is **3** and its allowable angles are `0<m<=p`, with straight angles allowed, exactly as accounted for above. The paper itself counts diagonal intersections of a **regular** polygon and does **not** formulate this separate classification of all convex equilateral polygons. Thus it **supports the certificate's word "implies"**, not a claim that the paper literally states the OEIS theorem. The paper's full proof was not reverified.

## Independent computation

**New program:** `check_polygons.cpp` (C++17, no downloaded code or floating-point comparisons); output: `output.log`. For each odd prime `p` in `{3,5,7,11,13}`, enumerate all ordered exterior-turn tuples `t_i=p-m_i`, with `0<=t_i<p`, `sum(t_i)=2p`, and first unit edge fixed at direction 0. The headings after each turn are exponents of `zeta_(2p)`. The vector sum is tested **exactly** using `zeta_(2p)^p=-1` and `Phi_(2p)(x)=sum_(k=0)^(p-1) (-1)^k*x^k`: the signed counts of powers `x^0,...,x^(p-1)` must equal one common integer times `(+1,-1,...,+1)`. Closed, monotonically turning, nondegenerate unit-edge polygons are convex; zero turns are included. This enumerates possible turn descriptions rather than assuming Lemma 2. No quotient by rotation/reflection is needed when there is only one valid description.

Compile/run: `g++ -std=c++17 -O3 -Wall -Wextra -pedantic check_polygons.cpp -o check_polygons && ./check_polygons > output.log`. On this verifier's container (wall-clock per-prime elapsed times printed by `steady_clock`):

| p | Candidate turn tuples | Exactly closed | Nonregular | OEIS a(p) | Runtime (seconds) |
|---:|---:|---:|---:|---:|---:|
| 3 | 1 | 1 | 0 | 1 | 0.00000014 |
| 5 | 381 | 1 | 0 | 1 | 0.000004226 |
| 7 | 26,769 | 1 | 0 | 1 | 0.000158476 |
| 11 | 60,632,419 | 1 | 0 | 1 | 0.259833 |
| 13 | 2,639,871,326 | 1 | 0 | 1 | 14.3764 |

These **match all tested prime-index terms** of the live A262181 (offset 3); no counterexamples found. This is finite evidence, not a computational proof for every prime. The exact original unrounded times are in `output.log`. SHA-256 (UTF-8 files, no normalization):

- `check_polygons.cpp`: `27cc183a9b17f5bb77977f974ca5bbcf3e89eabcd32f0419ea9316e9d41b77ab`
- `output.log`: `454f0b4a7d1b60ee52ba026443f923d6e0028fd83f4783de1bbd23c1e669ee07`

## Entry check

**Live page inspected on 2026-11-15:** https://oeis.org/A262181 . Name: "a(n) = total number of convex equilateral n-gons with corner angles of m*Pi/n (0 < m <= n)." Offset `3,2`. The displayed list for `n=3..20` includes `a(3)=a(5)=a(7)=a(11)=a(13)=a(17)=a(19)=1`. The COMMENTS still say, "Conjecture: There is only one convex equilateral n-gon for prime n." Poonen–Rubinstein and Lam–Leung are **not named** in its LINKS/FORMULA/COMMENTS. Its LINKS already cite Gilbert Labelle and Annie Lacasse, *Closed paths whose steps are roots of unity* (FPSAC 2011), which includes a related prime-root statement in §3, printed p. 602–603 (formula (3.1)), but counts unrestricted closed walks rather than convex equilateral polygons.

**Crucial prior OEIS statement:** The A262181 **FORMULA** dated 2017 says `A262181(n)=A292355(n)` for `n` prime or twice prime. The live A292355 ("Number of distinct convex equilateral n-gons having rotational symmetry ...", offset 3) already gives

`A292355(n)=-(1+(-1)^n)/2 + (1/n)*sum_(d|n) (phi(n/d)-mu(n/d))*binomial(3*d-1,d-1)`.

For every odd prime `p`, the `d=p` summand is zero (`phi(1)-mu(1)=0`) and `d=1` contributes `phi(p)-mu(p)=p`, giving **A292355(p)=1 and therefore A262181(p)=1**. Thus the equivalent prime-index numerical conclusion is **already a consequence of existing OEIS formulas**, notwithstanding the stale "Conjecture" comment. This is separate from the newly identified, absent Poonen–Rubinstein bibliographic attribution; the existing formula does not itself say every polygon is regular, although uniqueness plus the regular example entails that.

**Better/newer source:** T. Y. Lam and K. H. Leung, *On Vanishing Sums of Roots of Unity*, *J. Algebra* **224** (2000), 91–109, DOI `10.1006/jabr.1999.8089`, https://arxiv.org/abs/math/9511209 . **Corollary 3.4, printed page 8** gives the same minimal-relation classification for orders with two prime divisors and explicitly credits `[PR: Lemma 2]` for `m=2p`. It is newer and stronger in scope, but Poonen–Rubinstein remains the original direct result for `2p`.

**Access limitation:** The public OEIS HTML was readable, but the linked `internal format` (`/A262181/internal`), `history` (`/history?seq=A262181`) and text endpoints returned HTTP 403 through the available web interface; hence I cannot certify the complete revision history or raw internal fields. Dated attributions above are visible directly on the public entry, not inferred from inaccessible history. The claim that the bibliography is absent is limited to the **currently displayed entry**, not every historical revision.

## Verdict

**REFUTED as a *new* prime-case result / correction, not as mathematics.** The source and inference are sound; independent exact enumeration matches `a(p)=1` for `p=3,5,7,11,13`, and the Poonen–Rubinstein citation is indeed missing from the displayed current entry. But the existing A262181 equality with A292355, combined with A292355's own explicit formula, **already establishes the equivalent `a(p)=1` conclusion** for all odd primes. Therefore the requested novelty requirement ("or an equivalent statement") fails. A bibliographic/comment correction crediting Lemma 2 and marking the old "Conjecture" resolved would still be useful; the published paper itself does not explicitly formulate the polygon proposition. No priority is claimed. History-check completeness remains **not established** because OEIS blocked the raw views.
