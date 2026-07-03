---
name: review
description: Review a C/C++ source file for memory leaks, include audit issues, API consistency, constexpr opportunities, performance, documentation, security issues, and README accuracy
argument-hint: <file-path>
disable-model-invocation: true
---

Re-read $ARGUMENTS fresh before doing anything else. Do not rely on any cached content.

Review the file at $ARGUMENTS for the following, in order:

1. **Memory leaks** — dynamic allocations without matching deallocation on all code paths; missing cleanup in destructors or error branches.

2. **Include audit** — unused `#include` directives (nothing from the header is directly used in this file); missing `#include` directives (symbols are used but their header is not included, relying on transitive inclusion).

3. **API consistency** — naming conventions, parameter ordering, and return type conventions relative to the rest of the file and the project.

4. **constexpr opportunities** — functions, variables, or constructors that could be marked `constexpr` or `constexpr static`, considering whether the types involved (e.g. SIMD intrinsics, mutexes, heap allocation) actually permit compile-time evaluation.

5. **Performance** — unnecessary copies where a reference, move, or `std::move` would suffice; missing `noexcept` on non-throwing functions; heap allocations that could be stack-allocated or avoided; expensive operations inside tight loops that could be hoisted out; missing `reserve()` on containers that grow incrementally.

6. **Documentation** — public functions, methods, or types that lack doc comments; doc comments that are inconsistent with the current signature or behavior (wrong parameter names, stale descriptions, missing `\param` / `\return` / `\pre` entries relative to other documented symbols in the file).

7. **Security** — buffer overflows or out-of-bounds access; use of unsafe functions (e.g. `strcpy`, `sprintf`, `gets`); integer overflow or underflow in size calculations; unvalidated input at system boundaries; sensitive data (keys, secrets) left in memory longer than necessary; use of cryptographically weak primitives or RNG.

8. **README** — Review the README files for accuracy, consistency, and completeness.

Present all findings grouped by category before making any changes. For each finding include the line number and a brief explanation. After presenting the report, wait for confirmation before applying any fixes.

If $ARGUMENTS is empty, ask the user which file to review.
