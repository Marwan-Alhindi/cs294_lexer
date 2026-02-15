# Testing Rules

## Test Framework
- GoogleTest (gtest)

## What to Test
- Every public function/method must have at least one test
- Every token type must have a dedicated test case
- Edge cases must be explicitly tested (see assignment tips)

## Test File Naming
- Tests live alongside source: `src/<module>/<module>_test.cc`
- Test names: `TEST(<ModuleName>, <DescriptiveTestName>)`

## TDD Workflow (tests first)
1. Read the module's `.md` doc
2. Write test cases based on the documented API
3. Verify tests compile but FAIL (red)
4. Write implementation code
5. Verify tests PASS (green)
6. Refactor if needed

## Edge Cases to Cover
- `fn_name` is IDENT, not FN keyword
- `==` is EQ, not two ASSIGN tokens
- `!=` is NEQ, not NOT + ASSIGN
- `<=` and `>=` are single tokens
- Whitespace and comments should be skipped
- Empty input produces no tokens (or just EOF)
- Unterminated strings should produce an error token
- Numbers: only integers (no floats required)
