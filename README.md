# OEIS A262181: reference for prime-sided polygons (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted.** (replaced by the registry tool)
<!-- oeis-status:end -->

## Definition

a(n), n≥3, counts convex equilateral n-gons, up to translation, rotation and uniform scaling, with mirror images counted separately when distinct, with interior angles positive integer multiples of π/n, allowing straight angles π. The offset is 3.

## Terms / result

No terms change. The live [A262181](https://oeis.org/A262181), read 2026-11-13, has the unattributed line `Conjecture: There is only one convex equilateral n-gon for prime n.` The result is that a(p)=1 for primes p≥3.

## How it was obtained

Bjorn Poonen and Michael Rubinstein, *The number of intersection points made by the diagonals of a regular polygon*, SIAM Journal on Discrete Mathematics 11 (1998), 135–156, [doi:10.1137/S0895480195281246](https://doi.org/10.1137/S0895480195281246), [arXiv:math/9508209](https://arxiv.org/abs/math/9508209). Read 2026-11-13, [PDF, Lemma 2, p. 7](https://klein.mit.edu/~poonen/papers/ngon.pdf): “The only minimal relations (up to rotation) involving only the 2p-th roots of unity, for p prime, are R2 and Rp.” Normalized edge vectors are 2p-th roots, since exterior turns are multiples of π/p, and sum to zero by closure. Decompose this sum into minimal relations: for odd p, p terms cannot be partitioned entirely into pairs, so one Rp consumes all p terms. Convex order then gives the regular p-gon, up to similarity. The regular polygon exists. This is an application of the published lemma, not a new claim of priority.

## Verification

The paper's lemma and the correspondence were checked directly. The paper's proof and OEIS terms were not independently reverified. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

Poonen and Rubinstein's 1998 lemma supplies the needed roots-of-unity result. See [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Read Lemma 2 in the linked PDF and check the edge-vector argument above; allow about ten minutes. No paper is bundled.

## Provenance

Source: `projects/science/athanor-oeis`, commit `11b7ea9cc6f4c0057731d8e36c023f8b36e7c27f`, `tasks/2026-11-12-A262181-equilateral-prime-gons/answers/2026-11-12-chatgpt.md`.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
