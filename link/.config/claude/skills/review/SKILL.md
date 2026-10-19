---
name: review
description: Review C/C++ source files for bugs, memory leaks, include audit issues, API consistency, constexpr and noexcept opportunities, performance, documentation, security issues, and stale README or CLAUDE.md text
argument-hint: <file-path>...
disable-model-invocation: true
---

If $ARGUMENTS is empty, ask the user which files to review, and wait for the answer.

Re-read each file in $ARGUMENTS before doing anything else.  Do not rely on any cached content.

Check CLAUDE.md and memory before reviewing.  A vendored file, or a copy synced from another repo, is fixed upstream, so report a defect in one as a fix to make there.  Honor inline suppressions such as `// NOLINT`, and do not re-raise anything memory marks as intentional.

## Baseline

Run the repo's checks on each file before reading the code, and use their output as the baseline for the review.

- If CLAUDE.md names a build or lint command for the file, use it.
- Otherwise, from the header's directory, compile it as its own translation unit with `printf '#include "%s"\n' <file> | $CXX $CPPFLAGS $CXXFLAGS -x c++ -fsyntax-only -`, using `$CC`, `$CFLAGS`, and `-x c` for a `.h` file.  Then run `clang-tidy <file> -- $CPPFLAGS $CXXFLAGS`, or `$CFLAGS` for C.
- Judge each check by its output, not its exit status, since a Makefile recipe may ignore errors.
- Report only the diagnostics that memory does not already record as accepted.

## Review

Review each file for the following, in order.  The C++-only checks, such as constructors, `noexcept`, `std::move`, and `reserve()`, do not apply to C, where `constexpr` covers objects only.

1. **Bugs.**  Look for the following.
   - Logic errors and broken edge cases, such as an empty range, a zero, or the extreme values of a type.
   - Undefined behavior, such as signed overflow, a shift by the width of the type or more, an out-of-range conversion, or a strict-aliasing violation.

   Prove each bug before reporting it, with a test program that shows the wrong result.  An assertion inside `#if defined(DEBUG)` runs only when the program is built with `-DDEBUG`.

2. **Memory leaks.**
   - A dynamic allocation without a matching release on every code path.
   - Missing cleanup in a destructor or an error branch.

3. **Include audit.**
   - An unused `#include`, where nothing from the header is used directly in this file.
   - A missing `#include`, where a symbol is used but its header is reached only through transitive inclusion.

4. **API consistency.**  Compare naming conventions, parameter ordering, and return-type conventions with the rest of the file and the project.

5. **Stronger declarations.**
   - A function, variable, or constructor that could be `constexpr` or `static constexpr`, if the types involved permit compile-time evaluation.  SIMD intrinsics, mutexes, and heap allocation often do not.
   - A non-throwing C++ function that lacks `noexcept`.

6. **Performance.**
   - An unnecessary copy where a reference or `std::move` would do.
   - A heap allocation that could be on the stack or avoided.
   - An expensive operation inside a tight loop that could be hoisted out of it.
   - A container that grows incrementally without a `reserve()`.

7. **Documentation.**
   - A public function, method, or type with no doc comment.
   - A doc comment that no longer matches the signature or behavior, such as a wrong parameter name, a stale description, or a missing `\param`, `\return`, or `\pre` that other documented symbols in the file have.
   - A doc comment that breaks the repo's prose style guide, such as COMMENT-STYLE.md, if it has one.

8. **Security.**
   - A buffer overflow or out-of-bounds access.
   - An unsafe function, such as `strcpy`, `sprintf`, or `gets`.
   - Integer overflow or underflow in a size calculation.
   - Unvalidated input at a system boundary.
   - Sensitive data, such as a key or secret, left in memory longer than necessary.
   - A cryptographically weak primitive or RNG.

9. **Stale documentation elsewhere.**  Look for any README or CLAUDE.md that documents the reviewed files and describes usage, options, or behavior that no longer matches the code.

## Report

Present all findings before making any changes, grouped by category in the order above, and omit an empty category.  For each finding, give `path:line`, the problem, and a suggested fix.  If nothing survives, say so plainly.

After presenting the report, wait for confirmation before applying any fixes.
